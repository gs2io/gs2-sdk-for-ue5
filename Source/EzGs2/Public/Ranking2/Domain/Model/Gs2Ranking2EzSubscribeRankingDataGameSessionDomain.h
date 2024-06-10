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
#include "Ranking2/Domain/Model/SubscribeRankingDataAccessToken.h"
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
#include "Gs2Ranking2EzSubscribeRankingDataGameSessionDomain.h"
#include "Ranking2/Domain/Iterator/Gs2Ranking2EzDescribeSubscribeRankingsIterator.h"
#include "Util/Net/GameSession.h"
#include "Util/Net/Gs2Connection.h"

namespace Gs2::UE5::Ranking2::Domain::Model
{

    class EZGS2_API FEzSubscribeRankingDataGameSessionDomain final :
        public TSharedFromThis<FEzSubscribeRankingDataGameSessionDomain>
    {
        Gs2::Ranking2::Domain::Model::FSubscribeRankingDataAccessTokenDomainPtr Domain;
        Gs2::UE5::Util::FGameSessionPtr GameSession;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;
        TOptional<FString> RankingName() const;
        TOptional<int64> Season() const;
        TOptional<FString> ScorerUserId() const;

        FEzSubscribeRankingDataGameSessionDomain(
            Gs2::Ranking2::Domain::Model::FSubscribeRankingDataAccessTokenDomainPtr Domain,
            Gs2::UE5::Util::FGameSessionPtr GameSession,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

        class FGetSubscribeRankingRankTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Ranking2::Domain::Model::FEzSubscribeRankingDataGameSessionDomain>,
            public TSharedFromThis<FGetSubscribeRankingRankTask>
        {
            TSharedPtr<FEzSubscribeRankingDataGameSessionDomain> Self;

        public:
            explicit FGetSubscribeRankingRankTask(
                TSharedPtr<FEzSubscribeRankingDataGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Ranking2::Domain::Model::FEzSubscribeRankingDataGameSessionDomain>> Result
            ) override;
        };
        friend FGetSubscribeRankingRankTask;

        TSharedPtr<FAsyncTask<FGetSubscribeRankingRankTask>> GetSubscribeRankingRank(
        );

        class FModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Ranking2::Model::FEzSubscribeRankingData>,
            public TSharedFromThis<FModelTask>
        {
            TSharedPtr<FEzSubscribeRankingDataGameSessionDomain> Self;

        public:
            explicit FModelTask(
                TSharedPtr<FEzSubscribeRankingDataGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<Gs2::UE5::Ranking2::Model::FEzSubscribeRankingDataPtr> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(TFunction<void(Gs2::UE5::Ranking2::Model::FEzSubscribeRankingDataPtr)> Callback);

        void Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId);

    };
    typedef TSharedPtr<FEzSubscribeRankingDataGameSessionDomain> FEzSubscribeRankingDataGameSessionDomainPtr;
}
