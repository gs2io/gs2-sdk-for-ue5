
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
 *
 * deny overwrite
 */

#if defined(_MSC_VER)
#pragma warning (push)
#pragma warning (disable: 4458) // Declaration hides class member
#elif defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow" // declaration shadows a field of
#endif

// ReSharper disable CppUnusedIncludeDirective

#include "Ranking/Domain/Iterator/DescribeSubscribesByCategoryNameIterator.h"
#include "Ranking/Domain/Model/SubscribeUser.h"
#include "Ranking/Domain/Model/RankingCategory.h"
#include "Ranking/Model/Cache/SubscribeUser.h"

#include "Core/Domain/Gs2.h"

namespace Gs2::Ranking::Domain::Iterator
{

    FDescribeSubscribesByCategoryNameIterator::FDescribeSubscribesByCategoryNameIterator(
        const TSharedPtr<Core::Domain::FGs2> Gs2,
        const Gs2::Ranking::FGs2RankingRestClientPtr Client,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> CategoryName,
        const Gs2::Auth::Model::FAccessTokenPtr AccessToken
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Client(Client),
        NamespaceName(NamespaceName),
        CategoryName(CategoryName),
        AccessToken(AccessToken)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FDescribeSubscribesByCategoryNameIterator::FIteratorNextTask::Action(TSharedPtr<TSharedPtr<Gs2::Ranking::Model::FSubscribeUser>> Result)
    {
        ++Iterator;
        *Result = Iterator->Current();
        return Iterator.Error();
    }

    FDescribeSubscribesByCategoryNameIterator::FIterator::FIterator(
        const TSharedRef<FDescribeSubscribesByCategoryNameIterator> Iterable,
        FOneBeforeBegin
    ) :
        Self(Iterable),
        bLast(false),
        bEnd(false),
        FetchSize(TOptional<int32>())
    {
    }

    FDescribeSubscribesByCategoryNameIterator::FIterator& FDescribeSubscribesByCategoryNameIterator::FIterator::operator++()
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
            const auto UserId = Self->AccessToken.IsValid() ? Self->AccessToken->GetUserId() : TOptional<FString>();
            const auto TimeOffset = Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>();
            const auto ListParentKey = Gs2::Ranking::Model::Cache::FSubscribeUserCache::CreateCacheParentKey(
                Self->NamespaceName,
                UserId,
                Self->CategoryName,
                TOptional<FString>(),
                TimeOffset
            );
            if (!RangeIteratorOpt)
            {
                Range = Self->Gs2->Cache->TryGetList<Gs2::Ranking::Model::FSubscribeUser>(ListParentKey);

                if (Range)
                {
                    bLast = true;
                    RangeIteratorOpt = Range->CreateIterator();
                    bEnd = !static_cast<bool>(*RangeIteratorOpt) && bLast;
                    return *this;
                }
            }

            const auto Request =
                MakeShared<Gs2::Ranking::Request::FDescribeSubscribesByCategoryNameRequest>()
                    ->WithContextStack(Self->Gs2->DefaultContextStack)
                    ->WithNamespaceName(Self->NamespaceName)
                    ->WithCategoryName(Self->CategoryName)
                    ->WithAccessToken(Self->AccessToken == nullptr ? TOptional<FString>() : Self->AccessToken->GetToken())
            ;
            const auto Future = Self->Client->DescribeSubscribesByCategoryName(Request);
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
            Range = R->GetItems().IsValid() ? R->GetItems() : MakeShared<TArray<Gs2::Ranking::Model::FSubscribeUserPtr>>();
            const auto CacheOwnerSnapshotUserId = Self->AccessToken.IsValid() ? Self->UserId() : TOptional<FString>();
            const auto CacheOwnerSnapshotTimeOffset = Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>();
            const auto ResultModel = R;


            if (Range.IsValid())
            {
                for (const auto& Item : *Range)
                {
                    if (!Item.IsValid()) continue;
                    Gs2::Ranking::Model::Cache::FSubscribeUserCache::Put(
                        Self->Gs2->Cache,
                        Request->GetNamespaceName(), CacheOwnerSnapshotUserId, Request->GetCategoryName(), TOptional<FString>(), Item->GetTargetUserId(),
                        CacheOwnerSnapshotTimeOffset, Item
                    );
                }
            }
            if (Range)
            {
            }
            RangeIteratorOpt = Range->CreateIterator();
            bLast = true;
            if (bLast) {
                Self->Gs2->Cache->SetListCached(
                    Gs2::Ranking::Model::FSubscribeUser::TypeName,
                    ListParentKey
                );
            }
        }

        bEnd = bLast && !*RangeIteratorOpt;
        return *this;
    }

    FDescribeSubscribesByCategoryNameIterator::FIterator FDescribeSubscribesByCategoryNameIterator::OneBeforeBegin()
    {
        return FIterator::OneBeforeBeginOf(this->AsShared());
    }

    FDescribeSubscribesByCategoryNameIterator::FIterator FDescribeSubscribesByCategoryNameIterator::begin()
    {
        return FIterator::BeginOf(this->AsShared());
    }

    FDescribeSubscribesByCategoryNameIterator::FIterator FDescribeSubscribesByCategoryNameIterator::end()
    {
        return FIterator::EndOf(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif
