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

#include "Guard/Domain/Iterator/DescribeNamespacesIterator.h"
#include "Guard/Domain/Model/Namespace.h"

#include "Core/Domain/Gs2.h"

namespace Gs2::Guard::Domain::Iterator
{

    FDescribeNamespacesIterator::FDescribeNamespacesIterator(
        const TSharedPtr<Core::Domain::FGs2> Gs2,
        const Gs2::Guard::FGs2GuardRestClientPtr Client
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Client(Client)
    {
    }

    FDescribeNamespacesIterator::FDescribeNamespacesIterator(
        const FDescribeNamespacesIterator& From
    ):
        Gs2(From.Gs2),
        Client(From.Client)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FDescribeNamespacesIterator::FIteratorNextTask::Action(TSharedPtr<TSharedPtr<Gs2::Guard::Model::FNamespace>> Result)
    {
        ++Iterator;
        *Result = Iterator->Current();
        return Iterator.Error();
    }

    FDescribeNamespacesIterator::FIterator::FIterator(
        const TSharedRef<FDescribeNamespacesIterator> Iterable,
        FOneBeforeBegin
    ) :
        Self(Iterable),
        bLast(false),
        bEnd(false),
        PageToken(TOptional<FString>()),
        FetchSize(TOptional<int32>())
    {
    }

    FDescribeNamespacesIterator::FIterator& FDescribeNamespacesIterator::FIterator::operator++()
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
            const auto ListParentKey = "guard:Namespace";

            if (!RangeIteratorOpt)
            {
                Range = Self->Gs2->Cache->TryGetList<Gs2::Guard::Model::FNamespace>(ListParentKey);

                if (Range)
                {
                    bLast = true;
                    RangeIteratorOpt = Range->CreateIterator();
                    PageToken = TOptional<FString>();
                    bEnd = !static_cast<bool>(*RangeIteratorOpt) && bLast;
                    return *this;
                }
            }

            const auto Future = Self->Client->DescribeNamespaces(
                MakeShared<Gs2::Guard::Request::FDescribeNamespacesRequest>()
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
                Self->Gs2->Cache->Put(
                    Gs2::Guard::Model::FNamespace::TypeName,
                    ListParentKey,
                    Gs2::Guard::Domain::Model::FNamespaceDomain::CreateCacheKey(
                        Item->GetName()
                    ),
                    Item,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            if (Range)
            {
            }
            RangeIteratorOpt = Range->CreateIterator();
            PageToken = R->GetNextPageToken();
            bLast = !PageToken.IsSet();
            if (bLast) {
                Self->Gs2->Cache->SetListCached(
                    Gs2::Guard::Model::FNamespace::TypeName,
                    ListParentKey
                );
            }
        }

        bEnd = bLast && !*RangeIteratorOpt;
        return *this;
    }

    FDescribeNamespacesIterator::FIterator FDescribeNamespacesIterator::OneBeforeBegin()
    {
        return FIterator::OneBeforeBeginOf(this->AsShared());
    }

    FDescribeNamespacesIterator::FIterator FDescribeNamespacesIterator::begin()
    {
        return FIterator::BeginOf(this->AsShared());
    }

    FDescribeNamespacesIterator::FIterator FDescribeNamespacesIterator::end()
    {
        return FIterator::EndOf(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

