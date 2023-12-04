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
#include "AdReward/Domain/Gs2AdReward.h"
#include "Util/Net/Gs2Connection.h"
#include "AdReward/Domain/Model/Gs2AdRewardEzNamespaceDomain.h"

namespace Gs2::UE5::AdReward::Domain
{
    DECLARE_EVENT_OneParam(Gs2AdReward, FChangePointNotificationEvent, Gs2::AdReward::Model::FChangePointNotificationPtr);
    typedef TSharedPtr<FChangePointNotificationEvent> FChangePointNotificationEventPtr;

    class EZGS2_API FEzGs2AdReward {
        Gs2::AdReward::Domain::FGs2AdRewardDomainPtr Domain;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:
        FChangePointNotificationEvent ChangePointNotificationEvent;

        FEzGs2AdReward(
            Gs2::AdReward::Domain::FGs2AdRewardDomainPtr Domain,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

        Gs2::UE5::AdReward::Domain::Model::FEzNamespaceDomainPtr Namespace(
            const FString NamespaceName
        ) const;

        FChangePointNotificationEvent& OnChangePointNotification();
    };
    typedef TSharedPtr<FEzGs2AdReward> FEzGs2AdRewardPtr;
}
