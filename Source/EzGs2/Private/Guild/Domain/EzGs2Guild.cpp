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

#include "Guild/Domain/EzGs2Guild.h"

namespace Gs2::UE5::Guild::Domain
{

    FEzGs2Guild::FEzGs2Guild(
        Gs2::Guild::Domain::FGs2GuildDomainPtr Domain,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        ConnectionValue(Connection)
    {

    }

    Gs2::UE5::Guild::Domain::Model::FEzNamespaceDomainPtr FEzGs2Guild::Namespace(
        const FString NamespaceName
    ) const
    {
        return MakeShared<Gs2::UE5::Guild::Domain::Model::FEzNamespaceDomain>(
            Domain->Namespace(
                NamespaceName
            ),
            ConnectionValue
        );
    }

    FReceiveRequestNotificationEvent& FEzGs2Guild::OnReceiveRequestNotification()
    {
        return ReceiveRequestNotificationEvent;
    }

    FRemoveRequestNotificationEvent& FEzGs2Guild::OnRemoveRequestNotification()
    {
        return RemoveRequestNotificationEvent;
    }

    FJoinNotificationEvent& FEzGs2Guild::OnJoinNotification()
    {
        return JoinNotificationEvent;
    }

    FLeaveNotificationEvent& FEzGs2Guild::OnLeaveNotification()
    {
        return LeaveNotificationEvent;
    }

    FChangeMemberNotificationEvent& FEzGs2Guild::OnChangeMemberNotification()
    {
        return ChangeMemberNotificationEvent;
    }
}
