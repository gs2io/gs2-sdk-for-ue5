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

#include "Chat/Model/Gs2ChatUser.h"
#include "Chat/Domain/EzGs2Chat.h"
#include "Chat/Model/Gs2ChatRoom.h"
#include "Chat/Model/Gs2ChatSubscribe.h"
#include "Core/Model/Gs2AccessToken.h"
#include "Chat/Model/Gs2ChatRoom.h"
#include "Chat/Model/Gs2ChatSubscribe.h"
#include "Core/BpGs2Constant.h"

FGs2ChatRoom UGs2ChatUserFunctionLibrary::Room(
    FGs2ChatUser User,
    FString RoomName,
    FString Password
)
{
    FGs2ChatRoom Return;
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2ChatUserFunctionLibrary::Room] User parameter specification is missing."))
        return Return;
    }
    if (RoomName == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2ChatUserFunctionLibrary::Room] RoomName parameter specification is missing."))
        return Return;
    }
    Return.Value = User.Value->Room(
        RoomName,
        Password
    );
    return Return;
}

FGs2ChatOwnRoom UGs2ChatUserFunctionLibrary::OwnRoom(
    FGs2ChatOwnUser User,
    FString RoomName,
    FString Password
)
{
    FGs2ChatOwnRoom Return;
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2ChatUserFunctionLibrary::OwnRoom] User parameter specification is missing."))
        return Return;
    }
    if (RoomName == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2ChatUserFunctionLibrary::OwnRoom] RoomName parameter specification is missing."))
        return Return;
    }
    Return.Value = User.Value->Room(
        RoomName,
        Password
    );
    return Return;
}

FGs2ChatOwnSubscribe UGs2ChatUserFunctionLibrary::OwnSubscribe(
    FGs2ChatOwnUser User,
    FString RoomName
)
{
    FGs2ChatOwnSubscribe Return;
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2ChatUserFunctionLibrary::OwnSubscribe] User parameter specification is missing."))
        return Return;
    }
    if (RoomName == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2ChatUserFunctionLibrary::OwnSubscribe] RoomName parameter specification is missing."))
        return Return;
    }
    Return.Value = User.Value->Subscribe(
        RoomName
    );
    return Return;
}