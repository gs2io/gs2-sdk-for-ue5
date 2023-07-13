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
#include "Gs2LoginReward/Public/LoginReward/Domain/Gs2LoginReward.h"
#include "Util/Profile.h"
#include "LoginReward/Domain/Model/Gs2LoginRewardEzNamespaceDomain.h"

namespace Gs2::UE5::LoginReward::Domain
{

    class EZGS2_API FEzGs2LoginReward {
        Gs2::LoginReward::Domain::FGs2LoginRewardDomainPtr Domain;
        Gs2::UE5::Util::FProfilePtr ProfileValue;

        public:

        FEzGs2LoginReward(
            Gs2::LoginReward::Domain::FGs2LoginRewardDomainPtr Domain,
            Gs2::UE5::Util::FProfilePtr Profile
        );

        Gs2::UE5::LoginReward::Domain::Model::FEzNamespaceDomainPtr Namespace(
            const FString NamespaceName
        ) const;
    };
    typedef TSharedPtr<FEzGs2LoginReward> FEzGs2LoginRewardPtr;
}
