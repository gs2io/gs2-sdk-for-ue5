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

#include "Friend/Model/Gs2FriendUser.h"
#include "Friend/Model/Gs2FriendProfile.h"
#include "Friend/Model/Gs2FriendPublicProfile.h"
#include "Friend/Model/Gs2FriendBlackList.h"
#include "Friend/Model/Gs2FriendFollowUser.h"
#include "Friend/Model/Gs2FriendFriendRequest.h"
#include "Core/Model/Gs2AccessToken.h"
#include "Friend/Model/Gs2FriendProfile.h"
#include "Friend/Model/Gs2FriendPublicProfile.h"
#include "Friend/Model/Gs2FriendBlackList.h"
#include "Friend/Model/Gs2FriendFollowUser.h"
#include "Friend/Model/Gs2FriendFriend.h"
#include "Friend/Model/Gs2FriendSendFriendRequest.h"
#include "Friend/Model/Gs2FriendReceiveFriendRequest.h"
#include "Core/BpGs2Constant.h"

FGs2FriendOwnProfile UGs2FriendUserFunctionLibrary::OwnProfile(
    FGs2FriendOwnUser User
)
{
    FGs2FriendOwnProfile Return;
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2FriendUserFunctionLibrary::OwnProfile] User parameter specification is missing."))
        return Return;
    }
    Return.Value = User.Value->Profile(
    );
    return Return;
}

FGs2FriendPublicProfile UGs2FriendUserFunctionLibrary::PublicProfile(
    FGs2FriendUser User,
    FString UserId
)
{
    FGs2FriendPublicProfile Return;
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2FriendUserFunctionLibrary::PublicProfile] User parameter specification is missing."))
        return Return;
    }
    if (UserId == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2FriendUserFunctionLibrary::PublicProfile] UserId parameter specification is missing."))
        return Return;
    }
    Return.Value = User.Value->PublicProfile(
    );
    return Return;
}

FGs2FriendOwnBlackList UGs2FriendUserFunctionLibrary::OwnBlackList(
    FGs2FriendOwnUser User
)
{
    FGs2FriendOwnBlackList Return;
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2FriendUserFunctionLibrary::OwnBlackList] User parameter specification is missing."))
        return Return;
    }
    Return.Value = User.Value->BlackList(
    );
    return Return;
}

FGs2FriendOwnFollowUser UGs2FriendUserFunctionLibrary::OwnFollowUser(
    FGs2FriendOwnUser User,
    FString TargetUserId,
    bool WithProfile
)
{
    FGs2FriendOwnFollowUser Return;
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2FriendUserFunctionLibrary::OwnFollowUser] User parameter specification is missing."))
        return Return;
    }
    if (TargetUserId == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2FriendUserFunctionLibrary::OwnFollowUser] TargetUserId parameter specification is missing."))
        return Return;
    }
    Return.Value = User.Value->FollowUser(
        TargetUserId,
        WithProfile
    );
    return Return;
}

FGs2FriendOwnFriend UGs2FriendUserFunctionLibrary::OwnFriend(
    FGs2FriendOwnUser User,
    bool WithProfile
)
{
    FGs2FriendOwnFriend Return;
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2FriendUserFunctionLibrary::OwnFriend] User parameter specification is missing."))
        return Return;
    }
    Return.Value = User.Value->Friend(
        WithProfile
    );
    return Return;
}

FGs2FriendOwnSendFriendRequest UGs2FriendUserFunctionLibrary::OwnSendFriendRequest(
    FGs2FriendOwnUser User,
    FString TargetUserId
)
{
    FGs2FriendOwnSendFriendRequest Return;
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2FriendUserFunctionLibrary::OwnSendFriendRequest] User parameter specification is missing."))
        return Return;
    }
    if (TargetUserId == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2FriendUserFunctionLibrary::OwnSendFriendRequest] TargetUserId parameter specification is missing."))
        return Return;
    }
    Return.Value = User.Value->SendFriendRequest(
        TargetUserId
    );
    return Return;
}

FGs2FriendOwnReceiveFriendRequest UGs2FriendUserFunctionLibrary::OwnReceiveFriendRequest(
    FGs2FriendOwnUser User,
    FString FromUserId
)
{
    FGs2FriendOwnReceiveFriendRequest Return;
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2FriendUserFunctionLibrary::OwnReceiveFriendRequest] User parameter specification is missing."))
        return Return;
    }
    if (FromUserId == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2FriendUserFunctionLibrary::OwnReceiveFriendRequest] FromUserId parameter specification is missing."))
        return Return;
    }
    Return.Value = User.Value->ReceiveFriendRequest(
        FromUserId
    );
    return Return;
}