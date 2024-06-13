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

#include "Matchmaking/Domain/Iterator/DescribeJoinedSeasonGatheringsByUserIdIterator.h"
#include "Matchmaking/Domain/Model/JoinedSeasonGathering.h"
#include "Matchmaking/Domain/Model/Season.h"

#include "Core/Domain/Gs2.h"

namespace Gs2::Matchmaking::Domain::Iterator
{

    FDescribeJoinedSeasonGatheringsByUserIdIterator::FDescribeJoinedSeasonGatheringsByUserIdIterator(
        const TSharedPtr<Core::Domain::FGs2> Gs2,
        const Gs2::Matchmaking::FGs2MatchmakingRestClientPtr Client,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId,
        const TOptional<FString> SeasonName,
        const TOptional<FString> TimeOffsetToken
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Client(Client),
        NamespaceName(NamespaceName),
        UserId(UserId),
        SeasonName(SeasonName),
        TimeOffsetToken(TimeOffsetToken)
    {
    }

    FDescribeJoinedSeasonGatheringsByUserIdIterator::FDescribeJoinedSeasonGatheringsByUserIdIterator(
        const FDescribeJoinedSeasonGatheringsByUserIdIterator& From
    ):
        Gs2(From.Gs2),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        UserId(From.UserId),
        SeasonName(From.SeasonName),
        TimeOffsetToken(From.TimeOffsetToken)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FDescribeJoinedSeasonGatheringsByUserIdIterator::FIteratorNextTask::Action(TSharedPtr<TSharedPtr<Gs2::Matchmaking::Model::FJoinedSeasonGathering>> Result)
    {
        ++Iterator;
        *Result = Iterator->Current();
        return Iterator.Error();
    }

    FDescribeJoinedSeasonGatheringsByUserIdIterator::FIterator::FIterator(
        const TSharedRef<FDescribeJoinedSeasonGatheringsByUserIdIterator> Iterable,
        FOneBeforeBegin
    ) :
        Self(Iterable),
        bLast(false),
        bEnd(false),
        PageToken(TOptional<FString>()),
        FetchSize(TOptional<int32>())
    {
    }

    FDescribeJoinedSeasonGatheringsByUserIdIterator::FIterator& FDescribeJoinedSeasonGatheringsByUserIdIterator::FIterator::operator++()
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
                Self->UserId,
                Self->SeasonName,
                TOptional<int64>(),
                "JoinedSeasonGathering"
            );

            if (!RangeIteratorOpt)
            {
                Range = Self->Gs2->Cache->TryGetList<Gs2::Matchmaking::Model::FJoinedSeasonGathering>(ListParentKey);

                if (Range)
                {
                    bLast = true;
                    RangeIteratorOpt = Range->CreateIterator();
                    PageToken = TOptional<FString>();
                    bEnd = !static_cast<bool>(*RangeIteratorOpt) && bLast;
                    return *this;
                }
            }

            const auto Future = Self->Client->DescribeJoinedSeasonGatheringsByUserId(
                MakeShared<Gs2::Matchmaking::Request::FDescribeJoinedSeasonGatheringsByUserIdRequest>()
                    ->WithNamespaceName(Self->NamespaceName)
                    ->WithUserId(Self->UserId)
                    ->WithSeasonName(Self->SeasonName)
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
                    Gs2::Matchmaking::Model::FJoinedSeasonGathering::TypeName,
                    ListParentKey,
                    Gs2::Matchmaking::Domain::Model::FJoinedSeasonGatheringDomain::CreateCacheKey(
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
                    Gs2::Matchmaking::Model::FJoinedSeasonGathering::TypeName,
                    ListParentKey
                );
            }
        }

        bEnd = bLast && !*RangeIteratorOpt;
        return *this;
    }

    FDescribeJoinedSeasonGatheringsByUserIdIterator::FIterator FDescribeJoinedSeasonGatheringsByUserIdIterator::OneBeforeBegin()
    {
        return FIterator::OneBeforeBeginOf(this->AsShared());
    }

    FDescribeJoinedSeasonGatheringsByUserIdIterator::FIterator FDescribeJoinedSeasonGatheringsByUserIdIterator::begin()
    {
        return FIterator::BeginOf(this->AsShared());
    }

    FDescribeJoinedSeasonGatheringsByUserIdIterator::FIterator FDescribeJoinedSeasonGatheringsByUserIdIterator::end()
    {
        return FIterator::EndOf(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

