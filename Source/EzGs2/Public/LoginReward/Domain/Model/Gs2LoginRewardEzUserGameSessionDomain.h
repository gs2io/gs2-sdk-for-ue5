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
#include "LoginReward/Domain/Model/UserAccessToken.h"
#include "LoginReward/Model/Gs2LoginRewardEzReceiveStatus.h"
#include "LoginReward/Model/Gs2LoginRewardEzBonusModel.h"
#include "LoginReward/Model/Gs2LoginRewardEzReward.h"
#include "LoginReward/Model/Gs2LoginRewardEzConfig.h"
#include "LoginReward/Model/Gs2LoginRewardEzConsumeAction.h"
#include "LoginReward/Model/Gs2LoginRewardEzVerifyAction.h"
#include "LoginReward/Model/Gs2LoginRewardEzAcquireAction.h"
#include "LoginReward/Model/Gs2LoginRewardEzVerifyActionResult.h"
#include "LoginReward/Model/Gs2LoginRewardEzConsumeActionResult.h"
#include "LoginReward/Model/Gs2LoginRewardEzAcquireActionResult.h"
#include "LoginReward/Model/Gs2LoginRewardEzTransactionResult.h"
#include "Gs2LoginRewardEzBonusGameSessionDomain.h"
#include "Gs2LoginRewardEzReceiveStatusGameSessionDomain.h"
#include "LoginReward/Domain/Iterator/Gs2LoginRewardEzDescribeReceiveStatusesIterator.h"
#include "Gs2LoginRewardEzUserGameSessionDomain.h"
#include "Core/EzTransactionGameSessionDomain.h"
#include "Util/Net/GameSession.h"
#include "Util/Net/Gs2Connection.h"

namespace Gs2::UE5::LoginReward::Domain::Model
{

    class EZGS2_API FEzUserGameSessionDomain final :
        public TSharedFromThis<FEzUserGameSessionDomain>
    {
        Gs2::LoginReward::Domain::Model::FUserAccessTokenDomainPtr Domain;
        Gs2::UE5::Util::IGameSessionPtr GameSession;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:
        TOptional<FString> NextPageToken() const;
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;

        FEzUserGameSessionDomain(
            Gs2::LoginReward::Domain::Model::FUserAccessTokenDomainPtr Domain,
            Gs2::UE5::Util::IGameSessionPtr GameSession,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

        Gs2::UE5::LoginReward::Domain::Iterator::FEzDescribeReceiveStatusesIteratorPtr ReceiveStatuses(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeReceiveStatuses(TFunction<void()> Callback);

        void UnsubscribeReceiveStatuses(Gs2::Core::Domain::CallbackID CallbackId);

        Gs2::UE5::LoginReward::Domain::Model::FEzBonusGameSessionDomainPtr Bonus(
        ) const;

        Gs2::UE5::LoginReward::Domain::Model::FEzReceiveStatusGameSessionDomainPtr ReceiveStatus(
            const FString BonusModelName
        ) const;

    };
    typedef TSharedPtr<FEzUserGameSessionDomain> FEzUserGameSessionDomainPtr;
}
