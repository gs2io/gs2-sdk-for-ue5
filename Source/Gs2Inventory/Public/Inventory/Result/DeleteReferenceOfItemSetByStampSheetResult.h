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
    class GS2INVENTORY_API FDeleteReferenceOfItemSetByStampSheetResult final : public TSharedFromThis<FDeleteReferenceOfItemSetByStampSheetResult>
    {
        TOptional<FString> ItemValue;
        TSharedPtr<Model::FItemSet> ItemSetValue;
        TSharedPtr<Model::FItemModel> ItemModelValue;
        TSharedPtr<Model::FInventory> InventoryValue;
        
    public:
        
        FDeleteReferenceOfItemSetByStampSheetResult();
        FDeleteReferenceOfItemSetByStampSheetResult(
            const FDeleteReferenceOfItemSetByStampSheetResult& From
        );
        ~FDeleteReferenceOfItemSetByStampSheetResult() = default;

        TSharedPtr<FDeleteReferenceOfItemSetByStampSheetResult> WithItem(const TOptional<FString> Item);
        TSharedPtr<FDeleteReferenceOfItemSetByStampSheetResult> WithItemSet(const TSharedPtr<Model::FItemSet> ItemSet);
        TSharedPtr<FDeleteReferenceOfItemSetByStampSheetResult> WithItemModel(const TSharedPtr<Model::FItemModel> ItemModel);
        TSharedPtr<FDeleteReferenceOfItemSetByStampSheetResult> WithInventory(const TSharedPtr<Model::FInventory> Inventory);

        TOptional<FString> GetItem() const;
        TSharedPtr<Model::FItemSet> GetItemSet() const;
        TSharedPtr<Model::FItemModel> GetItemModel() const;
        TSharedPtr<Model::FInventory> GetInventory() const;

        static TSharedPtr<FDeleteReferenceOfItemSetByStampSheetResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDeleteReferenceOfItemSetByStampSheetResult, ESPMode::ThreadSafe> FDeleteReferenceOfItemSetByStampSheetResultPtr;
}