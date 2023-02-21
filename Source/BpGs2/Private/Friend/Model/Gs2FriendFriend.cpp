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
 *
 * deny overwrite
 */

#include "BpGs2/Public/Friend/Model/Gs2FriendFriend.h"
#include "BpGs2/Public/Friend/Model/Gs2FriendFriendUser.h"
#include "Core/Model/Gs2AccessToken.h"
#include "Friend/Model/Gs2FriendFriendUser.h"
#include "Core/BpGs2Constant.h"

FGs2FriendOwnFriendUser UGs2FriendFriendFunctionLibrary::OwnFriendUser(
    FGs2FriendOwnFriend Friend,
    FString TargetUserId
)
{
    FGs2FriendOwnFriendUser Return;
    if (Friend.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2FriendFriendFunctionLibrary::OwnFriendUser] Friend parameter specification is missing."))
        return Return;
    }
    if (TargetUserId == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2FriendFriendFunctionLibrary::OwnFriendUser] TargetUserId parameter specification is missing."))
        return Return;
    }
    Return.Value = Friend.Value->FriendUser(
        TargetUserId
    );
    return Return;
}