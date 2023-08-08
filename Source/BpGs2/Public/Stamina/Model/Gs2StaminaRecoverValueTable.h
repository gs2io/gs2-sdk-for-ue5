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

#include "Stamina/Model/Gs2StaminaEzRecoverValueTable.h"
#include "Gs2StaminaRecoverValueTable.generated.h"

USTRUCT(BlueprintType)
struct FGs2StaminaRecoverValueTable
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite)
    FString Name = "";
    UPROPERTY(BlueprintReadWrite)
    FString Metadata = "";
    UPROPERTY(BlueprintReadWrite)
    FString ExperienceModelId = "";
    UPROPERTY(BlueprintReadWrite)
    TArray<int32> Values = TArray<int32>();
};

inline FGs2StaminaRecoverValueTable EzRecoverValueTableToFGs2StaminaRecoverValueTable(
    const Gs2::UE5::Stamina::Model::FEzRecoverValueTablePtr Model
)
{
    FGs2StaminaRecoverValueTable Value;
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

inline Gs2::UE5::Stamina::Model::FEzRecoverValueTablePtr FGs2StaminaRecoverValueTableToEzRecoverValueTable(
    const FGs2StaminaRecoverValueTable Model
)
{
    return MakeShared<Gs2::UE5::Stamina::Model::FEzRecoverValueTable>()
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