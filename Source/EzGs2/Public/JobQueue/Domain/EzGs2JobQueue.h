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
#include "JobQueue/Domain/Gs2JobQueue.h"
#include "Util/Net/Gs2Connection.h"
#include "JobQueue/Domain/Model/Gs2JobQueueEzNamespaceDomain.h"

namespace Gs2::UE5::JobQueue::Domain
{
    DECLARE_EVENT_OneParam(Gs2JobQueue, FPushNotificationEvent, Gs2::JobQueue::Model::FPushNotificationPtr);
    typedef TSharedPtr<FPushNotificationEvent> FPushNotificationEventPtr;
    DECLARE_EVENT_OneParam(Gs2JobQueue, FRunNotificationEvent, Gs2::JobQueue::Model::FRunNotificationPtr);
    typedef TSharedPtr<FRunNotificationEvent> FRunNotificationEventPtr;

    class EZGS2_API FEzGs2JobQueue {
        Gs2::JobQueue::Domain::FGs2JobQueueDomainPtr Domain;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:
        FPushNotificationEvent PushNotificationEvent;
        FRunNotificationEvent RunNotificationEvent;

        FEzGs2JobQueue(
            Gs2::JobQueue::Domain::FGs2JobQueueDomainPtr Domain,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

        Gs2::UE5::JobQueue::Domain::Model::FEzNamespaceDomainPtr Namespace(
            const FString NamespaceName
        ) const;

        FPushNotificationEvent& OnPushNotification();

        FRunNotificationEvent& OnRunNotification();
    };
    typedef TSharedPtr<FEzGs2JobQueue> FEzGs2JobQueuePtr;
}
