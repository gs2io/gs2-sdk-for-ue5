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

#include "Ranking2/Domain/Iterator/DescribeSubscribeRankingsIterator.h"
#include "Ranking2/Domain/Model/SubscribeRankingData.h"
#include "Ranking2/Domain/Model/SubscribeRankingSeason.h"

#include "Core/Domain/Gs2.h"

namespace Gs2::Ranking2::Domain::Iterator
{

    FDescribeSubscribeRankingsIterator::FDescribeSubscribeRankingsIterator(
        const TSharedPtr<Core::Domain::FGs2> Gs2,
        const Gs2::Ranking2::FGs2Ranking2RestClientPtr Client,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr AccessToken,
        const TOptional<FString> RankingName,
        const TOptional<int64> Season
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Client(Client),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        RankingName(RankingName),
        Season(Season)
    {
    }

    FDescribeSubscribeRankingsIterator::FDescribeSubscribeRankingsIterator(
        const FDescribeSubscribeRankingsIterator& From
    ):
        Gs2(From.Gs2),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        AccessToken(From.AccessToken),
        RankingName(From.RankingName),
        Season(From.Season)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FDescribeSubscribeRankingsIterator::FIteratorNextTask::Action(TSharedPtr<TSharedPtr<Gs2::Ranking2::Model::FSubscribeRankingData>> Result)
    {
        ++Iterator;
        *Result = Iterator->Current();
        return Iterator.Error();
    }

    FDescribeSubscribeRankingsIterator::FIterator::FIterator(
        const TSharedRef<FDescribeSubscribeRankingsIterator> Iterable,
        FOneBeforeBegin
    ) :
        Self(Iterable),
        bLast(false),
        bEnd(false),
        PageToken(TOptional<FString>()),
        FetchSize(TOptional<int32>())
    {
    }

    FDescribeSubscribeRankingsIterator::FIterator& FDescribeSubscribeRankingsIterator::FIterator::operator++()
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
            const auto ListParentKey = Gs2::Ranking2::Domain::Model::FSubscribeRankingSeasonDomain::CreateCacheParentKey(
                Self->NamespaceName,
                Self->RankingName,
                Self->Season,
                "SubscribeRankingData"
            );

            if (!RangeIteratorOpt)
            {
                Range = Self->Gs2->Cache->TryGetList<Gs2::Ranking2::Model::FSubscribeRankingData>(ListParentKey);

                if (Range)
                {
                    bLast = true;
                    RangeIteratorOpt = Range->CreateIterator();
                    PageToken = TOptional<FString>();
                    bEnd = !static_cast<bool>(*RangeIteratorOpt) && bLast;
                    return *this;
                }
            }

            const auto Future = Self->Client->DescribeSubscribeRankings(
                MakeShared<Gs2::Ranking2::Request::FDescribeSubscribeRankingsRequest>()
                    ->WithNamespaceName(Self->NamespaceName)
                    ->WithAccessToken(Self->AccessToken == nullptr ? TOptional<FString>() : Self->AccessToken->GetToken())
                    ->WithRankingName(Self->RankingName)
                    ->WithSeason(Self->Season)
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
                    Gs2::Ranking2::Model::FSubscribeRankingData::TypeName,
                    ListParentKey,
                    Gs2::Ranking2::Domain::Model::FSubscribeRankingDataDomain::CreateCacheKey(
                        Item->GetRankingName(),
                        Item->GetScorerUserId()
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
                    Gs2::Ranking2::Model::FSubscribeRankingData::TypeName,
                    ListParentKey
                );
            }
        }

        bEnd = bLast && !*RangeIteratorOpt;
        return *this;
    }

    FDescribeSubscribeRankingsIterator::FIterator FDescribeSubscribeRankingsIterator::OneBeforeBegin()
    {
        return FIterator::OneBeforeBeginOf(this->AsShared());
    }

    FDescribeSubscribeRankingsIterator::FIterator FDescribeSubscribeRankingsIterator::begin()
    {
        return FIterator::BeginOf(this->AsShared());
    }

    FDescribeSubscribeRankingsIterator::FIterator FDescribeSubscribeRankingsIterator::end()
    {
        return FIterator::EndOf(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

