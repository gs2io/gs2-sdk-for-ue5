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
#include "Friend/Domain/Gs2Friend.h"
#include "Util/Net/Gs2Connection.h"
#include "Friend/Domain/Model/Gs2FriendEzNamespaceDomain.h"

namespace Gs2::UE5::Friend::Domain
{
    DECLARE_EVENT_OneParam(Gs2Friend, FFollowNotificationEvent, Gs2::Friend::Model::FFollowNotificationPtr);
    typedef TSharedPtr<FFollowNotificationEvent> FFollowNotificationEventPtr;
    DECLARE_EVENT_OneParam(Gs2Friend, FAcceptRequestNotificationEvent, Gs2::Friend::Model::FAcceptRequestNotificationPtr);
    typedef TSharedPtr<FAcceptRequestNotificationEvent> FAcceptRequestNotificationEventPtr;
    DECLARE_EVENT_OneParam(Gs2Friend, FRejectRequestNotificationEvent, Gs2::Friend::Model::FRejectRequestNotificationPtr);
    typedef TSharedPtr<FRejectRequestNotificationEvent> FRejectRequestNotificationEventPtr;
    DECLARE_EVENT_OneParam(Gs2Friend, FDeleteFriendNotificationEvent, Gs2::Friend::Model::FDeleteFriendNotificationPtr);
    typedef TSharedPtr<FDeleteFriendNotificationEvent> FDeleteFriendNotificationEventPtr;
    DECLARE_EVENT_OneParam(Gs2Friend, FReceiveRequestNotificationEvent, Gs2::Friend::Model::FReceiveRequestNotificationPtr);
    typedef TSharedPtr<FReceiveRequestNotificationEvent> FReceiveRequestNotificationEventPtr;
    DECLARE_EVENT_OneParam(Gs2Friend, FCancelRequestNotificationEvent, Gs2::Friend::Model::FCancelRequestNotificationPtr);
    typedef TSharedPtr<FCancelRequestNotificationEvent> FCancelRequestNotificationEventPtr;

    class EZGS2_API FEzGs2Friend {
        Gs2::Friend::Domain::FGs2FriendDomainPtr Domain;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:
        FFollowNotificationEvent FollowNotificationEvent;
        FAcceptRequestNotificationEvent AcceptRequestNotificationEvent;
        FRejectRequestNotificationEvent RejectRequestNotificationEvent;
        FDeleteFriendNotificationEvent DeleteFriendNotificationEvent;
        FReceiveRequestNotificationEvent ReceiveRequestNotificationEvent;
        FCancelRequestNotificationEvent CancelRequestNotificationEvent;

        FEzGs2Friend(
            Gs2::Friend::Domain::FGs2FriendDomainPtr Domain,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

        Gs2::UE5::Friend::Domain::Model::FEzNamespaceDomainPtr Namespace(
            const FString NamespaceName
        ) const;

        FFollowNotificationEvent& OnFollowNotification();

        FAcceptRequestNotificationEvent& OnAcceptRequestNotification();

        FRejectRequestNotificationEvent& OnRejectRequestNotification();

        FDeleteFriendNotificationEvent& OnDeleteFriendNotification();

        FReceiveRequestNotificationEvent& OnReceiveRequestNotification();

        FCancelRequestNotificationEvent& OnCancelRequestNotification();
    };
    typedef TSharedPtr<FEzGs2Friend> FEzGs2FriendPtr;
}
