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
#include "../Model/BigInventoryModel.h"

namespace Gs2::Inventory::Result
{
    class GS2INVENTORY_API FDescribeBigInventoryModelsResult final : public TSharedFromThis<FDescribeBigInventoryModelsResult>
    {
        TSharedPtr<TArray<TSharedPtr<Model::FBigInventoryModel>>> ItemsValue;
        
    public:
        
        FDescribeBigInventoryModelsResult();
        FDescribeBigInventoryModelsResult(
            const FDescribeBigInventoryModelsResult& From
        );
        ~FDescribeBigInventoryModelsResult() = default;

        TSharedPtr<FDescribeBigInventoryModelsResult> WithItems(const TSharedPtr<TArray<TSharedPtr<Model::FBigInventoryModel>>> Items);

        TSharedPtr<TArray<TSharedPtr<Model::FBigInventoryModel>>> GetItems() const;

        static TSharedPtr<FDescribeBigInventoryModelsResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDescribeBigInventoryModelsResult, ESPMode::ThreadSafe> FDescribeBigInventoryModelsResultPtr;
}