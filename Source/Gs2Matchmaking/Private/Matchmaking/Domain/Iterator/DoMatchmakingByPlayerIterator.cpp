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

#include "Matchmaking/Domain/Iterator/DoMatchmakingByPlayerIterator.h"
#include "Matchmaking/Domain/Model/Gathering.h"
#include "Matchmaking/Domain/Model/User.h"

namespace Gs2::Matchmaking::Domain::Iterator
{

    FDoMatchmakingByPlayerIterator::FDoMatchmakingByPlayerIterator(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Matchmaking::FGs2MatchmakingRestClientPtr Client,
        const TOptional<FString> NamespaceName,
        const Gs2::Matchmaking::Model::FPlayerPtr Player
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        Client(Client),
        NamespaceName(NamespaceName),
        Player(Player)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FDoMatchmakingByPlayerIterator::FIteratorNextTask::Action(TSharedPtr<TSharedPtr<Gs2::Matchmaking::Model::FGathering>> Result)
    {
        ++Iterator;
        *Result = Iterator->Current();
        return Iterator.Error();
    }

    FDoMatchmakingByPlayerIterator::FIterator::FIterator(
        const TSharedRef<FDoMatchmakingByPlayerIterator> Iterable,
        FOneBeforeBegin
    ) :
        Self(Iterable),
        bLast(false),
        bEnd(false),
        MatchmakingContextToken(TOptional<FString>()),
        FetchSize(TOptional<int32>())
    {
    }

    FDoMatchmakingByPlayerIterator::FIterator& FDoMatchmakingByPlayerIterator::FIterator::operator++()
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
            const auto Future = Self->Client->DoMatchmakingByPlayer(
                MakeShared<Gs2::Matchmaking::Request::FDoMatchmakingByPlayerRequest>()
                    ->WithNamespaceName(Self->NamespaceName)
                    ->WithPlayer(Self->Player)
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
            auto Arr = MakeShared<TArray<Gs2::Matchmaking::Model::FGatheringPtr>>();
            Arr->Add(R->GetItem());
            Range = Arr;
            RangeIteratorOpt = Range->CreateIterator();
            MatchmakingContextToken = R->GetMatchmakingContextToken();
            bLast = !MatchmakingContextToken.IsSet();
            Self->Cache->ClearListCache(
                Gs2::Matchmaking::Model::FGathering::TypeName,
                Gs2::Matchmaking::Domain::Model::FUserDomain::CreateCacheParentKey(
                Self->NamespaceName,
                TOptional<FString>("Singleton"),
                "Gathering"
            )
            );
        }

        bEnd = bLast && !*RangeIteratorOpt;
        return *this;
    }

    FDoMatchmakingByPlayerIterator::FIterator FDoMatchmakingByPlayerIterator::OneBeforeBegin()
    {
        return FIterator::OneBeforeBeginOf(this->AsShared());
    }

    FDoMatchmakingByPlayerIterator::FIterator FDoMatchmakingByPlayerIterator::begin()
    {
        return FIterator::BeginOf(this->AsShared());
    }

    FDoMatchmakingByPlayerIterator::FIterator FDoMatchmakingByPlayerIterator::end()
    {
        return FIterator::EndOf(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

