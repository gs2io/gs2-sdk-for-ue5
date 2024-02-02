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

#include "Friend/Model/Gs2FriendFollow.h"
#include "Friend/Model/Gs2FriendFollowUser.h"
#include "Core/Model/Gs2AccessToken.h"
#include "Friend/Model/Gs2FriendFollowUser.h"
#include "Core/BpGs2Constant.h"

FGs2FriendOwnFollowUser UGs2FriendFollowFunctionLibrary::OwnFollowUser(
    FGs2FriendOwnFollow Follow,
    FString UserId,
    FString TargetUserId
)
{
    FGs2FriendOwnFollowUser Return;
    if (Follow.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2FriendFollowFunctionLibrary::OwnFollowUser] Follow parameter specification is missing."))
        return Return;
    }
    if (UserId == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2FriendFollowFunctionLibrary::OwnFollowUser] UserId parameter specification is missing."))
        return Return;
    }
    if (TargetUserId == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2FriendFollowFunctionLibrary::OwnFollowUser] TargetUserId parameter specification is missing."))
        return Return;
    }
    Return.Value = Follow.Value->FollowUser(
        TargetUserId
    );
    return Return;
}