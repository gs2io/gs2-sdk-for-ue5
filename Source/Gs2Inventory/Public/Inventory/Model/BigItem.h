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
#include "Core/Gs2Object.h"

namespace Gs2::Inventory::Model
{
    class GS2INVENTORY_API FBigItem final : public Gs2Object, public TSharedFromThis<FBigItem>
    {
        TOptional<FString> ItemIdValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> ItemNameValue;
        TOptional<FString> CountValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> UpdatedAtValue;
        TOptional<int64> RevisionValue;

    public:
        FBigItem();
        FBigItem(
            const FBigItem& From
        );
        virtual ~FBigItem() override = default;

        TSharedPtr<FBigItem> WithItemId(const TOptional<FString> ItemId);
        TSharedPtr<FBigItem> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FBigItem> WithItemName(const TOptional<FString> ItemName);
        TSharedPtr<FBigItem> WithCount(const TOptional<FString> Count);
        TSharedPtr<FBigItem> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FBigItem> WithUpdatedAt(const TOptional<int64> UpdatedAt);
        TSharedPtr<FBigItem> WithRevision(const TOptional<int64> Revision);

        TOptional<FString> GetItemId() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetItemName() const;
        TOptional<FString> GetCount() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;
        TOptional<int64> GetUpdatedAt() const;
        FString GetUpdatedAtString() const;
        TOptional<int64> GetRevision() const;
        FString GetRevisionString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetUserIdFromGrn(const FString Grn);
        static TOptional<FString> GetInventoryNameFromGrn(const FString Grn);
        static TOptional<FString> GetItemNameFromGrn(const FString Grn);

        static TSharedPtr<FBigItem> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FBigItem, ESPMode::ThreadSafe> FBigItemPtr;
}