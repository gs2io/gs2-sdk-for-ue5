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
#include "Stamina/Domain/Model/Gs2StaminaEzStaminaGameSessionDomain.h"
#include "Gs2StaminaStamina.generated.h"

USTRUCT(BlueprintType)
struct FGs2StaminaOwnStamina
{
    GENERATED_BODY()

    Gs2::UE5::Stamina::Domain::Model::FEzStaminaGameSessionDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2StaminaStaminaValue
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly)
    FString StaminaName = "";
    UPROPERTY(BlueprintReadOnly)
    int32 Value = 0;
    UPROPERTY(BlueprintReadOnly)
    int32 OverflowValue = 0;
    UPROPERTY(BlueprintReadOnly)
    int32 MaxValue = 0;
    UPROPERTY(BlueprintReadOnly)
    int32 RecoverIntervalMinutes = 0;
    UPROPERTY(BlueprintReadOnly)
    int32 RecoverValue = 0;
    UPROPERTY(BlueprintReadOnly)
    int64 NextRecoverAt = 0;
};

inline FGs2StaminaStaminaValue EzStaminaToFGs2StaminaStaminaValue(
    const Gs2::UE5::Stamina::Model::FEzStaminaPtr Model
)
{
    FGs2StaminaStaminaValue Value;
    Value.StaminaName = Model->GetStaminaName() ? *Model->GetStaminaName() : "";
    Value.Value = Model->GetValue() ? *Model->GetValue() : 0;
    Value.OverflowValue = Model->GetOverflowValue() ? *Model->GetOverflowValue() : 0;
    Value.MaxValue = Model->GetMaxValue() ? *Model->GetMaxValue() : 0;
    Value.RecoverIntervalMinutes = Model->GetRecoverIntervalMinutes() ? *Model->GetRecoverIntervalMinutes() : 0;
    Value.RecoverValue = Model->GetRecoverValue() ? *Model->GetRecoverValue() : 0;
    Value.NextRecoverAt = Model->GetNextRecoverAt() ? *Model->GetNextRecoverAt() : 0;
    return Value;
}

inline Gs2::UE5::Stamina::Model::FEzStaminaPtr FGs2StaminaStaminaValueToEzStamina(
    const FGs2StaminaStaminaValue Model
)
{
    return MakeShared<Gs2::UE5::Stamina::Model::FEzStamina>()
        ->WithStaminaName(Model.StaminaName)
        ->WithValue(Model.Value)
        ->WithOverflowValue(Model.OverflowValue)
        ->WithMaxValue(Model.MaxValue)
        ->WithRecoverIntervalMinutes(Model.RecoverIntervalMinutes)
        ->WithRecoverValue(Model.RecoverValue)
        ->WithNextRecoverAt(Model.NextRecoverAt);
}

UCLASS()
class BPGS2_API UGs2StaminaStaminaFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};