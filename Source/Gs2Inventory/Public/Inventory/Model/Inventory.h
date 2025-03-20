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
    class GS2INVENTORY_API FInventory final : public FGs2Object, public TSharedFromThis<FInventory>
    {
        TOptional<FString> InventoryIdValue;
        TOptional<FString> InventoryNameValue;
        TOptional<FString> UserIdValue;
        TOptional<int32> CurrentInventoryCapacityUsageValue;
        TOptional<int32> CurrentInventoryMaxCapacityValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> UpdatedAtValue;
        TOptional<int64> RevisionValue;

    public:
        FInventory();
        FInventory(
            const FInventory& From
        );
        virtual ~FInventory() override = default;

        TSharedPtr<FInventory> WithInventoryId(const TOptional<FString> InventoryId);
        TSharedPtr<FInventory> WithInventoryName(const TOptional<FString> InventoryName);
        TSharedPtr<FInventory> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FInventory> WithCurrentInventoryCapacityUsage(const TOptional<int32> CurrentInventoryCapacityUsage);
        TSharedPtr<FInventory> WithCurrentInventoryMaxCapacity(const TOptional<int32> CurrentInventoryMaxCapacity);
        TSharedPtr<FInventory> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FInventory> WithUpdatedAt(const TOptional<int64> UpdatedAt);
        TSharedPtr<FInventory> WithRevision(const TOptional<int64> Revision);

        TOptional<FString> GetInventoryId() const;
        TOptional<FString> GetInventoryName() const;
        TOptional<FString> GetUserId() const;
        TOptional<int32> GetCurrentInventoryCapacityUsage() const;
        FString GetCurrentInventoryCapacityUsageString() const;
        TOptional<int32> GetCurrentInventoryMaxCapacity() const;
        FString GetCurrentInventoryMaxCapacityString() const;
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

        static TSharedPtr<FInventory> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FInventory, ESPMode::ThreadSafe> FInventoryPtr;
}