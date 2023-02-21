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
    class GS2INVENTORY_API FGetItemWithSignatureResult final : public TSharedFromThis<FGetItemWithSignatureResult>
    {
        TSharedPtr<TArray<TSharedPtr<Model::FItemSet>>> ItemsValue;
        TSharedPtr<Model::FItemModel> ItemModelValue;
        TSharedPtr<Model::FInventory> InventoryValue;
        TOptional<FString> BodyValue;
        TOptional<FString> SignatureValue;
        
    public:
        
        FGetItemWithSignatureResult();
        FGetItemWithSignatureResult(
            const FGetItemWithSignatureResult& From
        );
        ~FGetItemWithSignatureResult() = default;

        TSharedPtr<FGetItemWithSignatureResult> WithItems(const TSharedPtr<TArray<TSharedPtr<Model::FItemSet>>> Items);
        TSharedPtr<FGetItemWithSignatureResult> WithItemModel(const TSharedPtr<Model::FItemModel> ItemModel);
        TSharedPtr<FGetItemWithSignatureResult> WithInventory(const TSharedPtr<Model::FInventory> Inventory);
        TSharedPtr<FGetItemWithSignatureResult> WithBody(const TOptional<FString> Body);
        TSharedPtr<FGetItemWithSignatureResult> WithSignature(const TOptional<FString> Signature);

        TSharedPtr<TArray<TSharedPtr<Model::FItemSet>>> GetItems() const;
        TSharedPtr<Model::FItemModel> GetItemModel() const;
        TSharedPtr<Model::FInventory> GetInventory() const;
        TOptional<FString> GetBody() const;
        TOptional<FString> GetSignature() const;

        static TSharedPtr<FGetItemWithSignatureResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetItemWithSignatureResult, ESPMode::ThreadSafe> FGetItemWithSignatureResultPtr;
}