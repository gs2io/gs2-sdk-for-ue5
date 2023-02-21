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
#include "../Model/ItemSet.h"
#include "../Model/ItemModel.h"
#include "../Model/Inventory.h"

namespace Gs2::Inventory::Result
{
    class GS2INVENTORY_API FAcquireItemSetByUserIdResult final : public TSharedFromThis<FAcquireItemSetByUserIdResult>
    {
        TSharedPtr<TArray<TSharedPtr<Model::FItemSet>>> ItemsValue;
        TSharedPtr<Model::FItemModel> ItemModelValue;
        TSharedPtr<Model::FInventory> InventoryValue;
        TOptional<int64> OverflowCountValue;
        
    public:
        
        FAcquireItemSetByUserIdResult();
        FAcquireItemSetByUserIdResult(
            const FAcquireItemSetByUserIdResult& From
        );
        ~FAcquireItemSetByUserIdResult() = default;

        TSharedPtr<FAcquireItemSetByUserIdResult> WithItems(const TSharedPtr<TArray<TSharedPtr<Model::FItemSet>>> Items);
        TSharedPtr<FAcquireItemSetByUserIdResult> WithItemModel(const TSharedPtr<Model::FItemModel> ItemModel);
        TSharedPtr<FAcquireItemSetByUserIdResult> WithInventory(const TSharedPtr<Model::FInventory> Inventory);
        TSharedPtr<FAcquireItemSetByUserIdResult> WithOverflowCount(const TOptional<int64> OverflowCount);

        TSharedPtr<TArray<TSharedPtr<Model::FItemSet>>> GetItems() const;
        TSharedPtr<Model::FItemModel> GetItemModel() const;
        TSharedPtr<Model::FInventory> GetInventory() const;
        TOptional<int64> GetOverflowCount() const;
        FString GetOverflowCountString() const;

        static TSharedPtr<FAcquireItemSetByUserIdResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FAcquireItemSetByUserIdResult, ESPMode::ThreadSafe> FAcquireItemSetByUserIdResultPtr;
}