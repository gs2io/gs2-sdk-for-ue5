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
#include "Friend/Domain/Model/Gs2FriendEzProfileGameSessionDomain.h"
#include "Core/BpGs2Constant.h"
#include "Gs2FriendProfile.generated.h"

USTRUCT(BlueprintType)
struct FGs2FriendOwnProfile
{
    GENERATED_BODY()

    Gs2::UE5::Friend::Domain::Model::FEzProfileGameSessionDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2FriendProfileValue
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly)
    FString UserId = "";
    UPROPERTY(BlueprintReadOnly)
    FString PublicProfile = "";
    UPROPERTY(BlueprintReadOnly)
    FString FollowerProfile = "";
    UPROPERTY(BlueprintReadOnly)
    FString FriendProfile = "";
};

inline FGs2FriendProfileValue EzProfileToFGs2FriendProfileValue(
    const Gs2::UE5::Friend::Model::FEzProfilePtr Model
)
{
    FGs2FriendProfileValue Value;
    if (Model == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2FriendProfileFunctionLibrary::EzProfileToFGs2FriendProfileValue] Model parameter specification is missing."))
        return Value;
    }
    Value.UserId = Model->GetUserId() ? *Model->GetUserId() : "";
    Value.PublicProfile = Model->GetPublicProfile() ? *Model->GetPublicProfile() : "";
    Value.FollowerProfile = Model->GetFollowerProfile() ? *Model->GetFollowerProfile() : "";
    Value.FriendProfile = Model->GetFriendProfile() ? *Model->GetFriendProfile() : "";
    return Value;
}

inline Gs2::UE5::Friend::Model::FEzProfilePtr FGs2FriendProfileValueToEzProfile(
    const FGs2FriendProfileValue Model
)
{
    return MakeShared<Gs2::UE5::Friend::Model::FEzProfile>()
        ->WithUserId(Model.UserId)
        ->WithPublicProfile(Model.PublicProfile)
        ->WithFollowerProfile(Model.FollowerProfile)
        ->WithFriendProfile(Model.FriendProfile);
}

UCLASS()
class BPGS2_API UGs2FriendProfileFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};