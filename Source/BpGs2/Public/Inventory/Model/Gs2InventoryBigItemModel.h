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
#include "Inventory/Domain/Model/Gs2InventoryEzBigItemModelDomain.h"
#include "Core/BpGs2Constant.h"
#include "Gs2InventoryBigItemModel.generated.h"

USTRUCT(BlueprintType)
struct FGs2InventoryBigItemModel
{
    GENERATED_BODY()

    Gs2::UE5::Inventory::Domain::Model::FEzBigItemModelDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2InventoryBigItemModelValue
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly)
    FString Name = "";
    UPROPERTY(BlueprintReadOnly)
    FString Metadata = "";
};

inline FGs2InventoryBigItemModelValue EzBigItemModelToFGs2InventoryBigItemModelValue(
    const Gs2::UE5::Inventory::Model::FEzBigItemModelPtr Model
)
{
    FGs2InventoryBigItemModelValue Value;
    if (Model == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2InventoryBigItemModelFunctionLibrary::EzBigItemModelToFGs2InventoryBigItemModelValue] Model parameter specification is missing."))
        return Value;
    }
    Value.Name = Model->GetName() ? *Model->GetName() : "";
    Value.Metadata = Model->GetMetadata() ? *Model->GetMetadata() : "";
    return Value;
}

inline Gs2::UE5::Inventory::Model::FEzBigItemModelPtr FGs2InventoryBigItemModelValueToEzBigItemModel(
    const FGs2InventoryBigItemModelValue Model
)
{
    return MakeShared<Gs2::UE5::Inventory::Model::FEzBigItemModel>()
        ->WithName(Model.Name)
        ->WithMetadata(Model.Metadata);
}

UCLASS()
class BPGS2_API UGs2InventoryBigItemModelFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};