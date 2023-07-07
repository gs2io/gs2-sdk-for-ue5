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

#include "Inventory/Model/Gs2InventoryEzAcquireCount.h"
#include "Gs2InventoryAcquireCount.generated.h"

USTRUCT(BlueprintType)
struct FGs2InventoryAcquireCount
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite)
    FString ItemName = "";
    UPROPERTY(BlueprintReadWrite)
    int64 Count = 0;
};

inline FGs2InventoryAcquireCount EzAcquireCountToFGs2InventoryAcquireCount(
    const Gs2::UE5::Inventory::Model::FEzAcquireCountPtr Model
)
{
    FGs2InventoryAcquireCount Value;
    Value.ItemName = Model->GetItemName() ? *Model->GetItemName() : "";
    Value.Count = Model->GetCount() ? *Model->GetCount() : 0;
    return Value;
}

inline Gs2::UE5::Inventory::Model::FEzAcquireCountPtr FGs2InventoryAcquireCountToEzAcquireCount(
    const FGs2InventoryAcquireCount Model
)
{
    return MakeShared<Gs2::UE5::Inventory::Model::FEzAcquireCount>()
        ->WithItemName(Model.ItemName)
        ->WithCount(Model.Count);
}