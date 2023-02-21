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
#include "../Model/InventoryModelMaster.h"

namespace Gs2::Inventory::Result
{
    class GS2INVENTORY_API FUpdateInventoryModelMasterResult final : public TSharedFromThis<FUpdateInventoryModelMasterResult>
    {
        TSharedPtr<Model::FInventoryModelMaster> ItemValue;
        
    public:
        
        FUpdateInventoryModelMasterResult();
        FUpdateInventoryModelMasterResult(
            const FUpdateInventoryModelMasterResult& From
        );
        ~FUpdateInventoryModelMasterResult() = default;

        TSharedPtr<FUpdateInventoryModelMasterResult> WithItem(const TSharedPtr<Model::FInventoryModelMaster> Item);

        TSharedPtr<Model::FInventoryModelMaster> GetItem() const;

        static TSharedPtr<FUpdateInventoryModelMasterResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUpdateInventoryModelMasterResult, ESPMode::ThreadSafe> FUpdateInventoryModelMasterResultPtr;
}