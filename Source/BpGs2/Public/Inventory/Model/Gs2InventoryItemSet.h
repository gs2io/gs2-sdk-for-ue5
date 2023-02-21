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
#include "Inventory/Domain/Model/Gs2InventoryEzItemSetGameSessionDomain.h"
#include "Gs2InventoryItemSet.generated.h"

USTRUCT(BlueprintType)
struct FGs2InventoryOwnItemSet
{
    GENERATED_BODY()

    Gs2::UE5::Inventory::Domain::Model::FEzItemSetGameSessionDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2InventoryItemSetValue
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly)
    FString ItemSetId = "";
    UPROPERTY(BlueprintReadOnly)
    FString Name = "";
    UPROPERTY(BlueprintReadOnly)
    FString InventoryName = "";
    UPROPERTY(BlueprintReadOnly)
    FString ItemName = "";
    UPROPERTY(BlueprintReadOnly)
    int64 Count = 0;
    UPROPERTY(BlueprintReadOnly)
    int32 SortValue = 0;
    UPROPERTY(BlueprintReadOnly)
    int64 ExpiresAt = 0;
};

inline FGs2InventoryItemSetValue EzItemSetToFGs2InventoryItemSetValue(
    const Gs2::UE5::Inventory::Model::FEzItemSetPtr Model
)
{
    FGs2InventoryItemSetValue Value;
    Value.ItemSetId = Model->GetItemSetId() ? *Model->GetItemSetId() : "";
    Value.Name = Model->GetName() ? *Model->GetName() : "";
    Value.InventoryName = Model->GetInventoryName() ? *Model->GetInventoryName() : "";
    Value.ItemName = Model->GetItemName() ? *Model->GetItemName() : "";
    Value.Count = Model->GetCount() ? *Model->GetCount() : 0;
    Value.SortValue = Model->GetSortValue() ? *Model->GetSortValue() : 0;
    Value.ExpiresAt = Model->GetExpiresAt() ? *Model->GetExpiresAt() : 0;
    return Value;
}

inline Gs2::UE5::Inventory::Model::FEzItemSetPtr FGs2InventoryItemSetValueToEzItemSet(
    const FGs2InventoryItemSetValue Model
)
{
    return MakeShared<Gs2::UE5::Inventory::Model::FEzItemSet>()
        ->WithItemSetId(Model.ItemSetId)
        ->WithName(Model.Name)
        ->WithInventoryName(Model.InventoryName)
        ->WithItemName(Model.ItemName)
        ->WithCount(Model.Count)
        ->WithSortValue(Model.SortValue)
        ->WithExpiresAt(Model.ExpiresAt);
}

UCLASS()
class BPGS2_API UGs2InventoryItemSetFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};