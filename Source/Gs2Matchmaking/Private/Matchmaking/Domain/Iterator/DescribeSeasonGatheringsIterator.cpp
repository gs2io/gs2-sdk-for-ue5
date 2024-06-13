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

#include "Matchmaking/Domain/Iterator/DescribeSeasonGatheringsIterator.h"
#include "Matchmaking/Domain/Model/SeasonGathering.h"
#include "Matchmaking/Domain/Model/Season.h"

#include "Core/Domain/Gs2.h"

namespace Gs2::Matchmaking::Domain::Iterator
{

    FDescribeSeasonGatheringsIterator::FDescribeSeasonGatheringsIterator(
        const TSharedPtr<Core::Domain::FGs2> Gs2,
        const Gs2::Matchmaking::FGs2MatchmakingRestClientPtr Client,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> SeasonName,
        const TOptional<int64> Season,
        const TOptional<int64> Tier
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Client(Client),
        NamespaceName(NamespaceName),
        SeasonName(SeasonName),
        Season(Season),
        Tier(Tier)
    {
    }

    FDescribeSeasonGatheringsIterator::FDescribeSeasonGatheringsIterator(
        const FDescribeSeasonGatheringsIterator& From
    ):
        Gs2(From.Gs2),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        SeasonName(From.SeasonName),
        Season(From.Season),
        Tier(From.Tier)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FDescribeSeasonGatheringsIterator::FIteratorNextTask::Action(TSharedPtr<TSharedPtr<Gs2::Matchmaking::Model::FSeasonGathering>> Result)
    {
        ++Iterator;
        *Result = Iterator->Current();
        return Iterator.Error();
    }

    FDescribeSeasonGatheringsIterator::FIterator::FIterator(
        const TSharedRef<FDescribeSeasonGatheringsIterator> Iterable,
        FOneBeforeBegin
    ) :
        Self(Iterable),
        bLast(false),
        bEnd(false),
        PageToken(TOptional<FString>()),
        FetchSize(TOptional<int32>())
    {
    }

    FDescribeSeasonGatheringsIterator::FIterator& FDescribeSeasonGatheringsIterator::FIterator::operator++()
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
            const auto ListParentKey = Gs2::Matchmaking::Domain::Model::FSeasonDomain::CreateCacheParentKey(
                Self->NamespaceName,
                TOptional<FString>("Singleton"),
                Self->SeasonName,
                Self->Season,
                "SeasonGathering"
            );

            if (!RangeIteratorOpt)
            {
                Range = Self->Gs2->Cache->TryGetList<Gs2::Matchmaking::Model::FSeasonGathering>(ListParentKey);

                if (Range)
                {
                    Range->RemoveAll([this](const Gs2::Matchmaking::Model::FSeasonGatheringPtr& Item) { return Self->Tier && Item->GetTier() != Self->Tier; });
                    bLast = true;
                    RangeIteratorOpt = Range->CreateIterator();
                    PageToken = TOptional<FString>();
                    bEnd = !static_cast<bool>(*RangeIteratorOpt) && bLast;
                    return *this;
                }
            }

            const auto Future = Self->Client->DescribeSeasonGatherings(
                MakeShared<Gs2::Matchmaking::Request::FDescribeSeasonGatheringsRequest>()
                    ->WithNamespaceName(Self->NamespaceName)
                    ->WithSeasonName(Self->SeasonName)
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
                    Gs2::Matchmaking::Model::FSeasonGathering::TypeName,
                    ListParentKey,
                    Gs2::Matchmaking::Domain::Model::FSeasonGatheringDomain::CreateCacheKey(
                        FString::FromInt(*Item->GetTier()),
                        Item->GetName()
                    ),
                    Item,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            if (Range)
            {
                Range->RemoveAll([this](const Gs2::Matchmaking::Model::FSeasonGatheringPtr& Item) { return Self->Tier && Item->GetTier() != Self->Tier; });
            }
            RangeIteratorOpt = Range->CreateIterator();
            PageToken = R->GetNextPageToken();
            bLast = !PageToken.IsSet();
            if (bLast) {
                Self->Gs2->Cache->SetListCached(
                    Gs2::Matchmaking::Model::FSeasonGathering::TypeName,
                    ListParentKey
                );
            }
        }

        bEnd = bLast && !*RangeIteratorOpt;
        return *this;
    }

    FDescribeSeasonGatheringsIterator::FIterator FDescribeSeasonGatheringsIterator::OneBeforeBegin()
    {
        return FIterator::OneBeforeBeginOf(this->AsShared());
    }

    FDescribeSeasonGatheringsIterator::FIterator FDescribeSeasonGatheringsIterator::begin()
    {
        return FIterator::BeginOf(this->AsShared());
    }

    FDescribeSeasonGatheringsIterator::FIterator FDescribeSeasonGatheringsIterator::end()
    {
        return FIterator::EndOf(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

