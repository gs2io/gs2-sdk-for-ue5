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
#include "Guild/Domain/Gs2Guild.h"
#include "Util/Net/Gs2Connection.h"
#include "Guild/Domain/Model/Gs2GuildEzNamespaceDomain.h"
#include "Guild/Domain/Model/Gs2GuildEzIgnoreUserDomain.h"

namespace Gs2::UE5::Guild::Domain
{
    DECLARE_EVENT_OneParam(Gs2Guild, FReceiveRequestNotificationEvent, Gs2::Guild::Model::FReceiveRequestNotificationPtr);
    typedef TSharedPtr<FReceiveRequestNotificationEvent> FReceiveRequestNotificationEventPtr;
    DECLARE_EVENT_OneParam(Gs2Guild, FRemoveRequestNotificationEvent, Gs2::Guild::Model::FRemoveRequestNotificationPtr);
    typedef TSharedPtr<FRemoveRequestNotificationEvent> FRemoveRequestNotificationEventPtr;
    DECLARE_EVENT_OneParam(Gs2Guild, FChangeNotificationEvent, Gs2::Guild::Model::FChangeNotificationPtr);
    typedef TSharedPtr<FChangeNotificationEvent> FChangeNotificationEventPtr;
    DECLARE_EVENT_OneParam(Gs2Guild, FJoinNotificationEvent, Gs2::Guild::Model::FJoinNotificationPtr);
    typedef TSharedPtr<FJoinNotificationEvent> FJoinNotificationEventPtr;
    DECLARE_EVENT_OneParam(Gs2Guild, FLeaveNotificationEvent, Gs2::Guild::Model::FLeaveNotificationPtr);
    typedef TSharedPtr<FLeaveNotificationEvent> FLeaveNotificationEventPtr;
    DECLARE_EVENT_OneParam(Gs2Guild, FChangeMemberNotificationEvent, Gs2::Guild::Model::FChangeMemberNotificationPtr);
    typedef TSharedPtr<FChangeMemberNotificationEvent> FChangeMemberNotificationEventPtr;

    class EZGS2_API FEzGs2Guild {
        Gs2::Guild::Domain::FGs2GuildDomainPtr Domain;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:
        FReceiveRequestNotificationEvent ReceiveRequestNotificationEvent;
        FRemoveRequestNotificationEvent RemoveRequestNotificationEvent;
        FChangeNotificationEvent ChangeNotificationEvent;
        FJoinNotificationEvent JoinNotificationEvent;
        FLeaveNotificationEvent LeaveNotificationEvent;
        FChangeMemberNotificationEvent ChangeMemberNotificationEvent;

        FEzGs2Guild(
            Gs2::Guild::Domain::FGs2GuildDomainPtr Domain,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

        Gs2::UE5::Guild::Domain::Model::FEzNamespaceDomainPtr Namespace(
            const FString NamespaceName
        ) const;

        FReceiveRequestNotificationEvent& OnReceiveRequestNotification();

        FRemoveRequestNotificationEvent& OnRemoveRequestNotification();

        FChangeNotificationEvent& OnChangeNotification();

        FJoinNotificationEvent& OnJoinNotification();

        FLeaveNotificationEvent& OnLeaveNotification();

        FChangeMemberNotificationEvent& OnChangeMemberNotification();
    };
    typedef TSharedPtr<FEzGs2Guild> FEzGs2GuildPtr;
}
