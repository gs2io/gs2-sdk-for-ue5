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
#include "BigItem.h"

namespace Gs2::Inventory::Model
{
    class GS2INVENTORY_API FBigInventory final : public Gs2Object, public TSharedFromThis<FBigInventory>
    {
        TOptional<FString> InventoryIdValue;
        TOptional<FString> InventoryNameValue;
        TOptional<FString> UserIdValue;
        TSharedPtr<TArray<TSharedPtr<FBigItem>>> BigItemsValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> UpdatedAtValue;

    public:
        FBigInventory();
        FBigInventory(
            const FBigInventory& From
        );
        virtual ~FBigInventory() override = default;

        TSharedPtr<FBigInventory> WithInventoryId(const TOptional<FString> InventoryId);
        TSharedPtr<FBigInventory> WithInventoryName(const TOptional<FString> InventoryName);
        TSharedPtr<FBigInventory> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FBigInventory> WithBigItems(const TSharedPtr<TArray<TSharedPtr<FBigItem>>> BigItems);
        TSharedPtr<FBigInventory> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FBigInventory> WithUpdatedAt(const TOptional<int64> UpdatedAt);

        TOptional<FString> GetInventoryId() const;
        TOptional<FString> GetInventoryName() const;
        TOptional<FString> GetUserId() const;
        TSharedPtr<TArray<TSharedPtr<FBigItem>>> GetBigItems() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;
        TOptional<int64> GetUpdatedAt() const;
        FString GetUpdatedAtString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetUserIdFromGrn(const FString Grn);
        static TOptional<FString> GetInventoryNameFromGrn(const FString Grn);

        static TSharedPtr<FBigInventory> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FBigInventory, ESPMode::ThreadSafe> FBigInventoryPtr;
}