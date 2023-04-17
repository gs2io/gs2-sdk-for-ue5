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
#include "Gs2Inbox/Public/Inbox/Domain/Gs2Inbox.h"
#include "Util/Profile.h"
#include "Inbox/Domain/Model/Gs2InboxEzNamespaceDomain.h"

namespace Gs2::UE5::Inbox::Domain
{
    DECLARE_EVENT_OneParam(Gs2Inbox, FReceiveNotificationEvent, Gs2::Inbox::Model::FReceiveNotificationPtr);
    typedef TSharedPtr<FReceiveNotificationEvent> FReceiveNotificationEventPtr;

    class EZGS2_API FEzGs2Inbox {
        Gs2::Inbox::Domain::FGs2InboxDomainPtr Domain;
        Gs2::UE5::Util::FProfilePtr ProfileValue;

        public:
        FReceiveNotificationEvent ReceiveNotificationEvent;

        FEzGs2Inbox(
            Gs2::Inbox::Domain::FGs2InboxDomainPtr Domain,
            Gs2::UE5::Util::FProfilePtr Profile
        );

        Gs2::UE5::Inbox::Domain::Model::FEzNamespaceDomainPtr Namespace(
            const FString NamespaceName
        ) const;

        FReceiveNotificationEvent& OnReceiveNotification();
    };
    typedef TSharedPtr<FEzGs2Inbox> FEzGs2InboxPtr;
}
