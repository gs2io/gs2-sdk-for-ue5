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
#include "Inventory/Domain/Model/Gs2InventoryEzSimpleItemGameSessionDomain.h"
#include "Core/BpGs2Constant.h"
#include "Gs2InventorySimpleItem.generated.h"

USTRUCT(BlueprintType)
struct FGs2InventoryOwnSimpleItem
{
    GENERATED_BODY()

    Gs2::UE5::Inventory::Domain::Model::FEzSimpleItemGameSessionDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2InventorySimpleItemValue
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly)
    FString ItemId = "";
    UPROPERTY(BlueprintReadOnly)
    FString ItemName = "";
    UPROPERTY(BlueprintReadOnly)
    int64 Count = 0;
};

inline FGs2InventorySimpleItemValue EzSimpleItemToFGs2InventorySimpleItemValue(
    const Gs2::UE5::Inventory::Model::FEzSimpleItemPtr Model
)
{
    FGs2InventorySimpleItemValue Value;
    if (Model == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2InventorySimpleItemFunctionLibrary::EzSimpleItemToFGs2InventorySimpleItemValue] Model parameter specification is missing."))
        return Value;
    }
    Value.ItemId = Model->GetItemId() ? *Model->GetItemId() : "";
    Value.ItemName = Model->GetItemName() ? *Model->GetItemName() : "";
    Value.Count = Model->GetCount() ? *Model->GetCount() : 0;
    return Value;
}

inline Gs2::UE5::Inventory::Model::FEzSimpleItemPtr FGs2InventorySimpleItemValueToEzSimpleItem(
    const FGs2InventorySimpleItemValue Model
)
{
    return MakeShared<Gs2::UE5::Inventory::Model::FEzSimpleItem>()
        ->WithItemId(Model.ItemId)
        ->WithItemName(Model.ItemName)
        ->WithCount(Model.Count);
}

UCLASS()
class BPGS2_API UGs2InventorySimpleItemFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};