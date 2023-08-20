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
#include "../Model/BigItem.h"
#include "../Model/BigItemModel.h"

namespace Gs2::Inventory::Result
{
    class GS2INVENTORY_API FGetBigItemResult final : public TSharedFromThis<FGetBigItemResult>
    {
        TSharedPtr<Model::FBigItem> ItemValue;
        TSharedPtr<Model::FBigItemModel> ItemModelValue;
        
    public:
        
        FGetBigItemResult();
        FGetBigItemResult(
            const FGetBigItemResult& From
        );
        ~FGetBigItemResult() = default;

        TSharedPtr<FGetBigItemResult> WithItem(const TSharedPtr<Model::FBigItem> Item);
        TSharedPtr<FGetBigItemResult> WithItemModel(const TSharedPtr<Model::FBigItemModel> ItemModel);

        TSharedPtr<Model::FBigItem> GetItem() const;
        TSharedPtr<Model::FBigItemModel> GetItemModel() const;

        static TSharedPtr<FGetBigItemResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetBigItemResult, ESPMode::ThreadSafe> FGetBigItemResultPtr;
}