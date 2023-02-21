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
#include "Gs2Mission/Public/Mission/Domain/Gs2Mission.h"
#include "Util/Profile.h"
#include "Mission/Domain/Model/Gs2MissionEzNamespaceDomain.h"
#include "Mission/Domain/Model/Gs2MissionEzMissionTaskModelDomain.h"

namespace Gs2::UE5::Mission::Domain
{
    DECLARE_EVENT_OneParam(Gs2Mission, FCompleteNotificationEvent, Gs2::Mission::Model::FCompleteNotificationPtr);
    typedef TSharedPtr<FCompleteNotificationEvent> FCompleteNotificationEventPtr;

    class EZGS2_API FEzGs2Mission {
        Gs2::Mission::Domain::FGs2MissionDomainPtr Domain;
        Gs2::UE5::Util::FProfilePtr ProfileValue;

        public:
        FCompleteNotificationEvent CompleteNotificationEvent;

        FEzGs2Mission(
            Gs2::Mission::Domain::FGs2MissionDomainPtr Domain,
            Gs2::UE5::Util::FProfilePtr Profile
        );

        Gs2::UE5::Mission::Domain::Model::FEzNamespaceDomainPtr Namespace(
            const FString NamespaceName
        ) const;

        FCompleteNotificationEvent& OnCompleteNotification();
    };
    typedef TSharedPtr<FEzGs2Mission> FEzGs2MissionPtr;
}
