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

#pragma once

#include "CoreMinimal.h"
#include "Ranking2/Domain/Model/GlobalRankingModel.h"
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
#include "Gs2Ranking2EzGlobalRankingModelDomain.h"
#include "Gs2Ranking2EzGlobalRankingSeasonDomain.h"
#include "Ranking2/Domain/Iterator/Gs2Ranking2EzDescribeGlobalRankingModelsIterator.h"
#include "Util/Net/GameSession.h"
#include "Util/Net/Gs2Connection.h"

namespace Gs2::UE5::Ranking2::Domain::Model
{

    class EZGS2_API FEzGlobalRankingModelDomain final :
        public TSharedFromThis<FEzGlobalRankingModelDomain>
    {
        Gs2::Ranking2::Domain::Model::FGlobalRankingModelDomainPtr Domain;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:
        TOptional<FString> NamespaceName() const;
        TOptional<FString> RankingName() const;

        FEzGlobalRankingModelDomain(
            Gs2::Ranking2::Domain::Model::FGlobalRankingModelDomainPtr Domain,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

        Gs2::UE5::Ranking2::Domain::Model::FEzGlobalRankingSeasonDomainPtr GlobalRankingSeason(
            const int64 Season
        ) const;

        class FModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Ranking2::Model::FEzGlobalRankingModel>,
            public TSharedFromThis<FModelTask>
        {
            TSharedPtr<FEzGlobalRankingModelDomain> Self;

        public:
            explicit FModelTask(
                TSharedPtr<FEzGlobalRankingModelDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<Gs2::UE5::Ranking2::Model::FEzGlobalRankingModelPtr> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(TFunction<void(Gs2::UE5::Ranking2::Model::FEzGlobalRankingModelPtr)> Callback);

        void Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId);

    };
    typedef TSharedPtr<FEzGlobalRankingModelDomain> FEzGlobalRankingModelDomainPtr;
}
