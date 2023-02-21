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
    class GS2INVENTORY_API FConsumeItemSetByStampTaskResult final : public TSharedFromThis<FConsumeItemSetByStampTaskResult>
    {
        TSharedPtr<TArray<TSharedPtr<Model::FItemSet>>> ItemsValue;
        TSharedPtr<Model::FItemModel> ItemModelValue;
        TSharedPtr<Model::FInventory> InventoryValue;
        TOptional<FString> NewContextStackValue;
        
    public:
        
        FConsumeItemSetByStampTaskResult();
        FConsumeItemSetByStampTaskResult(
            const FConsumeItemSetByStampTaskResult& From
        );
        ~FConsumeItemSetByStampTaskResult() = default;

        TSharedPtr<FConsumeItemSetByStampTaskResult> WithItems(const TSharedPtr<TArray<TSharedPtr<Model::FItemSet>>> Items);
        TSharedPtr<FConsumeItemSetByStampTaskResult> WithItemModel(const TSharedPtr<Model::FItemModel> ItemModel);
        TSharedPtr<FConsumeItemSetByStampTaskResult> WithInventory(const TSharedPtr<Model::FInventory> Inventory);
        TSharedPtr<FConsumeItemSetByStampTaskResult> WithNewContextStack(const TOptional<FString> NewContextStack);

        TSharedPtr<TArray<TSharedPtr<Model::FItemSet>>> GetItems() const;
        TSharedPtr<Model::FItemModel> GetItemModel() const;
        TSharedPtr<Model::FInventory> GetInventory() const;
        TOptional<FString> GetNewContextStack() const;

        static TSharedPtr<FConsumeItemSetByStampTaskResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FConsumeItemSetByStampTaskResult, ESPMode::ThreadSafe> FConsumeItemSetByStampTaskResultPtr;
}