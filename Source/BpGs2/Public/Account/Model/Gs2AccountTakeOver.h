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
#include "Account/Domain/Model/Gs2AccountEzTakeOverGameSessionDomain.h"
#include "Account/Domain/Model/Gs2AccountEzTakeOverDomain.h"
#include "Core/BpGs2Constant.h"
#include "Gs2AccountTakeOver.generated.h"

USTRUCT(BlueprintType)
struct FGs2AccountOwnTakeOver
{
    GENERATED_BODY()

    Gs2::UE5::Account::Domain::Model::FEzTakeOverGameSessionDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2AccountTakeOver
{
    GENERATED_BODY()

    Gs2::UE5::Account::Domain::Model::FEzTakeOverDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2AccountTakeOverValue
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString UserId = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    int32 Type = 0;
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString UserIdentifier = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    int64 CreatedAt = 0;
};

inline FGs2AccountTakeOverValue EzTakeOverToFGs2AccountTakeOverValue(
    const Gs2::UE5::Account::Model::FEzTakeOverPtr Model
)
{
    FGs2AccountTakeOverValue Value;
    if (Model == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2AccountTakeOverFunctionLibrary::EzTakeOverToFGs2AccountTakeOverValue] Model parameter specification is missing."))
        return Value;
    }
    Value.UserId = Model->GetUserId() ? *Model->GetUserId() : "";
    Value.Type = Model->GetType() ? *Model->GetType() : 0;
    Value.UserIdentifier = Model->GetUserIdentifier() ? *Model->GetUserIdentifier() : "";
    Value.CreatedAt = Model->GetCreatedAt() ? *Model->GetCreatedAt() : 0;
    return Value;
}

inline Gs2::UE5::Account::Model::FEzTakeOverPtr FGs2AccountTakeOverValueToEzTakeOver(
    const FGs2AccountTakeOverValue Model
)
{
    return MakeShared<Gs2::UE5::Account::Model::FEzTakeOver>()
        ->WithUserId(Model.UserId)
        ->WithType(Model.Type)
        ->WithUserIdentifier(Model.UserIdentifier)
        ->WithCreatedAt(Model.CreatedAt);
}

UCLASS()
class BPGS2_API UGs2AccountTakeOverFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};