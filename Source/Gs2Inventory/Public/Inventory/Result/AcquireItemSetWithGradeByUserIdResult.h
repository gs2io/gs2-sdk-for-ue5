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
    class GS2INVENTORY_API FAcquireItemSetWithGradeByUserIdResult final : public TSharedFromThis<FAcquireItemSetWithGradeByUserIdResult>
    {
        TSharedPtr<Model::FItemSet> ItemValue;
        TSharedPtr<Gs2::Grade::Model::FStatus> StatusValue;
        TSharedPtr<Model::FItemModel> ItemModelValue;
        TSharedPtr<Model::FInventory> InventoryValue;
        TOptional<int64> OverflowCountValue;
        
    public:
        
        FAcquireItemSetWithGradeByUserIdResult();
        FAcquireItemSetWithGradeByUserIdResult(
            const FAcquireItemSetWithGradeByUserIdResult& From
        );
        ~FAcquireItemSetWithGradeByUserIdResult() = default;

        TSharedPtr<FAcquireItemSetWithGradeByUserIdResult> WithItem(const TSharedPtr<Model::FItemSet> Item);
        TSharedPtr<FAcquireItemSetWithGradeByUserIdResult> WithStatus(const TSharedPtr<Gs2::Grade::Model::FStatus> Status);
        TSharedPtr<FAcquireItemSetWithGradeByUserIdResult> WithItemModel(const TSharedPtr<Model::FItemModel> ItemModel);
        TSharedPtr<FAcquireItemSetWithGradeByUserIdResult> WithInventory(const TSharedPtr<Model::FInventory> Inventory);
        TSharedPtr<FAcquireItemSetWithGradeByUserIdResult> WithOverflowCount(const TOptional<int64> OverflowCount);

        TSharedPtr<Model::FItemSet> GetItem() const;
        TSharedPtr<Gs2::Grade::Model::FStatus> GetStatus() const;
        TSharedPtr<Model::FItemModel> GetItemModel() const;
        TSharedPtr<Model::FInventory> GetInventory() const;
        TOptional<int64> GetOverflowCount() const;
        FString GetOverflowCountString() const;

        static TSharedPtr<FAcquireItemSetWithGradeByUserIdResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FAcquireItemSetWithGradeByUserIdResult, ESPMode::ThreadSafe> FAcquireItemSetWithGradeByUserIdResultPtr;
}