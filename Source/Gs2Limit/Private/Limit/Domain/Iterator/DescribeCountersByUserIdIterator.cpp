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

#include "Limit/Domain/Iterator/DescribeCountersByUserIdIterator.h"
#include "Limit/Domain/Model/Counter.h"
#include "Limit/Domain/Model/User.h"

namespace Gs2::Limit::Domain::Iterator
{

    FDescribeCountersByUserIdIterator::FDescribeCountersByUserIdIterator(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Limit::FGs2LimitRestClientPtr Client,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId,
        const TOptional<FString> LimitName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        Client(Client),
        NamespaceName(NamespaceName),
        UserId(UserId),
        LimitName(LimitName)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FDescribeCountersByUserIdIterator::FIteratorNextTask::Action(TSharedPtr<TSharedPtr<Gs2::Limit::Model::FCounter>> Result)
    {
        ++Iterator;
        *Result = Iterator->Current();
        return Iterator.Error();
    }

    FDescribeCountersByUserIdIterator::FIterator::FIterator(
        const TSharedRef<FDescribeCountersByUserIdIterator> Iterable,
        FOneBeforeBegin
    ) :
        Self(Iterable),
        bLast(false),
        bEnd(false),
        PageToken(TOptional<FString>()),
        FetchSize(TOptional<int32>())
    {
    }

    FDescribeCountersByUserIdIterator::FIterator& FDescribeCountersByUserIdIterator::FIterator::operator++()
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
            const auto ListParentKey = Gs2::Limit::Domain::Model::FUserDomain::CreateCacheParentKey(
            Self->NamespaceName,
            Self->UserId,
            "Counter"
        );
            if (Self->Cache->IsListCached(
                Gs2::Limit::Model::FCounter::TypeName,
                ListParentKey
            )) {
                Range = MakeShared<TArray<Gs2::Limit::Model::FCounterPtr>>();
                *Range = Self->Cache->List<Gs2::Limit::Model::FCounter>(
                    ListParentKey
                );
                Range->RemoveAll([this](const Gs2::Limit::Model::FCounterPtr& Item) { return Self->LimitName && Item->GetLimitName() == Self->LimitName; });
                RangeIteratorOpt = Range->CreateIterator();
                PageToken = TOptional<FString>();
                bLast = true;
                bEnd = static_cast<bool>(*RangeIteratorOpt);
                return *this;
            }
            const auto Future = Self->Client->DescribeCountersByUserId(
                MakeShared<Gs2::Limit::Request::FDescribeCountersByUserIdRequest>()
                    ->WithNamespaceName(Self->NamespaceName)
                    ->WithUserId(Self->UserId)
                    ->WithLimitName(Self->LimitName)
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
                    Gs2::Limit::Model::FCounter::TypeName,
                    ListParentKey,
                    Gs2::Limit::Domain::Model::FCounterDomain::CreateCacheKey(
                        Item->GetLimitName(),
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

    FDescribeCountersByUserIdIterator::FIterator FDescribeCountersByUserIdIterator::OneBeforeBegin()
    {
        return FIterator::OneBeforeBeginOf(this->AsShared());
    }

    FDescribeCountersByUserIdIterator::FIterator FDescribeCountersByUserIdIterator::begin()
    {
        return FIterator::BeginOf(this->AsShared());
    }

    FDescribeCountersByUserIdIterator::FIterator FDescribeCountersByUserIdIterator::end()
    {
        return FIterator::EndOf(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

