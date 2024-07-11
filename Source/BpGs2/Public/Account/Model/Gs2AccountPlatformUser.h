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

#include "Account/Model/Gs2AccountEzPlatformUser.h"
#include "Gs2AccountPlatformUser.generated.h"

USTRUCT(BlueprintType)
struct FGs2AccountPlatformUser
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    int32 Type = 0;
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString UserIdentifier = "";
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString UserId = "";
};

inline FGs2AccountPlatformUser EzPlatformUserToFGs2AccountPlatformUser(
    const Gs2::UE5::Account::Model::FEzPlatformUserPtr Model
)
{
    FGs2AccountPlatformUser Value;
    Value.Type = Model->GetType() ? *Model->GetType() : 0;
    Value.UserIdentifier = Model->GetUserIdentifier() ? *Model->GetUserIdentifier() : "";
    Value.UserId = Model->GetUserId() ? *Model->GetUserId() : "";
    return Value;
}

inline Gs2::UE5::Account::Model::FEzPlatformUserPtr FGs2AccountPlatformUserToEzPlatformUser(
    const FGs2AccountPlatformUser Model
)
{
    return MakeShared<Gs2::UE5::Account::Model::FEzPlatformUser>()
        ->WithType(Model.Type)
        ->WithUserIdentifier(Model.UserIdentifier)
        ->WithUserId(Model.UserId);
}