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
#include "Ranking2/Domain/Model/SubscribeRankingSeasonAccessToken.h"
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
#include "Gs2Ranking2EzSubscribeRankingScoreGameSessionDomain.h"
#include "Ranking2/Domain/Iterator/Gs2Ranking2EzDescribeSubscribeRankingScoresIterator.h"
#include "Gs2Ranking2EzSubscribeRankingDataGameSessionDomain.h"
#include "Ranking2/Domain/Iterator/Gs2Ranking2EzDescribeSubscribeRankingsIterator.h"
#include "Gs2Ranking2EzSubscribeRankingSeasonGameSessionDomain.h"
#include "Util/Net/GameSession.h"
#include "Util/Net/Gs2Connection.h"

namespace Gs2::UE5::Ranking2::Domain::Model
{

    class EZGS2_API FEzSubscribeRankingSeasonGameSessionDomain final :
        public TSharedFromThis<FEzSubscribeRankingSeasonGameSessionDomain>
    {
        Gs2::Ranking2::Domain::Model::FSubscribeRankingSeasonAccessTokenDomainPtr Domain;
        Gs2::UE5::Util::IGameSessionPtr GameSession;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:
        TOptional<FString> NextPageToken() const;
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;
        TOptional<FString> RankingName() const;
        TOptional<int64> Season() const;

        FEzSubscribeRankingSeasonGameSessionDomain(
            Gs2::Ranking2::Domain::Model::FSubscribeRankingSeasonAccessTokenDomainPtr Domain,
            Gs2::UE5::Util::IGameSessionPtr GameSession,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

        class EZGS2_API FPutSubscribeRankingTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Ranking2::Domain::Model::FEzSubscribeRankingScoreGameSessionDomain>,
            public TSharedFromThis<FPutSubscribeRankingTask>
        {
            TSharedPtr<FEzSubscribeRankingSeasonGameSessionDomain> Self;
            int64 Score;
            TOptional<FString> Metadata;

        public:
            explicit FPutSubscribeRankingTask(
                TSharedPtr<FEzSubscribeRankingSeasonGameSessionDomain> Self,
                int64 Score,
                TOptional<FString> Metadata = TOptional<FString>()
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Ranking2::Domain::Model::FEzSubscribeRankingScoreGameSessionDomain>> Result
            ) override;
        };
        friend FPutSubscribeRankingTask;

        TSharedPtr<FAsyncTask<FPutSubscribeRankingTask>> PutSubscribeRanking(
            int64 Score,
            TOptional<FString> Metadata = TOptional<FString>()
        );

        Gs2::UE5::Ranking2::Domain::Iterator::FEzDescribeSubscribeRankingScoresIteratorPtr SubscribeRankingScores(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeSubscribeRankingScores(TFunction<void()> Callback);

        void UnsubscribeSubscribeRankingScores(Gs2::Core::Domain::CallbackID CallbackId);

        Gs2::UE5::Ranking2::Domain::Model::FEzSubscribeRankingScoreGameSessionDomainPtr SubscribeRankingScore(
        ) const;

        Gs2::UE5::Ranking2::Domain::Iterator::FEzDescribeSubscribeRankingsIteratorPtr SubscribeRankings(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeSubscribeRankings(TFunction<void()> Callback);

        void UnsubscribeSubscribeRankings(Gs2::Core::Domain::CallbackID CallbackId);

        Gs2::UE5::Ranking2::Domain::Model::FEzSubscribeRankingDataGameSessionDomainPtr SubscribeRankingData(
            const FString ScorerUserId
        ) const;

    };
    typedef TSharedPtr<FEzSubscribeRankingSeasonGameSessionDomain> FEzSubscribeRankingSeasonGameSessionDomainPtr;
}
