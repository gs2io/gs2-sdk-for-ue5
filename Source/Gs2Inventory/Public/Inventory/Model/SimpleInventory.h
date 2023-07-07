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
    class GS2INVENTORY_API FSimpleInventory final : public Gs2Object, public TSharedFromThis<FSimpleInventory>
    {
        TOptional<FString> InventoryIdValue;
        TOptional<FString> InventoryNameValue;
        TOptional<FString> UserIdValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> UpdatedAtValue;

    public:
        FSimpleInventory();
        FSimpleInventory(
            const FSimpleInventory& From
        );
        virtual ~FSimpleInventory() override = default;

        TSharedPtr<FSimpleInventory> WithInventoryId(const TOptional<FString> InventoryId);
        TSharedPtr<FSimpleInventory> WithInventoryName(const TOptional<FString> InventoryName);
        TSharedPtr<FSimpleInventory> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FSimpleInventory> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FSimpleInventory> WithUpdatedAt(const TOptional<int64> UpdatedAt);

        TOptional<FString> GetInventoryId() const;
        TOptional<FString> GetInventoryName() const;
        TOptional<FString> GetUserId() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;
        TOptional<int64> GetUpdatedAt() const;
        FString GetUpdatedAtString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetUserIdFromGrn(const FString Grn);
        static TOptional<FString> GetInventoryNameFromGrn(const FString Grn);

        static TSharedPtr<FSimpleInventory> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FSimpleInventory, ESPMode::ThreadSafe> FSimpleInventoryPtr;
}