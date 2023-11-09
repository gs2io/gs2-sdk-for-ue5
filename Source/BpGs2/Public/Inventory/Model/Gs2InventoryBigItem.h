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
#include "Inventory/Domain/Model/Gs2InventoryEzBigItemGameSessionDomain.h"
#include "Core/BpGs2Constant.h"
#include "Gs2InventoryBigItem.generated.h"

USTRUCT(BlueprintType)
struct FGs2InventoryOwnBigItem
{
    GENERATED_BODY()

    Gs2::UE5::Inventory::Domain::Model::FEzBigItemGameSessionDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2InventoryBigItemValue
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString ItemId = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString ItemName = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString Count = "";
};

inline FGs2InventoryBigItemValue EzBigItemToFGs2InventoryBigItemValue(
    const Gs2::UE5::Inventory::Model::FEzBigItemPtr Model
)
{
    FGs2InventoryBigItemValue Value;
    if (Model == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2InventoryBigItemFunctionLibrary::EzBigItemToFGs2InventoryBigItemValue] Model parameter specification is missing."))
        return Value;
    }
    Value.ItemId = Model->GetItemId() ? *Model->GetItemId() : "";
    Value.ItemName = Model->GetItemName() ? *Model->GetItemName() : "";
    Value.Count = Model->GetCount() ? *Model->GetCount() : "";
    return Value;
}

inline Gs2::UE5::Inventory::Model::FEzBigItemPtr FGs2InventoryBigItemValueToEzBigItem(
    const FGs2InventoryBigItemValue Model
)
{
    return MakeShared<Gs2::UE5::Inventory::Model::FEzBigItem>()
        ->WithItemId(Model.ItemId)
        ->WithItemName(Model.ItemName)
        ->WithCount(Model.Count);
}

UCLASS()
class BPGS2_API UGs2InventoryBigItemFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};