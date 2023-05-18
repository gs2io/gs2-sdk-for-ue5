/*
 * Copyright 2016 Game Server Services, Inc. or its affiliates. All Rights
 * Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

#if defined(_MSC_VER)
#pragma warning (push)
#pragma warning (disable: 4458) // Declaration hides class member
#elif defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow" // declaration shadows a field of
#endif

// ReSharper disable CppUnusedIncludeDirective

#include "Deploy/Domain/Iterator/DescribeOutputsIterator.h"
#include "Deploy/Domain/Model/Output.h"
#include "Deploy/Domain/Model/Stack.h"

namespace Gs2::Deploy::Domain::Iterator
{

    FDescribeOutputsIterator::FDescribeOutputsIterator(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Deploy::FGs2DeployRestClientPtr Client,
        const TOptional<FString> StackName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        Client(Client),
        StackName(StackName)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FDescribeOutputsIterator::FIteratorNextTask::Action(TSharedPtr<TSharedPtr<Gs2::Deploy::Model::FOutput>> Result)
    {
        ++Iterator;
        *Result = Iterator->Current();
        return Iterator.Error();
    }

    FDescribeOutputsIterator::FIterator::FIterator(
        const TSharedRef<FDescribeOutputsIterator> Iterable,
        FOneBeforeBegin
    ) :
        Self(Iterable),
        bLast(false),
        bEnd(false),
        PageToken(TOptional<FString>()),
        FetchSize(TOptional<int32>())
    {
    }

    FDescribeOutputsIterator::FIterator& FDescribeOutputsIterator::FIterator::operator++()
    {
        

        if (bEnd) return *this;

        if (ErrorValue && bLast)
        {
            bEnd = true;
            return *this;
        }

        if (RangeIteratorOpt) ++*RangeIteratorOpt;

        if (!RangeIteratorOpt || (!*RangeIteratorOpt && !bLast))
        {
            const auto ListParentKey = Gs2::Deploy::Domain::Model::FStackDomain::CreateCacheParentKey(
                Self->StackName,
                "Output"
            );
            Range = Self->Cache->TryGetList<Gs2::Deploy::Model::FOutput>(ListParentKey);
            if (Range) {
                RangeIteratorOpt = Range->CreateIterator();
                PageToken = TOptional<FString>();
                bLast = true;
                bEnd = !static_cast<bool>(*RangeIteratorOpt);
                return *this;
            }
            const auto Future = Self->Client->DescribeOutputs(
                MakeShared<Gs2::Deploy::Request::FDescribeOutputsRequest>()
                    ->WithStackName(Self->StackName)
                    ->WithPageToken(PageToken)
                    ->WithLimit(FetchSize)
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                ErrorValue = Future->GetTask().Error();
                bLast = true;
                return *this;
            }
            else
            {
                ErrorValue = nullptr;
            }
            const auto R = Future->GetTask().Result();
            Future->EnsureCompletion();
            Range = R->GetItems();
            for (auto Item : *R->GetItems())
            {
                Self->Cache->Put(
                    Gs2::Deploy::Model::FOutput::TypeName,
                    ListParentKey,
                    Gs2::Deploy::Domain::Model::FOutputDomain::CreateCacheKey(
                        Item->GetName()
                    ),
                    Item,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            RangeIteratorOpt = Range->CreateIterator();
            PageToken = R->GetNextPageToken();
            bLast = !PageToken.IsSet();
            if (bLast) {
                Self->Cache->SetListCache(
                    Gs2::Deploy::Model::FOutput::TypeName,
                    ListParentKey
                );
            }
        }

        bEnd = bLast && !*RangeIteratorOpt;
        return *this;
    }

    FDescribeOutputsIterator::FIterator FDescribeOutputsIterator::OneBeforeBegin()
    {
        return FIterator::OneBeforeBeginOf(this->AsShared());
    }

    FDescribeOutputsIterator::FIterator FDescribeOutputsIterator::begin()
    {
        return FIterator::BeginOf(this->AsShared());
    }

    FDescribeOutputsIterator::FIterator FDescribeOutputsIterator::end()
    {
        return FIterator::EndOf(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

