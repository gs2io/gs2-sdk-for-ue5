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
    class GS2INVENTORY_API FConsumeItemSetByUserIdResult final : public TSharedFromThis<FConsumeItemSetByUserIdResult>
    {
        TSharedPtr<TArray<TSharedPtr<Model::FItemSet>>> ItemsValue;
        TSharedPtr<Model::FItemModel> ItemModelValue;
        TSharedPtr<Model::FInventory> InventoryValue;
        
    public:
        
        FConsumeItemSetByUserIdResult();
        FConsumeItemSetByUserIdResult(
            const FConsumeItemSetByUserIdResult& From
        );
        ~FConsumeItemSetByUserIdResult() = default;

        TSharedPtr<FConsumeItemSetByUserIdResult> WithItems(const TSharedPtr<TArray<TSharedPtr<Model::FItemSet>>> Items);
        TSharedPtr<FConsumeItemSetByUserIdResult> WithItemModel(const TSharedPtr<Model::FItemModel> ItemModel);
        TSharedPtr<FConsumeItemSetByUserIdResult> WithInventory(const TSharedPtr<Model::FInventory> Inventory);

        TSharedPtr<TArray<TSharedPtr<Model::FItemSet>>> GetItems() const;
        TSharedPtr<Model::FItemModel> GetItemModel() const;
        TSharedPtr<Model::FInventory> GetInventory() const;

        static TSharedPtr<FConsumeItemSetByUserIdResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FConsumeItemSetByUserIdResult, ESPMode::ThreadSafe> FConsumeItemSetByUserIdResultPtr;
}