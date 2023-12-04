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
#include "Realtime/Domain/Gs2Realtime.h"
#include "Util/Net/Gs2Connection.h"
#include "Realtime/Domain/Model/Gs2RealtimeEzNamespaceDomain.h"

namespace Gs2::UE5::Realtime::Domain
{
    DECLARE_EVENT_OneParam(Gs2Realtime, FCreateNotificationEvent, Gs2::Realtime::Model::FCreateNotificationPtr);
    typedef TSharedPtr<FCreateNotificationEvent> FCreateNotificationEventPtr;

    class EZGS2_API FEzGs2Realtime {
        Gs2::Realtime::Domain::FGs2RealtimeDomainPtr Domain;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:
        FCreateNotificationEvent CreateNotificationEvent;

        FEzGs2Realtime(
            Gs2::Realtime::Domain::FGs2RealtimeDomainPtr Domain,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

        Gs2::UE5::Realtime::Domain::Model::FEzNamespaceDomainPtr Namespace(
            const FString NamespaceName
        ) const;

        FCreateNotificationEvent& OnCreateNotification();
    };
    typedef TSharedPtr<FEzGs2Realtime> FEzGs2RealtimePtr;
}
