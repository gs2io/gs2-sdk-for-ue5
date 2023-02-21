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

namespace Gs2::Inventory::Model
{
    class GS2INVENTORY_API FItemModelMaster final : public TSharedFromThis<FItemModelMaster>
    {
        TOptional<FString> ItemModelIdValue;
        TOptional<FString> InventoryNameValue;
        TOptional<FString> NameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        TOptional<int64> StackingLimitValue;
        TOptional<bool> AllowMultipleStacksValue;
        TOptional<int32> SortValueValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> UpdatedAtValue;

    public:
        FItemModelMaster();
        FItemModelMaster(
            const FItemModelMaster& From
        );
        ~FItemModelMaster() = default;

        TSharedPtr<FItemModelMaster> WithItemModelId(const TOptional<FString> ItemModelId);
        TSharedPtr<FItemModelMaster> WithInventoryName(const TOptional<FString> InventoryName);
        TSharedPtr<FItemModelMaster> WithName(const TOptional<FString> Name);
        TSharedPtr<FItemModelMaster> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FItemModelMaster> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FItemModelMaster> WithStackingLimit(const TOptional<int64> StackingLimit);
        TSharedPtr<FItemModelMaster> WithAllowMultipleStacks(const TOptional<bool> AllowMultipleStacks);
        TSharedPtr<FItemModelMaster> WithSortValue(const TOptional<int32> SortValue);
        TSharedPtr<FItemModelMaster> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FItemModelMaster> WithUpdatedAt(const TOptional<int64> UpdatedAt);

        TOptional<FString> GetItemModelId() const;
        TOptional<FString> GetInventoryName() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMetadata() const;
        TOptional<int64> GetStackingLimit() const;
        FString GetStackingLimitString() const;
        TOptional<bool> GetAllowMultipleStacks() const;
        FString GetAllowMultipleStacksString() const;
        TOptional<int32> GetSortValue() const;
        FString GetSortValueString() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;
        TOptional<int64> GetUpdatedAt() const;
        FString GetUpdatedAtString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetInventoryNameFromGrn(const FString Grn);
        static TOptional<FString> GetItemNameFromGrn(const FString Grn);

        static TSharedPtr<FItemModelMaster> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FItemModelMaster, ESPMode::ThreadSafe> FItemModelMasterPtr;
}