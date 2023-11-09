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
#include "Inventory/Domain/Model/Gs2InventoryEzInventoryModelDomain.h"
#include "Core/BpGs2Constant.h"
#include "Gs2InventoryInventoryModel.generated.h"

USTRUCT(BlueprintType)
struct FGs2InventoryInventoryModel
{
    GENERATED_BODY()

    Gs2::UE5::Inventory::Domain::Model::FEzInventoryModelDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2InventoryInventoryModelValue
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString Name = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString Metadata = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    int32 InitialCapacity = 0;
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    int32 MaxCapacity = 0;
};

inline FGs2InventoryInventoryModelValue EzInventoryModelToFGs2InventoryInventoryModelValue(
    const Gs2::UE5::Inventory::Model::FEzInventoryModelPtr Model
)
{
    FGs2InventoryInventoryModelValue Value;
    if (Model == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2InventoryInventoryModelFunctionLibrary::EzInventoryModelToFGs2InventoryInventoryModelValue] Model parameter specification is missing."))
        return Value;
    }
    Value.Name = Model->GetName() ? *Model->GetName() : "";
    Value.Metadata = Model->GetMetadata() ? *Model->GetMetadata() : "";
    Value.InitialCapacity = Model->GetInitialCapacity() ? *Model->GetInitialCapacity() : 0;
    Value.MaxCapacity = Model->GetMaxCapacity() ? *Model->GetMaxCapacity() : 0;
    return Value;
}

inline Gs2::UE5::Inventory::Model::FEzInventoryModelPtr FGs2InventoryInventoryModelValueToEzInventoryModel(
    const FGs2InventoryInventoryModelValue Model
)
{
    return MakeShared<Gs2::UE5::Inventory::Model::FEzInventoryModel>()
        ->WithName(Model.Name)
        ->WithMetadata(Model.Metadata)
        ->WithInitialCapacity(Model.InitialCapacity)
        ->WithMaxCapacity(Model.MaxCapacity);
}

UCLASS()
class BPGS2_API UGs2InventoryInventoryModelFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Inventory::ItemModel", Category="Game Server Services|GS2-Inventory|Namespace|InventoryModel|ItemModel", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="ItemModel") FGs2InventoryItemModel ItemModel(
        FGs2InventoryInventoryModel InventoryModel,
        FString ItemName
    );
};