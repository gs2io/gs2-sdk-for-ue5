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
#include "Ranking2/Domain/Model/Namespace.h"
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
#include "Gs2Ranking2EzGlobalRankingModelDomain.h"
#include "Ranking2/Domain/Iterator/Gs2Ranking2EzDescribeGlobalRankingModelsIterator.h"
#include "Gs2Ranking2EzUserDomain.h"
#include "Gs2Ranking2EzUserDomain.h"
#include "Gs2Ranking2EzUserGameSessionDomain.h"
#include "Gs2Ranking2EzSubscribeRankingModelDomain.h"
#include "Ranking2/Domain/Iterator/Gs2Ranking2EzDescribeSubscribeRankingModelsIterator.h"
#include "Gs2Ranking2EzClusterRankingModelDomain.h"
#include "Ranking2/Domain/Iterator/Gs2Ranking2EzDescribeClusterRankingModelsIterator.h"
#include "Gs2Ranking2EzNamespaceDomain.h"
#include "Util/Net/GameSession.h"
#include "Util/Net/Gs2Connection.h"

namespace Gs2::UE5::Ranking2::Domain::Model
{

    class EZGS2_API FEzNamespaceDomain final :
        public TSharedFromThis<FEzNamespaceDomain>
    {
        Gs2::Ranking2::Domain::Model::FNamespaceDomainPtr Domain;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:
        TOptional<FString> Status() const;
        TOptional<FString> Url() const;
        TOptional<FString> UploadToken() const;
        TOptional<FString> UploadUrl() const;
        TOptional<FString> NextPageToken() const;
        TOptional<FString> NamespaceName() const;

        FEzNamespaceDomain(
            Gs2::Ranking2::Domain::Model::FNamespaceDomainPtr Domain,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

        Gs2::UE5::Ranking2::Domain::Iterator::FEzDescribeGlobalRankingModelsIteratorPtr GlobalRankingModels(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeGlobalRankingModels(TFunction<void()> Callback);

        void UnsubscribeGlobalRankingModels(Gs2::Core::Domain::CallbackID CallbackId);

        Gs2::UE5::Ranking2::Domain::Model::FEzGlobalRankingModelDomainPtr GlobalRankingModel(
            const FString RankingName
        ) const;

        Gs2::UE5::Ranking2::Domain::Model::FEzUserDomainPtr User(
            const FString UserId
        ) const;

        Gs2::UE5::Ranking2::Domain::Model::FEzUserGameSessionDomainPtr Me(
            Gs2::UE5::Util::IGameSessionPtr GameSession
        ) const;

        Gs2::UE5::Ranking2::Domain::Iterator::FEzDescribeSubscribeRankingModelsIteratorPtr SubscribeRankingModels(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeSubscribeRankingModels(TFunction<void()> Callback);

        void UnsubscribeSubscribeRankingModels(Gs2::Core::Domain::CallbackID CallbackId);

        Gs2::UE5::Ranking2::Domain::Model::FEzSubscribeRankingModelDomainPtr SubscribeRankingModel(
            const FString RankingName
        ) const;

        Gs2::UE5::Ranking2::Domain::Iterator::FEzDescribeClusterRankingModelsIteratorPtr ClusterRankingModels(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeClusterRankingModels(TFunction<void()> Callback);

        void UnsubscribeClusterRankingModels(Gs2::Core::Domain::CallbackID CallbackId);

        Gs2::UE5::Ranking2::Domain::Model::FEzClusterRankingModelDomainPtr ClusterRankingModel(
            const FString RankingName
        ) const;

    };
    typedef TSharedPtr<FEzNamespaceDomain> FEzNamespaceDomainPtr;
}
