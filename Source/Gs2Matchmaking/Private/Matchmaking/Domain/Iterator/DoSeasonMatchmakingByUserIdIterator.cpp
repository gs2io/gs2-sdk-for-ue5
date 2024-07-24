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

#include "Matchmaking/Domain/Iterator/DoSeasonMatchmakingByUserIdIterator.h"
#include "Matchmaking/Domain/Model/SeasonGathering.h"
#include "Matchmaking/Domain/Model/Season.h"

#include "Core/Domain/Gs2.h"

namespace Gs2::Matchmaking::Domain::Iterator
{

    FDoSeasonMatchmakingByUserIdIterator::FDoSeasonMatchmakingByUserIdIterator(
        const TSharedPtr<Core::Domain::FGs2> Gs2,
        const Gs2::Matchmaking::FGs2MatchmakingRestClientPtr Client,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> SeasonName,
        const TOptional<FString> UserId,
        const TOptional<FString> TimeOffsetToken
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Client(Client),
        NamespaceName(NamespaceName),
        SeasonName(SeasonName),
        UserId(UserId),
        TimeOffsetToken(TimeOffsetToken)
    {
    }

    FDoSeasonMatchmakingByUserIdIterator::FDoSeasonMatchmakingByUserIdIterator(
        const FDoSeasonMatchmakingByUserIdIterator& From
    ):
        Gs2(From.Gs2),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        SeasonName(From.SeasonName),
        UserId(From.UserId),
        TimeOffsetToken(From.TimeOffsetToken)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FDoSeasonMatchmakingByUserIdIterator::FIteratorNextTask::Action(TSharedPtr<TSharedPtr<Gs2::Matchmaking::Model::FSeasonGathering>> Result)
    {
        ++Iterator;
        *Result = Iterator->Current();
        return Iterator.Error();
    }

    FDoSeasonMatchmakingByUserIdIterator::FIterator::FIterator(
        const TSharedRef<FDoSeasonMatchmakingByUserIdIterator> Iterable,
        FOneBeforeBegin
    ) :
        Self(Iterable),
        bLast(false),
        bEnd(false),
        MatchmakingContextToken(TOptional<FString>()),
        FetchSize(TOptional<int32>())
    {
    }

    FDoSeasonMatchmakingByUserIdIterator::FIterator& FDoSeasonMatchmakingByUserIdIterator::FIterator::operator++()
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
                TOptional<int64>(),
                "SeasonGathering"
            );

            if (!RangeIteratorOpt)
            {
                Range = Self->Gs2->Cache->TryGetList<Gs2::Matchmaking::Model::FSeasonGathering>(ListParentKey);

                if (Range)
                {
                    bLast = true;
                    RangeIteratorOpt = Range->CreateIterator();
                    bEnd = !static_cast<bool>(*RangeIteratorOpt) && bLast;
                    return *this;
                }
            }

            const auto Future = Self->Client->DoSeasonMatchmakingByUserId(
                MakeShared<Gs2::Matchmaking::Request::FDoSeasonMatchmakingByUserIdRequest>()
                    ->WithNamespaceName(Self->NamespaceName)
                    ->WithSeasonName(Self->SeasonName)
                    ->WithUserId(Self->UserId)
                    ->WithMatchmakingContextToken(MatchmakingContextToken)
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
            auto Arr = MakeShared<TArray<Gs2::Matchmaking::Model::FSeasonGatheringPtr>>();
            Arr->Add(R->GetItem());
            Range = Arr;
            auto Item = R->GetItem();
            RangeIteratorOpt = Range->CreateIterator();
            MatchmakingContextToken = R->GetMatchmakingContextToken();
            bLast = !MatchmakingContextToken.IsSet();
        }

        bEnd = bLast && !*RangeIteratorOpt;
        return *this;
    }

    FDoSeasonMatchmakingByUserIdIterator::FIterator FDoSeasonMatchmakingByUserIdIterator::OneBeforeBegin()
    {
        return FIterator::OneBeforeBeginOf(this->AsShared());
    }

    FDoSeasonMatchmakingByUserIdIterator::FIterator FDoSeasonMatchmakingByUserIdIterator::begin()
    {
        return FIterator::BeginOf(this->AsShared());
    }

    FDoSeasonMatchmakingByUserIdIterator::FIterator FDoSeasonMatchmakingByUserIdIterator::end()
    {
        return FIterator::EndOf(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

