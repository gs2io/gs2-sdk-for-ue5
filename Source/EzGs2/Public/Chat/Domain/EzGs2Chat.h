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
#include "Chat/Domain/Gs2Chat.h"
#include "Util/Profile.h"
#include "Chat/Domain/Model/Gs2ChatEzNamespaceDomain.h"

namespace Gs2::UE5::Chat::Domain
{
    DECLARE_EVENT_OneParam(Gs2Chat, FPostNotificationEvent, Gs2::Chat::Model::FPostNotificationPtr);
    typedef TSharedPtr<FPostNotificationEvent> FPostNotificationEventPtr;

    class EZGS2_API FEzGs2Chat {
        Gs2::Chat::Domain::FGs2ChatDomainPtr Domain;
        Gs2::UE5::Util::FProfilePtr ProfileValue;

        public:
        FPostNotificationEvent PostNotificationEvent;

        FEzGs2Chat(
            Gs2::Chat::Domain::FGs2ChatDomainPtr Domain,
            Gs2::UE5::Util::FProfilePtr Profile
        );

        Gs2::UE5::Chat::Domain::Model::FEzNamespaceDomainPtr Namespace(
            const FString NamespaceName
        ) const;

        FPostNotificationEvent& OnPostNotification();
    };
    typedef TSharedPtr<FEzGs2Chat> FEzGs2ChatPtr;
}
