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

// ReSharper disable CppUnusedIncludeDirective

#pragma once

#include "Core/Domain/Gs2Core.h"
#include "Auth/Gs2Auth.h"
#include "Matchmaking/Gs2Matchmaking.h"

namespace Gs2::Matchmaking::Domain::Iterator
{

    class FDoMatchmakingByUserIdIteratorLoadTask;

    class GS2MATCHMAKING_API FDoMatchmakingByUserIdIterator :
        public Gs2::Core::Domain::Model::TGs2Iterator<Gs2::Matchmaking::Model::FGathering, FDoMatchmakingByUserIdIteratorLoadTask>
    {
        const Core::Domain::FCacheDatabasePtr Cache;
        const Gs2::Matchmaking::FGs2MatchmakingRestClientPtr Client;

        friend FDoMatchmakingByUserIdIteratorLoadTask;
        virtual TSharedPtr<FAsyncTask<FDoMatchmakingByUserIdIteratorLoadTask>> Load() override;

public:
        const TOptional<FString> NamespaceName;
        const TOptional<FString> UserId;
        const Gs2::Matchmaking::Model::FPlayerPtr Player;
        TOptional<FString> MatchmakingContextToken;
        TOptional<int32> FetchSize;

        FDoMatchmakingByUserIdIterator(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Matchmaking::FGs2MatchmakingRestClientPtr Client,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> UserId,
            const Gs2::Matchmaking::Model::FPlayerPtr Player
        );

        class GS2MATCHMAKING_API IteratorImpl
        {
            friend FDoMatchmakingByUserIdIterator;

            TSharedPtr<FAsyncTask<Gs2::Matchmaking::Domain::Iterator::FDoMatchmakingByUserIdIterator::FNextTask>> Task;
            Gs2::Matchmaking::Model::FGatheringPtr Current;

        public:
            explicit IteratorImpl(
                const TSharedPtr<FAsyncTask<Gs2::Matchmaking::Domain::Iterator::FDoMatchmakingByUserIdIterator::FNextTask>> Task
            ): Task(Task)
            {

            }
            const Gs2::Matchmaking::Model::FGatheringPtr& operator*() const;
            Gs2::Matchmaking::Model::FGatheringPtr operator->();
            IteratorImpl& operator++();

            friend bool operator== (const IteratorImpl& a, const IteratorImpl& b)
            {
                if (a.Task == nullptr && b.Task == nullptr)
                {
                    return true;
                }
                if (a.Task == nullptr)
                {
                    return b.Current == nullptr;
                }
                if (b.Task == nullptr)
                {
                    return a.Current == nullptr;
                }
                return a.Current == b.Current;
            };
            friend bool operator!= (const IteratorImpl& a, const IteratorImpl& b)
            {
                return !operator==(a, b);
            };
        };

        IteratorImpl begin();
        IteratorImpl end();
    };
    typedef TSharedPtr<FDoMatchmakingByUserIdIterator> FDoMatchmakingByUserIdIteratorPtr;

    class FDoMatchmakingByUserIdIteratorLoadTask :
        public Gs2::Core::Util::TGs2Future<TArray<Gs2::Matchmaking::Model::FGatheringPtr>>,
        public TSharedFromThis<FDoMatchmakingByUserIdIteratorLoadTask>
    {
        TSharedPtr<FDoMatchmakingByUserIdIterator> Self;

    public:
        explicit FDoMatchmakingByUserIdIteratorLoadTask(
            TSharedPtr<FDoMatchmakingByUserIdIterator> Self
        ): Self(Self)
        {

        }

        virtual Gs2::Core::Model::FGs2ErrorPtr Action(
            TSharedPtr<TSharedPtr<TArray<Gs2::Matchmaking::Model::FGatheringPtr>>> Result
        ) override;
    };
}
