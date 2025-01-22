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

#include "Chat/Model/Gs2ChatRoom.h"
#include "Chat/Domain/EzGs2Chat.h"
#include "Chat/Model/Gs2ChatMessage.h"
#include "Core/Model/Gs2AccessToken.h"
#include "Chat/Model/Gs2ChatMessage.h"
#include "Core/BpGs2Constant.h"

FGs2ChatOwnMessage UGs2ChatRoomFunctionLibrary::OwnMessage(
    FGs2ChatOwnRoom Room,
    FString MessageName
)
{
    FGs2ChatOwnMessage Return;
    if (Room.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2ChatRoomFunctionLibrary::OwnMessage] Room parameter specification is missing."))
        return Return;
    }
    if (MessageName == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2ChatRoomFunctionLibrary::OwnMessage] MessageName parameter specification is missing."))
        return Return;
    }
    Return.Value = Room.Value->Message(
        MessageName
    );
    return Return;
}