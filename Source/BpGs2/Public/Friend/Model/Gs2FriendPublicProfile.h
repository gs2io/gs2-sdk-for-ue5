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
#include "Friend/Domain/Model/Gs2FriendEzPublicProfileDomain.h"
#include "Core/BpGs2Constant.h"
#include "Gs2FriendPublicProfile.generated.h"

USTRUCT(BlueprintType)
struct FGs2FriendPublicProfile
{
    GENERATED_BODY()

    Gs2::UE5::Friend::Domain::Model::FEzPublicProfileDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2FriendPublicProfileValue
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString UserId = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString PublicProfile = "";
};

inline FGs2FriendPublicProfileValue EzPublicProfileToFGs2FriendPublicProfileValue(
    const Gs2::UE5::Friend::Model::FEzPublicProfilePtr Model
)
{
    FGs2FriendPublicProfileValue Value;
    if (Model == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2FriendPublicProfileFunctionLibrary::EzPublicProfileToFGs2FriendPublicProfileValue] Model parameter specification is missing."))
        return Value;
    }
    Value.UserId = Model->GetUserId() ? *Model->GetUserId() : "";
    Value.PublicProfile = Model->GetPublicProfile() ? *Model->GetPublicProfile() : "";
    return Value;
}

inline Gs2::UE5::Friend::Model::FEzPublicProfilePtr FGs2FriendPublicProfileValueToEzPublicProfile(
    const FGs2FriendPublicProfileValue Model
)
{
    return MakeShared<Gs2::UE5::Friend::Model::FEzPublicProfile>()
        ->WithUserId(Model.UserId)
        ->WithPublicProfile(Model.PublicProfile);
}

UCLASS()
class BPGS2_API UGs2FriendPublicProfileFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};