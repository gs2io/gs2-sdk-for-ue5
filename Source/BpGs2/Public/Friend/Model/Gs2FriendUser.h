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

#pragma once

#include "CoreMinimal.h"
#include "Friend/Domain/Model/Gs2FriendEzUserGameSessionDomain.h"
#include "Friend/Domain/Model/Gs2FriendEzUserDomain.h"
#include "Gs2FriendUser.generated.h"

USTRUCT(BlueprintType)
struct FGs2FriendOwnUser
{
    GENERATED_BODY()

    Gs2::UE5::Friend::Domain::Model::FEzUserGameSessionDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2FriendUser
{
    GENERATED_BODY()

    Gs2::UE5::Friend::Domain::Model::FEzUserDomainPtr Value = nullptr;
};

UCLASS()
class BPGS2_API UGs2FriendUserFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Friend::OwnProfile", Category="Game Server Services|GS2-Friend|Namespace|User|Profile", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="Profile") FGs2FriendOwnProfile OwnProfile(
        FGs2FriendOwnUser User
    );

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Friend::PublicProfile", Category="Game Server Services|GS2-Friend|Namespace|User|PublicProfile", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="PublicProfile") FGs2FriendPublicProfile PublicProfile(
        FGs2FriendUser User,
        FString UserId
    );

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Friend::OwnBlackList", Category="Game Server Services|GS2-Friend|Namespace|User|BlackList", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="BlackList") FGs2FriendOwnBlackList OwnBlackList(
        FGs2FriendOwnUser User
    );

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Friend::OwnFollowUser", Category="Game Server Services|GS2-Friend|Namespace|User|FollowUser", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="FollowUser") FGs2FriendOwnFollowUser OwnFollowUser(
        FGs2FriendOwnUser User,
        FString TargetUserId,
        bool WithProfile
    );

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Friend::OwnFriend", Category="Game Server Services|GS2-Friend|Namespace|User|Friend", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="Friend") FGs2FriendOwnFriend OwnFriend(
        FGs2FriendOwnUser User,
        bool WithProfile
    );

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Friend::OwnSendFriendRequest", Category="Game Server Services|GS2-Friend|Namespace|User|SendFriendRequest", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="SendFriendRequest") FGs2FriendOwnSendFriendRequest OwnSendFriendRequest(
        FGs2FriendOwnUser User,
        FString TargetUserId
    );

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Friend::OwnReceiveFriendRequest", Category="Game Server Services|GS2-Friend|Namespace|User|ReceiveFriendRequest", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="ReceiveFriendRequest") FGs2FriendOwnReceiveFriendRequest OwnReceiveFriendRequest(
        FGs2FriendOwnUser User,
        FString FromUserId
    );
};