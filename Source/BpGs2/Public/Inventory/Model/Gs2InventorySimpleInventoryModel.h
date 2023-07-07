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
#include "Inventory/Domain/Model/Gs2InventoryEzSimpleInventoryModelDomain.h"
#include "Core/BpGs2Constant.h"
#include "Gs2InventorySimpleInventoryModel.generated.h"

USTRUCT(BlueprintType)
struct FGs2InventorySimpleInventoryModel
{
    GENERATED_BODY()

    Gs2::UE5::Inventory::Domain::Model::FEzSimpleInventoryModelDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2InventorySimpleInventoryModelValue
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly)
    FString Name = "";
    UPROPERTY(BlueprintReadOnly)
    FString Metadata = "";
};

inline FGs2InventorySimpleInventoryModelValue EzSimpleInventoryModelToFGs2InventorySimpleInventoryModelValue(
    const Gs2::UE5::Inventory::Model::FEzSimpleInventoryModelPtr Model
)
{
    FGs2InventorySimpleInventoryModelValue Value;
    if (Model == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2InventorySimpleInventoryModelFunctionLibrary::EzSimpleInventoryModelToFGs2InventorySimpleInventoryModelValue] Model parameter specification is missing."))
        return Value;
    }
    Value.Name = Model->GetName() ? *Model->GetName() : "";
    Value.Metadata = Model->GetMetadata() ? *Model->GetMetadata() : "";
    return Value;
}

inline Gs2::UE5::Inventory::Model::FEzSimpleInventoryModelPtr FGs2InventorySimpleInventoryModelValueToEzSimpleInventoryModel(
    const FGs2InventorySimpleInventoryModelValue Model
)
{
    return MakeShared<Gs2::UE5::Inventory::Model::FEzSimpleInventoryModel>()
        ->WithName(Model.Name)
        ->WithMetadata(Model.Metadata);
}

UCLASS()
class BPGS2_API UGs2InventorySimpleInventoryModelFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Inventory::SimpleItemModel", Category="Game Server Services|GS2-Inventory|Namespace|SimpleInventoryModel|SimpleItemModel", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="SimpleItemModel") FGs2InventorySimpleItemModel SimpleItemModel(
        FGs2InventorySimpleInventoryModel SimpleInventoryModel,
        FString ItemName
    );
};