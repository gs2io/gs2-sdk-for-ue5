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
    class GS2INVENTORY_API FVerifyReferenceOfByStampTaskResult final : public TSharedFromThis<FVerifyReferenceOfByStampTaskResult>
    {
        TSharedPtr<TArray<FString>> ItemValue;
        TSharedPtr<Model::FItemSet> ItemSetValue;
        TSharedPtr<Model::FItemModel> ItemModelValue;
        TSharedPtr<Model::FInventory> InventoryValue;
        TOptional<FString> NewContextStackValue;
        
    public:
        
        FVerifyReferenceOfByStampTaskResult();
        FVerifyReferenceOfByStampTaskResult(
            const FVerifyReferenceOfByStampTaskResult& From
        );
        ~FVerifyReferenceOfByStampTaskResult() = default;

        TSharedPtr<FVerifyReferenceOfByStampTaskResult> WithItem(const TSharedPtr<TArray<FString>> Item);
        TSharedPtr<FVerifyReferenceOfByStampTaskResult> WithItemSet(const TSharedPtr<Model::FItemSet> ItemSet);
        TSharedPtr<FVerifyReferenceOfByStampTaskResult> WithItemModel(const TSharedPtr<Model::FItemModel> ItemModel);
        TSharedPtr<FVerifyReferenceOfByStampTaskResult> WithInventory(const TSharedPtr<Model::FInventory> Inventory);
        TSharedPtr<FVerifyReferenceOfByStampTaskResult> WithNewContextStack(const TOptional<FString> NewContextStack);

        TSharedPtr<TArray<FString>> GetItem() const;
        TSharedPtr<Model::FItemSet> GetItemSet() const;
        TSharedPtr<Model::FItemModel> GetItemModel() const;
        TSharedPtr<Model::FInventory> GetInventory() const;
        TOptional<FString> GetNewContextStack() const;

        static TSharedPtr<FVerifyReferenceOfByStampTaskResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FVerifyReferenceOfByStampTaskResult, ESPMode::ThreadSafe> FVerifyReferenceOfByStampTaskResultPtr;
}