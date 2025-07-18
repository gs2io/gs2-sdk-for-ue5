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
#include "Ranking2/Domain/Model/ClusterRankingSeasonAccessToken.h"
#include "Ranking2/Model/Gs2Ranking2EzGlobalRankingData.h"
#include "Ranking2/Model/Gs2Ranking2EzGlobalRankingModel.h"
#include "Ranking2/Model/Gs2Ranking2EzGlobalRankingReceivedReward.h"
#include "Ranking2/Model/Gs2Ranking2EzGlobalRankingScore.h"
#include "Ranking2/Model/Gs2Ranking2EzClusterRankingData.h"
#include "Ranking2/Model/Gs2Ranking2EzClusterRankingModel.h"
#include "Ranking2/Model/Gs2Ranking2EzClusterRankingReceivedReward.h"
#include "Ranking2/Model/Gs2Ranking2EzClusterRankingScore.h"
#include "Ranking2/Model/Gs2Ranking2EzSubscribeRankingData.h"
#include "Ranking2/Model/Gs2Ranking2EzSubscribeRankingModel.h"
#include "Ranking2/Model/Gs2Ranking2EzSubscribeRankingScore.h"
#include "Ranking2/Model/Gs2Ranking2EzRankingReward.h"
#include "Ranking2/Model/Gs2Ranking2EzAcquireAction.h"
#include "Ranking2/Model/Gs2Ranking2EzConfig.h"
#include "Ranking2/Model/Gs2Ranking2EzSubscribeUser.h"
#include "Ranking2/Model/Gs2Ranking2EzVerifyActionResult.h"
#include "Ranking2/Model/Gs2Ranking2EzConsumeActionResult.h"
#include "Ranking2/Model/Gs2Ranking2EzAcquireActionResult.h"
#include "Ranking2/Model/Gs2Ranking2EzTransactionResult.h"
#include "Ranking2/Domain/Iterator/Gs2Ranking2EzDescribeClusterRankingsIterator.h"
#include "Gs2Ranking2EzClusterRankingReceivedRewardGameSessionDomain.h"
#include "Ranking2/Domain/Iterator/Gs2Ranking2EzDescribeClusterRankingReceivedRewardsIterator.h"
#include "Gs2Ranking2EzClusterRankingScoreGameSessionDomain.h"
#include "Ranking2/Domain/Iterator/Gs2Ranking2EzDescribeClusterRankingScoresIterator.h"
#include "Gs2Ranking2EzClusterRankingSeasonGameSessionDomain.h"
#include "Core/EzTransactionGameSessionDomain.h"
#include "Util/Net/GameSession.h"
#include "Util/Net/Gs2Connection.h"

namespace Gs2::UE5::Ranking2::Domain::Model
{

    class EZGS2_API FEzClusterRankingSeasonGameSessionDomain final :
        public TSharedFromThis<FEzClusterRankingSeasonGameSessionDomain>
    {
        Gs2::Ranking2::Domain::Model::FClusterRankingSeasonAccessTokenDomainPtr Domain;
        Gs2::UE5::Util::IGameSessionPtr GameSession;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:
        TOptional<FString> NextPageToken() const;
        TOptional<FString> NamespaceName() const;
        TOptional<FString> RankingName() const;
        TOptional<FString> ClusterName() const;
        TOptional<int64> Season() const;
        TOptional<FString> UserId() const;

        FEzClusterRankingSeasonGameSessionDomain(
            Gs2::Ranking2::Domain::Model::FClusterRankingSeasonAccessTokenDomainPtr Domain,
            Gs2::UE5::Util::IGameSessionPtr GameSession,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

        class EZGS2_API FGetClusterRankingRankTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Ranking2::Domain::Model::FEzClusterRankingDataGameSessionDomain>,
            public TSharedFromThis<FGetClusterRankingRankTask>
        {
            TSharedPtr<FEzClusterRankingSeasonGameSessionDomain> Self;

        public:
            explicit FGetClusterRankingRankTask(
                TSharedPtr<FEzClusterRankingSeasonGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Ranking2::Domain::Model::FEzClusterRankingDataGameSessionDomain>> Result
            ) override;
        };
        friend FGetClusterRankingRankTask;

        TSharedPtr<FAsyncTask<FGetClusterRankingRankTask>> GetClusterRankingRank(
        );

        class EZGS2_API FPutClusterRankingTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Ranking2::Domain::Model::FEzClusterRankingScoreGameSessionDomain>,
            public TSharedFromThis<FPutClusterRankingTask>
        {
            TSharedPtr<FEzClusterRankingSeasonGameSessionDomain> Self;
            int64 Score;
            TOptional<FString> Metadata;

        public:
            explicit FPutClusterRankingTask(
                TSharedPtr<FEzClusterRankingSeasonGameSessionDomain> Self,
                int64 Score,
                TOptional<FString> Metadata = TOptional<FString>()
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Ranking2::Domain::Model::FEzClusterRankingScoreGameSessionDomain>> Result
            ) override;
        };
        friend FPutClusterRankingTask;

        TSharedPtr<FAsyncTask<FPutClusterRankingTask>> PutClusterRanking(
            int64 Score,
            TOptional<FString> Metadata = TOptional<FString>()
        );

        Gs2::UE5::Ranking2::Domain::Iterator::FEzDescribeClusterRankingsIteratorPtr ClusterRankings(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeClusterRankings(TFunction<void()> Callback);

        void UnsubscribeClusterRankings(Gs2::Core::Domain::CallbackID CallbackId);

        Gs2::UE5::Ranking2::Domain::Model::FEzClusterRankingDataGameSessionDomainPtr ClusterRankingData(
            const FString ScorerUserId
        ) const;

        Gs2::UE5::Ranking2::Domain::Iterator::FEzDescribeClusterRankingReceivedRewardsIteratorPtr ClusterRankingReceivedRewards(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeClusterRankingReceivedRewards(TFunction<void()> Callback);

        void UnsubscribeClusterRankingReceivedRewards(Gs2::Core::Domain::CallbackID CallbackId);

        Gs2::UE5::Ranking2::Domain::Model::FEzClusterRankingReceivedRewardGameSessionDomainPtr ClusterRankingReceivedReward(
        ) const;

        Gs2::UE5::Ranking2::Domain::Iterator::FEzDescribeClusterRankingScoresIteratorPtr ClusterRankingScores(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeClusterRankingScores(TFunction<void()> Callback);

        void UnsubscribeClusterRankingScores(Gs2::Core::Domain::CallbackID CallbackId);

        Gs2::UE5::Ranking2::Domain::Model::FEzClusterRankingScoreGameSessionDomainPtr ClusterRankingScore(
        ) const;

    };
    typedef TSharedPtr<FEzClusterRankingSeasonGameSessionDomain> FEzClusterRankingSeasonGameSessionDomainPtr;
}
