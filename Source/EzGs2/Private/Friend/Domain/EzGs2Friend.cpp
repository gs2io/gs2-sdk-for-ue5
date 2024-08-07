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

#include "Friend/Domain/EzGs2Friend.h"

namespace Gs2::UE5::Friend::Domain
{

    FEzGs2Friend::FEzGs2Friend(
        Gs2::Friend::Domain::FGs2FriendDomainPtr Domain,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        ConnectionValue(Connection)
    {

    }

    Gs2::UE5::Friend::Domain::Model::FEzNamespaceDomainPtr FEzGs2Friend::Namespace(
        const FString NamespaceName
    ) const
    {
        return MakeShared<Gs2::UE5::Friend::Domain::Model::FEzNamespaceDomain>(
            Domain->Namespace(
                NamespaceName
            ),
            ConnectionValue
        );
    }

    FFollowNotificationEvent& FEzGs2Friend::OnFollowNotification()
    {
        return FollowNotificationEvent;
    }

    FAcceptRequestNotificationEvent& FEzGs2Friend::OnAcceptRequestNotification()
    {
        return AcceptRequestNotificationEvent;
    }

    FRejectRequestNotificationEvent& FEzGs2Friend::OnRejectRequestNotification()
    {
        return RejectRequestNotificationEvent;
    }

    FDeleteFriendNotificationEvent& FEzGs2Friend::OnDeleteFriendNotification()
    {
        return DeleteFriendNotificationEvent;
    }

    FReceiveRequestNotificationEvent& FEzGs2Friend::OnReceiveRequestNotification()
    {
        return ReceiveRequestNotificationEvent;
    }

    FCancelRequestNotificationEvent& FEzGs2Friend::OnCancelRequestNotification()
    {
        return CancelRequestNotificationEvent;
    }
}
