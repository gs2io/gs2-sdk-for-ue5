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
#include "Gs2Grade/Public/Grade/Model/Status.h"
#include "../Model/ItemModel.h"
#include "../Model/Inventory.h"

namespace Gs2::Inventory::Result
{
    class GS2INVENTORY_API FAcquireItemSetWithGradeByStampSheetResult final : public TSharedFromThis<FAcquireItemSetWithGradeByStampSheetResult>
    {
        TSharedPtr<Model::FItemSet> ItemValue;
        TSharedPtr<Gs2::Grade::Model::FStatus> StatusValue;
        TSharedPtr<Model::FItemModel> ItemModelValue;
        TSharedPtr<Model::FInventory> InventoryValue;
        TOptional<int64> OverflowCountValue;
        
    public:
        
        FAcquireItemSetWithGradeByStampSheetResult();
        FAcquireItemSetWithGradeByStampSheetResult(
            const FAcquireItemSetWithGradeByStampSheetResult& From
        );
        ~FAcquireItemSetWithGradeByStampSheetResult() = default;

        TSharedPtr<FAcquireItemSetWithGradeByStampSheetResult> WithItem(const TSharedPtr<Model::FItemSet> Item);
        TSharedPtr<FAcquireItemSetWithGradeByStampSheetResult> WithStatus(const TSharedPtr<Gs2::Grade::Model::FStatus> Status);
        TSharedPtr<FAcquireItemSetWithGradeByStampSheetResult> WithItemModel(const TSharedPtr<Model::FItemModel> ItemModel);
        TSharedPtr<FAcquireItemSetWithGradeByStampSheetResult> WithInventory(const TSharedPtr<Model::FInventory> Inventory);
        TSharedPtr<FAcquireItemSetWithGradeByStampSheetResult> WithOverflowCount(const TOptional<int64> OverflowCount);

        TSharedPtr<Model::FItemSet> GetItem() const;
        TSharedPtr<Gs2::Grade::Model::FStatus> GetStatus() const;
        TSharedPtr<Model::FItemModel> GetItemModel() const;
        TSharedPtr<Model::FInventory> GetInventory() const;
        TOptional<int64> GetOverflowCount() const;
        FString GetOverflowCountString() const;

        static TSharedPtr<FAcquireItemSetWithGradeByStampSheetResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FAcquireItemSetWithGradeByStampSheetResult, ESPMode::ThreadSafe> FAcquireItemSetWithGradeByStampSheetResultPtr;
}