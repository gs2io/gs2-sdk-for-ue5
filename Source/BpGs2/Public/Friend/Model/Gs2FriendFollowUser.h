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
#include "Friend/Domain/Model/Gs2FriendEzFollowUserGameSessionDomain.h"
#include "Core/BpGs2Constant.h"
#include "Gs2FriendFollowUser.generated.h"

USTRUCT(BlueprintType)
struct FGs2FriendOwnFollowUser
{
    GENERATED_BODY()

    Gs2::UE5::Friend::Domain::Model::FEzFollowUserGameSessionDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2FriendFollowUserValue
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString UserId = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString PublicProfile = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString FollowerProfile = "";
};

inline FGs2FriendFollowUserValue EzFollowUserToFGs2FriendFollowUserValue(
    const Gs2::UE5::Friend::Model::FEzFollowUserPtr Model
)
{
    FGs2FriendFollowUserValue Value;
    if (Model == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2FriendFollowUserFunctionLibrary::EzFollowUserToFGs2FriendFollowUserValue] Model parameter specification is missing."))
        return Value;
    }
    Value.UserId = Model->GetUserId() ? *Model->GetUserId() : "";
    Value.PublicProfile = Model->GetPublicProfile() ? *Model->GetPublicProfile() : "";
    Value.FollowerProfile = Model->GetFollowerProfile() ? *Model->GetFollowerProfile() : "";
    return Value;
}

inline Gs2::UE5::Friend::Model::FEzFollowUserPtr FGs2FriendFollowUserValueToEzFollowUser(
    const FGs2FriendFollowUserValue Model
)
{
    return MakeShared<Gs2::UE5::Friend::Model::FEzFollowUser>()
        ->WithUserId(Model.UserId)
        ->WithPublicProfile(Model.PublicProfile)
        ->WithFollowerProfile(Model.FollowerProfile);
}

UCLASS()
class BPGS2_API UGs2FriendFollowUserFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};