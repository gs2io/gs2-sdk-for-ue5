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

#include "Friend/Model/Gs2Friend.h"
#include "Friend/Domain/EzGs2Friend.h"
#include "Friend/Model/Gs2FriendNamespace.h"
#include "Core/BpGs2Constant.h"

FGs2Friend UGs2FriendFunctionLibrary::Service(
    FGs2Client Client,
    FBpFriendFollowNotificationEvent FollowNotification,
    FBpFriendAcceptRequestNotificationEvent AcceptRequestNotification,
    FBpFriendRejectRequestNotificationEvent RejectRequestNotification,
    FBpFriendDeleteFriendNotificationEvent DeleteFriendNotification,
    FBpFriendReceiveRequestNotificationEvent ReceiveRequestNotification,
    FBpFriendCancelRequestNotificationEvent CancelRequestNotification
)
{
    FGs2Friend Return;
    if (Client.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2FriendFunctionLibrary::Service] Client parameter specification is missing."))
        return Return;
    }
    Client.Value->Friend->OnFollowNotification().AddLambda([&FollowNotification](auto Notification)
    {
        FollowNotification.Value.Execute(EzFollowNotificationToFGs2FriendFollowNotification(Notification));
    });
    Client.Value->Friend->OnAcceptRequestNotification().AddLambda([&AcceptRequestNotification](auto Notification)
    {
        AcceptRequestNotification.Value.Execute(EzAcceptRequestNotificationToFGs2FriendAcceptRequestNotification(Notification));
    });
    Client.Value->Friend->OnRejectRequestNotification().AddLambda([&RejectRequestNotification](auto Notification)
    {
        RejectRequestNotification.Value.Execute(EzRejectRequestNotificationToFGs2FriendRejectRequestNotification(Notification));
    });
    Client.Value->Friend->OnDeleteFriendNotification().AddLambda([&DeleteFriendNotification](auto Notification)
    {
        DeleteFriendNotification.Value.Execute(EzDeleteFriendNotificationToFGs2FriendDeleteFriendNotification(Notification));
    });
    Client.Value->Friend->OnReceiveRequestNotification().AddLambda([&ReceiveRequestNotification](auto Notification)
    {
        ReceiveRequestNotification.Value.Execute(EzReceiveRequestNotificationToFGs2FriendReceiveRequestNotification(Notification));
    });
    Client.Value->Friend->OnCancelRequestNotification().AddLambda([&CancelRequestNotification](auto Notification)
    {
        CancelRequestNotification.Value.Execute(EzCancelRequestNotificationToFGs2FriendCancelRequestNotification(Notification));
    });
    Return.Value = Client.Value->Friend;
    return Return;
}
FGs2FriendNamespace UGs2FriendFunctionLibrary::Namespace(
    FGs2Friend Service,
    FString NamespaceName
)
{
    FGs2FriendNamespace Return;
    if (Service.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2FriendFunctionLibrary::Namespace] Service parameter specification is missing."))
        return Return;
    }
    if (NamespaceName == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2FriendFunctionLibrary::Namespace] NamespaceName parameter specification is missing."))
        return Return;
    }
    Return.Value = Service.Value->Namespace(
        NamespaceName
    );
    return Return;
}