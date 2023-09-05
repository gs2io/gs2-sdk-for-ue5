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
    class GS2INVENTORY_API FSetCapacityByUserIdResult final : public TSharedFromThis<FSetCapacityByUserIdResult>
    {
        TSharedPtr<Model::FInventory> ItemValue;
        TSharedPtr<Model::FInventory> OldValue;
        
    public:
        
        FSetCapacityByUserIdResult();
        FSetCapacityByUserIdResult(
            const FSetCapacityByUserIdResult& From
        );
        ~FSetCapacityByUserIdResult() = default;

        TSharedPtr<FSetCapacityByUserIdResult> WithItem(const TSharedPtr<Model::FInventory> Item);
        TSharedPtr<FSetCapacityByUserIdResult> WithOld(const TSharedPtr<Model::FInventory> Old);

        TSharedPtr<Model::FInventory> GetItem() const;
        TSharedPtr<Model::FInventory> GetOld() const;

        static TSharedPtr<FSetCapacityByUserIdResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FSetCapacityByUserIdResult, ESPMode::ThreadSafe> FSetCapacityByUserIdResultPtr;
}