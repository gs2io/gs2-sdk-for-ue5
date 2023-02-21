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
    class GS2INVENTORY_API FItemSet final : public TSharedFromThis<FItemSet>
    {
        TOptional<FString> ItemSetIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> InventoryNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> ItemNameValue;
        TOptional<int64> CountValue;
        TSharedPtr<TArray<FString>> ReferenceOfValue;
        TOptional<int32> SortValueValue;
        TOptional<int64> ExpiresAtValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> UpdatedAtValue;

    public:
        FItemSet();
        FItemSet(
            const FItemSet& From
        );
        ~FItemSet() = default;

        TSharedPtr<FItemSet> WithItemSetId(const TOptional<FString> ItemSetId);
        TSharedPtr<FItemSet> WithName(const TOptional<FString> Name);
        TSharedPtr<FItemSet> WithInventoryName(const TOptional<FString> InventoryName);
        TSharedPtr<FItemSet> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FItemSet> WithItemName(const TOptional<FString> ItemName);
        TSharedPtr<FItemSet> WithCount(const TOptional<int64> Count);
        TSharedPtr<FItemSet> WithReferenceOf(const TSharedPtr<TArray<FString>> ReferenceOf);
        TSharedPtr<FItemSet> WithSortValue(const TOptional<int32> SortValue);
        TSharedPtr<FItemSet> WithExpiresAt(const TOptional<int64> ExpiresAt);
        TSharedPtr<FItemSet> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FItemSet> WithUpdatedAt(const TOptional<int64> UpdatedAt);

        TOptional<FString> GetItemSetId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetInventoryName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetItemName() const;
        TOptional<int64> GetCount() const;
        FString GetCountString() const;
        TSharedPtr<TArray<FString>> GetReferenceOf() const;
        TOptional<int32> GetSortValue() const;
        FString GetSortValueString() const;
        TOptional<int64> GetExpiresAt() const;
        FString GetExpiresAtString() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;
        TOptional<int64> GetUpdatedAt() const;
        FString GetUpdatedAtString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetUserIdFromGrn(const FString Grn);
        static TOptional<FString> GetInventoryNameFromGrn(const FString Grn);
        static TOptional<FString> GetItemNameFromGrn(const FString Grn);
        static TOptional<FString> GetItemSetNameFromGrn(const FString Grn);

        static TSharedPtr<FItemSet> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FItemSet, ESPMode::ThreadSafe> FItemSetPtr;
}