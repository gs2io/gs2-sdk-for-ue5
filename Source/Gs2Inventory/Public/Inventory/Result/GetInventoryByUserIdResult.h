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
#include "../Model/Inventory.h"

namespace Gs2::Inventory::Result
{
    class GS2INVENTORY_API FGetInventoryByUserIdResult final : public TSharedFromThis<FGetInventoryByUserIdResult>
    {
        TSharedPtr<Model::FInventory> ItemValue;
        
    public:
        
        FGetInventoryByUserIdResult();
        FGetInventoryByUserIdResult(
            const FGetInventoryByUserIdResult& From
        );
        ~FGetInventoryByUserIdResult() = default;

        TSharedPtr<FGetInventoryByUserIdResult> WithItem(const TSharedPtr<Model::FInventory> Item);

        TSharedPtr<Model::FInventory> GetItem() const;

        static TSharedPtr<FGetInventoryByUserIdResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetInventoryByUserIdResult, ESPMode::ThreadSafe> FGetInventoryByUserIdResultPtr;
}