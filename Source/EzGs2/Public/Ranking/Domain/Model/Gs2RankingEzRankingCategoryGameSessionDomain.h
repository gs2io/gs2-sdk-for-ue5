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

#pragma once

#include "CoreMinimal.h"
#include "Ranking/Domain/Model/RankingCategoryAccessToken.h"
#include "Ranking/Model/Gs2RankingEzCategoryModel.h"
#include "Ranking/Model/Gs2RankingEzGlobalRankingSetting.h"
#include "Ranking/Model/Gs2RankingEzScope.h"
#include "Ranking/Model/Gs2RankingEzScore.h"
#include "Ranking/Model/Gs2RankingEzRanking.h"
#include "Ranking/Model/Gs2RankingEzSubscribeUser.h"
#include "Gs2RankingEzSubscribeUserGameSessionDomain.h"
#include "Ranking/Domain/Iterator/Gs2RankingEzDescribeSubscribesByCategoryNameIterator.h"
#include "Gs2RankingEzRankingGameSessionDomain.h"
#include "Ranking/Domain/Iterator/Gs2RankingEzDescribeRankingsIterator.h"
#include "Gs2RankingEzRankingCategoryGameSessionDomain.h"
#include "Util/Net/GameSession.h"
#include "Util/Net/Gs2Connection.h"

namespace Gs2::UE5::Ranking::Domain::Model
{

    class EZGS2_API FEzRankingCategoryGameSessionDomain final :
        public TSharedFromThis<FEzRankingCategoryGameSessionDomain>
    {
        Gs2::Ranking::Domain::Model::FRankingCategoryAccessTokenDomainPtr Domain;
        Gs2::UE5::Util::FGameSessionPtr GameSession;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:
        TOptional<FString> NextPageToken() const;
        TOptional<bool> Processing() const;
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;
        TOptional<FString> CategoryName() const;
        TOptional<FString> AdditionalScopeName() const;

        FEzRankingCategoryGameSessionDomain(
            Gs2::Ranking::Domain::Model::FRankingCategoryAccessTokenDomainPtr Domain,
            Gs2::UE5::Util::FGameSessionPtr GameSession,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

        class FSubscribeTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Ranking::Domain::Model::FEzSubscribeUserGameSessionDomain>,
            public TSharedFromThis<FSubscribeTask>
        {
            TSharedPtr<FEzRankingCategoryGameSessionDomain> Self;
            FString TargetUserId;

        public:
            explicit FSubscribeTask(
                TSharedPtr<FEzRankingCategoryGameSessionDomain> Self,
                FString TargetUserId
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Ranking::Domain::Model::FEzSubscribeUserGameSessionDomain>> Result
            ) override;
        };
        friend FSubscribeTask;

        TSharedPtr<FAsyncTask<FSubscribeTask>> Subscribe(
            FString TargetUserId
        );

        class FPutScoreTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Ranking::Domain::Model::FEzScoreGameSessionDomain>,
            public TSharedFromThis<FPutScoreTask>
        {
            TSharedPtr<FEzRankingCategoryGameSessionDomain> Self;
            int64 Score;
            TOptional<FString> Metadata;

        public:
            explicit FPutScoreTask(
                TSharedPtr<FEzRankingCategoryGameSessionDomain> Self,
                int64 Score,
                TOptional<FString> Metadata = TOptional<FString>()
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Ranking::Domain::Model::FEzScoreGameSessionDomain>> Result
            ) override;
        };
        friend FPutScoreTask;

        TSharedPtr<FAsyncTask<FPutScoreTask>> PutScore(
            int64 Score,
            TOptional<FString> Metadata = TOptional<FString>()
        );

        Gs2::UE5::Ranking::Domain::Iterator::FEzDescribeSubscribesByCategoryNameIteratorPtr SubscribeUsers(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeSubscribeUsers(TFunction<void()> Callback);

        void UnsubscribeSubscribeUsers(Gs2::Core::Domain::CallbackID CallbackId);

        Gs2::UE5::Ranking::Domain::Model::FEzSubscribeUserGameSessionDomainPtr SubscribeUser(
            const FString TargetUserId
        ) const;

        Gs2::UE5::Ranking::Domain::Iterator::FEzDescribeRankingsIteratorPtr Rankings(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeRankings(TFunction<void()> Callback);

        void UnsubscribeRankings(Gs2::Core::Domain::CallbackID CallbackId);

        Gs2::UE5::Ranking::Domain::Model::FEzRankingGameSessionDomainPtr Ranking(
            const TOptional<FString> ScorerUserId = TOptional<FString>(),
            const TOptional<int64> Index = TOptional<int64>()
        ) const;

    };
    typedef TSharedPtr<FEzRankingCategoryGameSessionDomain> FEzRankingCategoryGameSessionDomainPtr;
}
