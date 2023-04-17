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

#include "Matchmaking/Model/Gs2Matchmaking.h"
#include "BpGs2/Public/Matchmaking/Model/Gs2MatchmakingNamespace.h"
#include "BpGs2/Public/Matchmaking/Model/Gs2MatchmakingBallot.h"
#include "Core/BpGs2Constant.h"

FGs2Matchmaking UGs2MatchmakingFunctionLibrary::Service(
    FGs2Client Client,
    FBpMatchmakingJoinNotificationEvent JoinNotification,
    FBpMatchmakingLeaveNotificationEvent LeaveNotification,
    FBpMatchmakingCompleteNotificationEvent CompleteNotification,
    FBpMatchmakingChangeRatingNotificationEvent ChangeRatingNotification
)
{
    FGs2Matchmaking Return;
    if (Client.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2MatchmakingFunctionLibrary::Service] Client parameter specification is missing."))
        return Return;
    }
    Client.Value->Matchmaking->OnJoinNotification().AddLambda([&JoinNotification](auto Notification)
    {
        JoinNotification.Value.Execute(EzJoinNotificationToFGs2MatchmakingJoinNotification(Notification));
    });
    Client.Value->Matchmaking->OnLeaveNotification().AddLambda([&LeaveNotification](auto Notification)
    {
        LeaveNotification.Value.Execute(EzLeaveNotificationToFGs2MatchmakingLeaveNotification(Notification));
    });
    Client.Value->Matchmaking->OnCompleteNotification().AddLambda([&CompleteNotification](auto Notification)
    {
        CompleteNotification.Value.Execute(EzCompleteNotificationToFGs2MatchmakingCompleteNotification(Notification));
    });
    Client.Value->Matchmaking->OnChangeRatingNotification().AddLambda([&ChangeRatingNotification](auto Notification)
    {
        ChangeRatingNotification.Value.Execute(EzChangeRatingNotificationToFGs2MatchmakingChangeRatingNotification(Notification));
    });
    Return.Value = Client.Value->Matchmaking;
    return Return;
}
FGs2MatchmakingNamespace UGs2MatchmakingFunctionLibrary::Namespace(
    FGs2Matchmaking Service,
    FString NamespaceName
)
{
    FGs2MatchmakingNamespace Return;
    if (Service.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2MatchmakingFunctionLibrary::Namespace] Service parameter specification is missing."))
        return Return;
    }
    if (NamespaceName == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2MatchmakingFunctionLibrary::Namespace] NamespaceName parameter specification is missing."))
        return Return;
    }
    Return.Value = Service.Value->Namespace(
        NamespaceName
    );
    return Return;
}