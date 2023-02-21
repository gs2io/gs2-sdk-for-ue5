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

#include "Stamina/Model/Gs2StaminaEzMaxStaminaTable.h"
#include "Gs2StaminaMaxStaminaTable.generated.h"

USTRUCT(BlueprintType)
struct FGs2StaminaMaxStaminaTable
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite)
    FString MaxStaminaTableId = "";
    UPROPERTY(BlueprintReadWrite)
    FString Name = "";
    UPROPERTY(BlueprintReadWrite)
    FString Metadata = "";
    UPROPERTY(BlueprintReadWrite)
    FString ExperienceModelId = "";
    UPROPERTY(BlueprintReadWrite)
    TArray<int32> Values = TArray<int32>();
};

inline FGs2StaminaMaxStaminaTable EzMaxStaminaTableToFGs2StaminaMaxStaminaTable(
    const Gs2::UE5::Stamina::Model::FEzMaxStaminaTablePtr Model
)
{
    FGs2StaminaMaxStaminaTable Value;
    Value.Name = Model->GetName() ? *Model->GetName() : "";
    Value.Metadata = Model->GetMetadata() ? *Model->GetMetadata() : "";
    Value.ExperienceModelId = Model->GetExperienceModelId() ? *Model->GetExperienceModelId() : "";
    Value.Values = Model->GetValues() ? [&]
    {
        TArray<int32> r;
        for (auto v : *Model->GetValues())
        {
            r.Add(v);
        }
        return r;
    }() : TArray<int32>();
    return Value;
}

inline Gs2::UE5::Stamina::Model::FEzMaxStaminaTablePtr FGs2StaminaMaxStaminaTableToEzMaxStaminaTable(
    const FGs2StaminaMaxStaminaTable Model
)
{
    return MakeShared<Gs2::UE5::Stamina::Model::FEzMaxStaminaTable>()
        ->WithName(Model.Name)
        ->WithMetadata(Model.Metadata)
        ->WithExperienceModelId(Model.ExperienceModelId)
        ->WithValues([&]{
            auto r = MakeShared<TArray<int32>>();
            for (auto v : Model.Values) {
                r->Add(v);
            }
            return r;
        }());
}