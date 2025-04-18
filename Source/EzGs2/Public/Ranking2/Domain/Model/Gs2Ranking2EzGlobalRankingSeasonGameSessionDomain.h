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
#include "Ranking2/Domain/Model/GlobalRankingSeasonAccessToken.h"
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
#include "Gs2Ranking2EzGlobalRankingScoreGameSessionDomain.h"
#include "Ranking2/Domain/Iterator/Gs2Ranking2EzDescribeGlobalRankingScoresIterator.h"
#include "Gs2Ranking2EzGlobalRankingDataGameSessionDomain.h"
#include "Ranking2/Domain/Iterator/Gs2Ranking2EzDescribeGlobalRankingsIterator.h"
#include "Gs2Ranking2EzGlobalRankingReceivedRewardGameSessionDomain.h"
#include "Ranking2/Domain/Iterator/Gs2Ranking2EzDescribeGlobalRankingReceivedRewardsIterator.h"
#include "Gs2Ranking2EzGlobalRankingSeasonGameSessionDomain.h"
#include "Util/Net/GameSession.h"
#include "Util/Net/Gs2Connection.h"

namespace Gs2::UE5::Ranking2::Domain::Model
{

    class EZGS2_API FEzGlobalRankingSeasonGameSessionDomain final :
        public TSharedFromThis<FEzGlobalRankingSeasonGameSessionDomain>
    {
        Gs2::Ranking2::Domain::Model::FGlobalRankingSeasonAccessTokenDomainPtr Domain;
        Gs2::UE5::Util::IGameSessionPtr GameSession;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:
        TOptional<FString> NextPageToken() const;
        TOptional<FString> NamespaceName() const;
        TOptional<FString> RankingName() const;
        TOptional<int64> Season() const;
        TOptional<FString> UserId() const;

        FEzGlobalRankingSeasonGameSessionDomain(
            Gs2::Ranking2::Domain::Model::FGlobalRankingSeasonAccessTokenDomainPtr Domain,
            Gs2::UE5::Util::IGameSessionPtr GameSession,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

        class EZGS2_API FPutGlobalRankingTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Ranking2::Domain::Model::FEzGlobalRankingScoreGameSessionDomain>,
            public TSharedFromThis<FPutGlobalRankingTask>
        {
            TSharedPtr<FEzGlobalRankingSeasonGameSessionDomain> Self;
            int64 Score;
            TOptional<FString> Metadata;

        public:
            explicit FPutGlobalRankingTask(
                TSharedPtr<FEzGlobalRankingSeasonGameSessionDomain> Self,
                int64 Score,
                TOptional<FString> Metadata = TOptional<FString>()
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Ranking2::Domain::Model::FEzGlobalRankingScoreGameSessionDomain>> Result
            ) override;
        };
        friend FPutGlobalRankingTask;

        TSharedPtr<FAsyncTask<FPutGlobalRankingTask>> PutGlobalRanking(
            int64 Score,
            TOptional<FString> Metadata = TOptional<FString>()
        );

        Gs2::UE5::Ranking2::Domain::Iterator::FEzDescribeGlobalRankingScoresIteratorPtr GlobalRankingScores(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeGlobalRankingScores(TFunction<void()> Callback);

        void UnsubscribeGlobalRankingScores(Gs2::Core::Domain::CallbackID CallbackId);

        Gs2::UE5::Ranking2::Domain::Model::FEzGlobalRankingScoreGameSessionDomainPtr GlobalRankingScore(
        ) const;

        Gs2::UE5::Ranking2::Domain::Iterator::FEzDescribeGlobalRankingsIteratorPtr GlobalRankings(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeGlobalRankings(TFunction<void()> Callback);

        void UnsubscribeGlobalRankings(Gs2::Core::Domain::CallbackID CallbackId);

        Gs2::UE5::Ranking2::Domain::Model::FEzGlobalRankingDataGameSessionDomainPtr GlobalRankingData(
        ) const;

        Gs2::UE5::Ranking2::Domain::Iterator::FEzDescribeGlobalRankingReceivedRewardsIteratorPtr GlobalRankingReceivedRewards(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeGlobalRankingReceivedRewards(TFunction<void()> Callback);

        void UnsubscribeGlobalRankingReceivedRewards(Gs2::Core::Domain::CallbackID CallbackId);

        Gs2::UE5::Ranking2::Domain::Model::FEzGlobalRankingReceivedRewardGameSessionDomainPtr GlobalRankingReceivedReward(
        ) const;

    };
    typedef TSharedPtr<FEzGlobalRankingSeasonGameSessionDomain> FEzGlobalRankingSeasonGameSessionDomainPtr;
}
