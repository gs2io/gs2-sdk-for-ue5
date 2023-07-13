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
#include "LoginReward/Domain/Model/User.h"
#include "LoginReward/Model/Gs2LoginRewardEzReceiveStatus.h"
#include "LoginReward/Model/Gs2LoginRewardEzBonusModel.h"
#include "LoginReward/Model/Gs2LoginRewardEzReward.h"
#include "LoginReward/Model/Gs2LoginRewardEzConfig.h"
#include "LoginReward/Model/Gs2LoginRewardEzConsumeAction.h"
#include "LoginReward/Model/Gs2LoginRewardEzAcquireAction.h"
#include "Gs2LoginRewardEzReceiveStatusDomain.h"
#include "Gs2LoginRewardEzUserDomain.h"
#include "Gs2LoginRewardEzUserDomain.h"
#include "Gs2LoginRewardEzUserGameSessionDomain.h"
#include "Auth/Model/Gs2AuthEzAccessToken.h"
#include "Util/Profile.h"

namespace Gs2::UE5::LoginReward::Domain::Model
{

    class EZGS2_API FEzUserDomain final :
        public TSharedFromThis<FEzUserDomain>
    {
        Gs2::LoginReward::Domain::Model::FUserDomainPtr Domain;
        Gs2::UE5::Util::FProfilePtr ProfileValue;

        public:
        TOptional<FString> NextPageToken() const;
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;

        FEzUserDomain(
            Gs2::LoginReward::Domain::Model::FUserDomainPtr Domain,
            Gs2::UE5::Util::FProfilePtr Profile
        );

        Gs2::UE5::LoginReward::Domain::Model::FEzReceiveStatusDomainPtr ReceiveStatus(
            const FString BonusModelName
        ) const;

    };
    typedef TSharedPtr<FEzUserDomain> FEzUserDomainPtr;
}
