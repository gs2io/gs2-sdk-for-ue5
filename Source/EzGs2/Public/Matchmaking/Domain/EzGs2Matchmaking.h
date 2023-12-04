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
#include "Matchmaking/Domain/Gs2Matchmaking.h"
#include "Util/Net/Gs2Connection.h"
#include "Matchmaking/Domain/Model/Gs2MatchmakingEzNamespaceDomain.h"
#include "Matchmaking/Domain/Model/Gs2MatchmakingEzBallotDomain.h"

namespace Gs2::UE5::Matchmaking::Domain
{
    DECLARE_EVENT_OneParam(Gs2Matchmaking, FJoinNotificationEvent, Gs2::Matchmaking::Model::FJoinNotificationPtr);
    typedef TSharedPtr<FJoinNotificationEvent> FJoinNotificationEventPtr;
    DECLARE_EVENT_OneParam(Gs2Matchmaking, FLeaveNotificationEvent, Gs2::Matchmaking::Model::FLeaveNotificationPtr);
    typedef TSharedPtr<FLeaveNotificationEvent> FLeaveNotificationEventPtr;
    DECLARE_EVENT_OneParam(Gs2Matchmaking, FCompleteNotificationEvent, Gs2::Matchmaking::Model::FCompleteNotificationPtr);
    typedef TSharedPtr<FCompleteNotificationEvent> FCompleteNotificationEventPtr;
    DECLARE_EVENT_OneParam(Gs2Matchmaking, FChangeRatingNotificationEvent, Gs2::Matchmaking::Model::FChangeRatingNotificationPtr);
    typedef TSharedPtr<FChangeRatingNotificationEvent> FChangeRatingNotificationEventPtr;

    class EZGS2_API FEzGs2Matchmaking {
        Gs2::Matchmaking::Domain::FGs2MatchmakingDomainPtr Domain;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:
        FJoinNotificationEvent JoinNotificationEvent;
        FLeaveNotificationEvent LeaveNotificationEvent;
        FCompleteNotificationEvent CompleteNotificationEvent;
        FChangeRatingNotificationEvent ChangeRatingNotificationEvent;

        FEzGs2Matchmaking(
            Gs2::Matchmaking::Domain::FGs2MatchmakingDomainPtr Domain,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

        Gs2::UE5::Matchmaking::Domain::Model::FEzNamespaceDomainPtr Namespace(
            const FString NamespaceName
        ) const;

        FJoinNotificationEvent& OnJoinNotification();

        FLeaveNotificationEvent& OnLeaveNotification();

        FCompleteNotificationEvent& OnCompleteNotification();

        FChangeRatingNotificationEvent& OnChangeRatingNotification();
    };
    typedef TSharedPtr<FEzGs2Matchmaking> FEzGs2MatchmakingPtr;
}
