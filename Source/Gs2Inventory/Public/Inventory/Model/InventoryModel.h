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
#include "ItemModel.h"

namespace Gs2::Inventory::Model
{
    class GS2INVENTORY_API FInventoryModel final : public TSharedFromThis<FInventoryModel>
    {
        TOptional<FString> InventoryModelIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;
        TOptional<int32> InitialCapacityValue;
        TOptional<int32> MaxCapacityValue;
        TOptional<bool> ProtectReferencedItemValue;
        TSharedPtr<TArray<TSharedPtr<FItemModel>>> ItemModelsValue;

    public:
        FInventoryModel();
        FInventoryModel(
            const FInventoryModel& From
        );
        ~FInventoryModel() = default;

        TSharedPtr<FInventoryModel> WithInventoryModelId(const TOptional<FString> InventoryModelId);
        TSharedPtr<FInventoryModel> WithName(const TOptional<FString> Name);
        TSharedPtr<FInventoryModel> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FInventoryModel> WithInitialCapacity(const TOptional<int32> InitialCapacity);
        TSharedPtr<FInventoryModel> WithMaxCapacity(const TOptional<int32> MaxCapacity);
        TSharedPtr<FInventoryModel> WithProtectReferencedItem(const TOptional<bool> ProtectReferencedItem);
        TSharedPtr<FInventoryModel> WithItemModels(const TSharedPtr<TArray<TSharedPtr<FItemModel>>> ItemModels);

        TOptional<FString> GetInventoryModelId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetMetadata() const;
        TOptional<int32> GetInitialCapacity() const;
        FString GetInitialCapacityString() const;
        TOptional<int32> GetMaxCapacity() const;
        FString GetMaxCapacityString() const;
        TOptional<bool> GetProtectReferencedItem() const;
        FString GetProtectReferencedItemString() const;
        TSharedPtr<TArray<TSharedPtr<FItemModel>>> GetItemModels() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetInventoryNameFromGrn(const FString Grn);

        static TSharedPtr<FInventoryModel> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FInventoryModel, ESPMode::ThreadSafe> FInventoryModelPtr;
}