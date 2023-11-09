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
#include "Inventory/Domain/Model/Gs2InventoryEzInventoryGameSessionDomain.h"
#include "Core/BpGs2Constant.h"
#include "Gs2InventoryInventory.generated.h"

USTRUCT(BlueprintType)
struct FGs2InventoryOwnInventory
{
    GENERATED_BODY()

    Gs2::UE5::Inventory::Domain::Model::FEzInventoryGameSessionDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2InventoryInventoryValue
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString InventoryId = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString InventoryName = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    int32 CurrentInventoryCapacityUsage = 0;
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    int32 CurrentInventoryMaxCapacity = 0;
};

inline FGs2InventoryInventoryValue EzInventoryToFGs2InventoryInventoryValue(
    const Gs2::UE5::Inventory::Model::FEzInventoryPtr Model
)
{
    FGs2InventoryInventoryValue Value;
    if (Model == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2InventoryInventoryFunctionLibrary::EzInventoryToFGs2InventoryInventoryValue] Model parameter specification is missing."))
        return Value;
    }
    Value.InventoryId = Model->GetInventoryId() ? *Model->GetInventoryId() : "";
    Value.InventoryName = Model->GetInventoryName() ? *Model->GetInventoryName() : "";
    Value.CurrentInventoryCapacityUsage = Model->GetCurrentInventoryCapacityUsage() ? *Model->GetCurrentInventoryCapacityUsage() : 0;
    Value.CurrentInventoryMaxCapacity = Model->GetCurrentInventoryMaxCapacity() ? *Model->GetCurrentInventoryMaxCapacity() : 0;
    return Value;
}

inline Gs2::UE5::Inventory::Model::FEzInventoryPtr FGs2InventoryInventoryValueToEzInventory(
    const FGs2InventoryInventoryValue Model
)
{
    return MakeShared<Gs2::UE5::Inventory::Model::FEzInventory>()
        ->WithInventoryId(Model.InventoryId)
        ->WithInventoryName(Model.InventoryName)
        ->WithCurrentInventoryCapacityUsage(Model.CurrentInventoryCapacityUsage)
        ->WithCurrentInventoryMaxCapacity(Model.CurrentInventoryMaxCapacity);
}

UCLASS()
class BPGS2_API UGs2InventoryInventoryFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Inventory::OwnItemSet", Category="Game Server Services|GS2-Inventory|Namespace|User|Inventory|ItemSet", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="ItemSet") FGs2InventoryOwnItemSet OwnItemSet(
        FGs2InventoryOwnInventory Inventory,
        FString ItemName,
        FString ItemSetName
    );
};