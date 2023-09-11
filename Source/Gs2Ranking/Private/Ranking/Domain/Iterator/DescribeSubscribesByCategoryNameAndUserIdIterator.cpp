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

#include "Ranking/Domain/Iterator/DescribeSubscribesByCategoryNameAndUserIdIterator.h"
#include "Ranking/Domain/Model/SubscribeUser.h"
#include "Ranking/Domain/Model/User.h"

namespace Gs2::Ranking::Domain::Iterator
{

    FDescribeSubscribesByCategoryNameAndUserIdIterator::FDescribeSubscribesByCategoryNameAndUserIdIterator(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Ranking::FGs2RankingRestClientPtr Client,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> CategoryName,
        const TOptional<FString> UserId
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        Client(Client),
        NamespaceName(NamespaceName),
        CategoryName(CategoryName),
        UserId(UserId)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FDescribeSubscribesByCategoryNameAndUserIdIterator::FIteratorNextTask::Action(TSharedPtr<TSharedPtr<Gs2::Ranking::Model::FSubscribeUser>> Result)
    {
        ++Iterator;
        *Result = Iterator->Current();
        return Iterator.Error();
    }

    FDescribeSubscribesByCategoryNameAndUserIdIterator::FIterator::FIterator(
        const TSharedRef<FDescribeSubscribesByCategoryNameAndUserIdIterator> Iterable,
        FOneBeforeBegin
    ) :
        Self(Iterable),
        bLast(false),
        bEnd(false),
        FetchSize(TOptional<int32>())
    {
    }

    FDescribeSubscribesByCategoryNameAndUserIdIterator::FIterator& FDescribeSubscribesByCategoryNameAndUserIdIterator::FIterator::operator++()
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
            const auto ListParentKey = Gs2::Ranking::Domain::Model::FUserDomain::CreateCacheParentKey(
                Self->NamespaceName,
                Self->UserId,
                "SubscribeUser"
            );

            if (!RangeIteratorOpt)
            {
                Range = Self->Cache->TryGetList<Gs2::Ranking::Model::FSubscribeUser>(ListParentKey);

                if (Range)
                {
                    Range->RemoveAll([this](const Gs2::Ranking::Model::FSubscribeUserPtr& Item) { return Self->CategoryName && Item->GetCategoryName() != Self->CategoryName; });
                    bLast = true;
                    RangeIteratorOpt = Range->CreateIterator();
                    bEnd = !static_cast<bool>(*RangeIteratorOpt) && bLast;
                    return *this;
                }
            }

            const auto Future = Self->Client->DescribeSubscribesByCategoryNameAndUserId(
                MakeShared<Gs2::Ranking::Request::FDescribeSubscribesByCategoryNameAndUserIdRequest>()
                    ->WithNamespaceName(Self->NamespaceName)
                    ->WithCategoryName(Self->CategoryName)
                    ->WithUserId(Self->UserId)
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
                    Gs2::Ranking::Model::FSubscribeUser::TypeName,
                    ListParentKey,
                    Gs2::Ranking::Domain::Model::FSubscribeUserDomain::CreateCacheKey(
                        Item->GetCategoryName(),
                        Item->GetTargetUserId()
                    ),
                    Item,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            if (Range)
            {
                Range->RemoveAll([this](const Gs2::Ranking::Model::FSubscribeUserPtr& Item) { return Self->CategoryName && Item->GetCategoryName() != Self->CategoryName; });
            }
            RangeIteratorOpt = Range->CreateIterator();
            bLast = true;
            if (bLast) {
                Self->Cache->SetListCached(
                    Gs2::Ranking::Model::FSubscribeUser::TypeName,
                    ListParentKey
                );
            }
        }

        bEnd = bLast && !*RangeIteratorOpt;
        return *this;
    }

    FDescribeSubscribesByCategoryNameAndUserIdIterator::FIterator FDescribeSubscribesByCategoryNameAndUserIdIterator::OneBeforeBegin()
    {
        return FIterator::OneBeforeBeginOf(this->AsShared());
    }

    FDescribeSubscribesByCategoryNameAndUserIdIterator::FIterator FDescribeSubscribesByCategoryNameAndUserIdIterator::begin()
    {
        return FIterator::BeginOf(this->AsShared());
    }

    FDescribeSubscribesByCategoryNameAndUserIdIterator::FIterator FDescribeSubscribesByCategoryNameAndUserIdIterator::end()
    {
        return FIterator::EndOf(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

