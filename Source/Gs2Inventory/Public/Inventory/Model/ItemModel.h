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
    class GS2INVENTORY_API FItemModel final : public TSharedFromThis<FItemModel>
    {
        TOptional<FString> ItemModelIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;
        TOptional<int64> StackingLimitValue;
        TOptional<bool> AllowMultipleStacksValue;
        TOptional<int32> SortValueValue;

    public:
        FItemModel();
        FItemModel(
            const FItemModel& From
        );
        ~FItemModel() = default;

        TSharedPtr<FItemModel> WithItemModelId(const TOptional<FString> ItemModelId);
        TSharedPtr<FItemModel> WithName(const TOptional<FString> Name);
        TSharedPtr<FItemModel> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FItemModel> WithStackingLimit(const TOptional<int64> StackingLimit);
        TSharedPtr<FItemModel> WithAllowMultipleStacks(const TOptional<bool> AllowMultipleStacks);
        TSharedPtr<FItemModel> WithSortValue(const TOptional<int32> SortValue);

        TOptional<FString> GetItemModelId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetMetadata() const;
        TOptional<int64> GetStackingLimit() const;
        FString GetStackingLimitString() const;
        TOptional<bool> GetAllowMultipleStacks() const;
        FString GetAllowMultipleStacksString() const;
        TOptional<int32> GetSortValue() const;
        FString GetSortValueString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetInventoryNameFromGrn(const FString Grn);
        static TOptional<FString> GetItemNameFromGrn(const FString Grn);

        static TSharedPtr<FItemModel> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FItemModel, ESPMode::ThreadSafe> FItemModelPtr;
}