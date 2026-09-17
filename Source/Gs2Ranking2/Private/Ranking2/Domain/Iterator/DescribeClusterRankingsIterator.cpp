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

#include "Ranking2/Domain/Iterator/DescribeClusterRankingsIterator.h"
#include "Ranking2/Domain/Model/ClusterRankingData.h"
#include "Ranking2/Domain/Model/ClusterRankingSeason.h"

#include "Core/Domain/Gs2.h"
#include "Ranking2/Model/Cache/ClusterRankingData.h"

namespace Gs2::Ranking2::Domain::Iterator
{

    FDescribeClusterRankingsIterator::FDescribeClusterRankingsIterator(
        const TSharedPtr<Core::Domain::FGs2> Gs2,
        const Gs2::Ranking2::FGs2Ranking2RestClientPtr Client,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr AccessToken,
        const TOptional<FString> RankingName,
        const TOptional<FString> ClusterName,
        const TOptional<int64> Season
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Client(Client),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        RankingName(RankingName),
        ClusterName(ClusterName),
        Season(Season)
    {
    }

    FDescribeClusterRankingsIterator::FDescribeClusterRankingsIterator(
        const FDescribeClusterRankingsIterator& From
    ):
        Gs2(From.Gs2),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        AccessToken(From.AccessToken),
        RankingName(From.RankingName),
        ClusterName(From.ClusterName),
        Season(From.Season)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FDescribeClusterRankingsIterator::FIteratorNextTask::Action(TSharedPtr<TSharedPtr<Gs2::Ranking2::Model::FClusterRankingData>> Result)
    {
        ++Iterator;
        *Result = Iterator->Current();
        return Iterator.Error();
    }

    FDescribeClusterRankingsIterator::FIterator::FIterator(
        const TSharedRef<FDescribeClusterRankingsIterator> Iterable,
        FOneBeforeBegin
    ) :
        Self(Iterable),
        bLast(false),
        bEnd(false),
        PageToken(TOptional<FString>()),
        FetchSize(TOptional<int32>())
    {
    }

    FDescribeClusterRankingsIterator::FIterator& FDescribeClusterRankingsIterator::FIterator::operator++()
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
            const auto bUseCache = Self->Season.IsSet();
            const auto ListParentKey = Gs2::Ranking2::Model::Cache::FClusterRankingDataCache::CreateCacheParentKey(
                Self->NamespaceName,
                Self->RankingName,
                Self->ClusterName,
                Self->Season,
                Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>()
            );

            if (!RangeIteratorOpt && bUseCache)
            {
                Range = Self->Gs2->Cache->TryGetList<Gs2::Ranking2::Model::FClusterRankingData>(ListParentKey);

                if (Range)
                {
                    bLast = true;
                    RangeIteratorOpt = Range->CreateIterator();
                    PageToken = TOptional<FString>();
                    bEnd = !static_cast<bool>(*RangeIteratorOpt) && bLast;
                    return *this;
                }
            }

            const auto Request =
                MakeShared<Gs2::Ranking2::Request::FDescribeClusterRankingsRequest>()
                    ->WithContextStack(Self->Gs2->DefaultContextStack)
                    ->WithNamespaceName(Self->NamespaceName)
                    ->WithAccessToken(Self->AccessToken == nullptr ? TOptional<FString>() : Self->AccessToken->GetToken())
                    ->WithRankingName(Self->RankingName)
                    ->WithClusterName(Self->ClusterName)
                    ->WithSeason(Self->Season)
                    ->WithPageToken(PageToken)
                    ->WithLimit(FetchSize)
            ;
            const auto Future = Self->Client->DescribeClusterRankings(Request);
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
            Range = R->GetItems().IsValid() ? R->GetItems() : MakeShared<TArray<Gs2::Ranking2::Model::FClusterRankingDataPtr>>();
            const auto CacheOwnerSnapshotTimeOffset = Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>();
            const auto ResultModel = R;


            if (Range.IsValid())
            {
                for (const auto& Item : *Range)
                {
                    if (!Item.IsValid()) continue;
                    Gs2::Ranking2::Model::Cache::FClusterRankingDataCache::Put(
                        Self->Gs2->Cache,
                        Request->GetNamespaceName(), Request->GetRankingName(), Request->GetClusterName(), Item->GetSeason(), Item->GetUserId(),
                        CacheOwnerSnapshotTimeOffset, Item
                    );
                    if (!Request->GetSeason().IsSet())
                    {
                        Gs2::Ranking2::Model::Cache::FClusterRankingDataCache::Put(
                            Self->Gs2->Cache,
                            Request->GetNamespaceName(), Request->GetRankingName(), Request->GetClusterName(), TOptional<int64>(), Item->GetUserId(),
                            CacheOwnerSnapshotTimeOffset, Item
                        );
                    }
                }
            }
            if (Range)
            {
            }
            RangeIteratorOpt = Range->CreateIterator();
            PageToken = R->GetNextPageToken();
            bLast = !PageToken.IsSet();
            if (bUseCache && bLast) {
                Self->Gs2->Cache->SetListCached(
                    Gs2::Ranking2::Model::FClusterRankingData::TypeName,
                    ListParentKey
                );
            }
        }

        bEnd = bLast && !*RangeIteratorOpt;
        return *this;
    }

    FDescribeClusterRankingsIterator::FIterator FDescribeClusterRankingsIterator::OneBeforeBegin()
    {
        return FIterator::OneBeforeBeginOf(this->AsShared());
    }

    FDescribeClusterRankingsIterator::FIterator FDescribeClusterRankingsIterator::begin()
    {
        return FIterator::BeginOf(this->AsShared());
    }

    FDescribeClusterRankingsIterator::FIterator FDescribeClusterRankingsIterator::end()
    {
        return FIterator::EndOf(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif
