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
#include "Inventory/Domain/Model/Gs2InventoryEzItemModelDomain.h"
#include "Gs2InventoryItemModel.generated.h"

USTRUCT(BlueprintType)
struct FGs2InventoryItemModel
{
    GENERATED_BODY()

    Gs2::UE5::Inventory::Domain::Model::FEzItemModelDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2InventoryItemModelValue
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly)
    FString Name = "";
    UPROPERTY(BlueprintReadOnly)
    FString Metadata = "";
    UPROPERTY(BlueprintReadOnly)
    int64 StackingLimit = 0;
    UPROPERTY(BlueprintReadOnly)
    bool AllowMultipleStacks = false;
    UPROPERTY(BlueprintReadOnly)
    int32 SortValue = 0;
};

inline FGs2InventoryItemModelValue EzItemModelToFGs2InventoryItemModelValue(
    const Gs2::UE5::Inventory::Model::FEzItemModelPtr Model
)
{
    FGs2InventoryItemModelValue Value;
    Value.Name = Model->GetName() ? *Model->GetName() : "";
    Value.Metadata = Model->GetMetadata() ? *Model->GetMetadata() : "";
    Value.StackingLimit = Model->GetStackingLimit() ? *Model->GetStackingLimit() : 0;
    Value.AllowMultipleStacks = Model->GetAllowMultipleStacks() ? *Model->GetAllowMultipleStacks() : false;
    Value.SortValue = Model->GetSortValue() ? *Model->GetSortValue() : 0;
    return Value;
}

inline Gs2::UE5::Inventory::Model::FEzItemModelPtr FGs2InventoryItemModelValueToEzItemModel(
    const FGs2InventoryItemModelValue Model
)
{
    return MakeShared<Gs2::UE5::Inventory::Model::FEzItemModel>()
        ->WithName(Model.Name)
        ->WithMetadata(Model.Metadata)
        ->WithStackingLimit(Model.StackingLimit)
        ->WithAllowMultipleStacks(Model.AllowMultipleStacks)
        ->WithSortValue(Model.SortValue);
}

UCLASS()
class BPGS2_API UGs2InventoryItemModelFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};