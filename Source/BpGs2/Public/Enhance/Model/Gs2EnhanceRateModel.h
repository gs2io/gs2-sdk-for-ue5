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
#include "Enhance/Domain/Model/Gs2EnhanceEzRateModelDomain.h"
#include "Gs2EnhanceRateModel.generated.h"

USTRUCT(BlueprintType)
struct FGs2EnhanceRateModel
{
    GENERATED_BODY()

    Gs2::UE5::Enhance::Domain::Model::FEzRateModelDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2EnhanceRateModelValue
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly)
    FString Name = "";
    UPROPERTY(BlueprintReadOnly)
    FString Metadata = "";
    UPROPERTY(BlueprintReadOnly)
    FString TargetInventoryModelId = "";
    UPROPERTY(BlueprintReadOnly)
    FString AcquireExperienceSuffix = "";
    UPROPERTY(BlueprintReadOnly)
    FString MaterialInventoryModelId = "";
    UPROPERTY(BlueprintReadOnly)
    FString ExperienceModelId = "";
};

inline FGs2EnhanceRateModelValue EzRateModelToFGs2EnhanceRateModelValue(
    const Gs2::UE5::Enhance::Model::FEzRateModelPtr Model
)
{
    FGs2EnhanceRateModelValue Value;
    Value.Name = Model->GetName() ? *Model->GetName() : "";
    Value.Metadata = Model->GetMetadata() ? *Model->GetMetadata() : "";
    Value.TargetInventoryModelId = Model->GetTargetInventoryModelId() ? *Model->GetTargetInventoryModelId() : "";
    Value.AcquireExperienceSuffix = Model->GetAcquireExperienceSuffix() ? *Model->GetAcquireExperienceSuffix() : "";
    Value.MaterialInventoryModelId = Model->GetMaterialInventoryModelId() ? *Model->GetMaterialInventoryModelId() : "";
    Value.ExperienceModelId = Model->GetExperienceModelId() ? *Model->GetExperienceModelId() : "";
    return Value;
}

inline Gs2::UE5::Enhance::Model::FEzRateModelPtr FGs2EnhanceRateModelValueToEzRateModel(
    const FGs2EnhanceRateModelValue Model
)
{
    return MakeShared<Gs2::UE5::Enhance::Model::FEzRateModel>()
        ->WithName(Model.Name)
        ->WithMetadata(Model.Metadata)
        ->WithTargetInventoryModelId(Model.TargetInventoryModelId)
        ->WithAcquireExperienceSuffix(Model.AcquireExperienceSuffix)
        ->WithMaterialInventoryModelId(Model.MaterialInventoryModelId)
        ->WithExperienceModelId(Model.ExperienceModelId);
}

UCLASS()
class BPGS2_API UGs2EnhanceRateModelFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};