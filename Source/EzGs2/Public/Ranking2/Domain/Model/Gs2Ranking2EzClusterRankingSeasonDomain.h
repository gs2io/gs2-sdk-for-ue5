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
#include "Ranking2/Domain/Model/ClusterRankingSeason.h"
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
#include "Gs2Ranking2EzClusterRankingReceivedRewardDomain.h"
#include "Gs2Ranking2EzClusterRankingScoreDomain.h"
#include "Gs2Ranking2EzClusterRankingSeasonDomain.h"
#include "Core/EzTransactionDomain.h"
#include "Util/Net/GameSession.h"
#include "Util/Net/Gs2Connection.h"

namespace Gs2::UE5::Ranking2::Domain::Model
{

    class EZGS2_API FEzClusterRankingSeasonDomain final :
        public TSharedFromThis<FEzClusterRankingSeasonDomain>
    {
        Gs2::Ranking2::Domain::Model::FClusterRankingSeasonDomainPtr Domain;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:
        TOptional<FString> NextPageToken() const;
        TOptional<FString> NamespaceName() const;
        TOptional<FString> RankingName() const;
        TOptional<FString> ClusterName() const;
        TOptional<int64> Season() const;
        TOptional<FString> UserId() const;

        FEzClusterRankingSeasonDomain(
            Gs2::Ranking2::Domain::Model::FClusterRankingSeasonDomainPtr Domain,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

        Gs2::UE5::Ranking2::Domain::Model::FEzClusterRankingReceivedRewardDomainPtr ClusterRankingReceivedReward(
        ) const;

        Gs2::UE5::Ranking2::Domain::Model::FEzClusterRankingScoreDomainPtr ClusterRankingScore(
        ) const;

    };
    typedef TSharedPtr<FEzClusterRankingSeasonDomain> FEzClusterRankingSeasonDomainPtr;
}
