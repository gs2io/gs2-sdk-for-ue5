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
#include "MegaField/Domain/Model/Gs2MegaFieldEzLayerModelDomain.h"
#include "Core/BpGs2Constant.h"
#include "Gs2MegaFieldLayerModel.generated.h"

USTRUCT(BlueprintType)
struct FGs2MegaFieldLayerModel
{
    GENERATED_BODY()

    Gs2::UE5::MegaField::Domain::Model::FEzLayerModelDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2MegaFieldLayerModelValue
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly)
    FString Name = "";
    UPROPERTY(BlueprintReadOnly)
    FString Metadata = "";
};

inline FGs2MegaFieldLayerModelValue EzLayerModelToFGs2MegaFieldLayerModelValue(
    const Gs2::UE5::MegaField::Model::FEzLayerModelPtr Model
)
{
    FGs2MegaFieldLayerModelValue Value;
    if (Model == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2MegaFieldLayerModelFunctionLibrary::EzLayerModelToFGs2MegaFieldLayerModelValue] Model parameter specification is missing."))
        return Value;
    }
    Value.Name = Model->GetName() ? *Model->GetName() : "";
    Value.Metadata = Model->GetMetadata() ? *Model->GetMetadata() : "";
    return Value;
}

inline Gs2::UE5::MegaField::Model::FEzLayerModelPtr FGs2MegaFieldLayerModelValueToEzLayerModel(
    const FGs2MegaFieldLayerModelValue Model
)
{
    return MakeShared<Gs2::UE5::MegaField::Model::FEzLayerModel>()
        ->WithName(Model.Name)
        ->WithMetadata(Model.Metadata);
}

UCLASS()
class BPGS2_API UGs2MegaFieldLayerModelFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};