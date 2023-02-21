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
#include "Friend/Domain/Model/Gs2FriendEzFriendUserGameSessionDomain.h"
#include "Gs2FriendFriendUser.generated.h"

USTRUCT(BlueprintType)
struct FGs2FriendOwnFriendUser
{
    GENERATED_BODY()

    Gs2::UE5::Friend::Domain::Model::FEzFriendUserGameSessionDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2FriendFriendUserValue
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly)
    FString UserId = "";
    UPROPERTY(BlueprintReadOnly)
    FString PublicProfile = "";
    UPROPERTY(BlueprintReadOnly)
    FString FriendProfile = "";
};

inline FGs2FriendFriendUserValue EzFriendUserToFGs2FriendFriendUserValue(
    const Gs2::UE5::Friend::Model::FEzFriendUserPtr Model
)
{
    FGs2FriendFriendUserValue Value;
    Value.UserId = Model->GetUserId() ? *Model->GetUserId() : "";
    Value.PublicProfile = Model->GetPublicProfile() ? *Model->GetPublicProfile() : "";
    Value.FriendProfile = Model->GetFriendProfile() ? *Model->GetFriendProfile() : "";
    return Value;
}

inline Gs2::UE5::Friend::Model::FEzFriendUserPtr FGs2FriendFriendUserValueToEzFriendUser(
    const FGs2FriendFriendUserValue Model
)
{
    return MakeShared<Gs2::UE5::Friend::Model::FEzFriendUser>()
        ->WithUserId(Model.UserId)
        ->WithPublicProfile(Model.PublicProfile)
        ->WithFriendProfile(Model.FriendProfile);
}

UCLASS()
class BPGS2_API UGs2FriendFriendUserFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};