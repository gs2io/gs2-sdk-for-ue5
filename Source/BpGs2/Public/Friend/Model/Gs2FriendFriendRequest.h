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

#include "Friend/Model/Gs2FriendEzFriendRequest.h"
#include "Gs2FriendFriendRequest.generated.h"

USTRUCT(BlueprintType)
struct FGs2FriendFriendRequest
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString UserId = "";
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString TargetUserId = "";
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString PublicProfile = "";
};

inline FGs2FriendFriendRequest EzFriendRequestToFGs2FriendFriendRequest(
    const Gs2::UE5::Friend::Model::FEzFriendRequestPtr Model
)
{
    FGs2FriendFriendRequest Value;
    Value.UserId = Model->GetUserId() ? *Model->GetUserId() : "";
    Value.TargetUserId = Model->GetTargetUserId() ? *Model->GetTargetUserId() : "";
    Value.PublicProfile = Model->GetPublicProfile() ? *Model->GetPublicProfile() : "";
    return Value;
}

inline Gs2::UE5::Friend::Model::FEzFriendRequestPtr FGs2FriendFriendRequestToEzFriendRequest(
    const FGs2FriendFriendRequest Model
)
{
    return MakeShared<Gs2::UE5::Friend::Model::FEzFriendRequest>()
        ->WithUserId(Model.UserId)
        ->WithTargetUserId(Model.TargetUserId)
        ->WithPublicProfile(Model.PublicProfile);
}