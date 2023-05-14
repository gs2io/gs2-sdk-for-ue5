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

#include "News/Domain/Iterator/DescribeOutputsIterator.h"
#include "News/Domain/Model/Output.h"
#include "News/Domain/Model/Progress.h"

namespace Gs2::News::Domain::Iterator
{

    FDescribeOutputsIterator::FDescribeOutputsIterator(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::News::FGs2NewsRestClientPtr Client,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UploadToken
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        Client(Client),
        NamespaceName(NamespaceName),
        UploadToken(UploadToken)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FDescribeOutputsIterator::FIteratorNextTask::Action(TSharedPtr<TSharedPtr<Gs2::News::Model::FOutput>> Result)
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
            const auto ListParentKey = Gs2::News::Domain::Model::FProgressDomain::CreateCacheParentKey(
            Self->NamespaceName,
            Self->UploadToken,
            "Output"
        );
            if (Self->Cache->IsListCached(
                Gs2::News::Model::FOutput::TypeName,
                ListParentKey
            )) {
                Range = MakeShared<TArray<Gs2::News::Model::FOutputPtr>>();
                *Range = Self->Cache->List<Gs2::News::Model::FOutput>(
                    ListParentKey
                );
                RangeIteratorOpt = Range->CreateIterator();
                PageToken = TOptional<FString>();
                bLast = true;
                bEnd = static_cast<bool>(*RangeIteratorOpt);
                return *this;
            }
            const auto Future = Self->Client->DescribeOutputs(
                MakeShared<Gs2::News::Request::FDescribeOutputsRequest>()
                    ->WithNamespaceName(Self->NamespaceName)
                    ->WithUploadToken(Self->UploadToken)
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
                    Gs2::News::Model::FOutput::TypeName,
                    ListParentKey,
                    Gs2::News::Domain::Model::FOutputDomain::CreateCacheKey(
                        Item->GetName()
                    ),
                    Item,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            RangeIteratorOpt = Range->CreateIterator();
            PageToken = R->GetNextPageToken();
            bLast = !PageToken.IsSet();
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

