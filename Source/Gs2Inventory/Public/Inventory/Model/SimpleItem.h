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
    class GS2INVENTORY_API FSimpleItem final : public Gs2Object, public TSharedFromThis<FSimpleItem>
    {
        TOptional<FString> ItemIdValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> ItemNameValue;
        TOptional<int64> CountValue;
        TOptional<int64> RevisionValue;

    public:
        FSimpleItem();
        FSimpleItem(
            const FSimpleItem& From
        );
        virtual ~FSimpleItem() override = default;

        TSharedPtr<FSimpleItem> WithItemId(const TOptional<FString> ItemId);
        TSharedPtr<FSimpleItem> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FSimpleItem> WithItemName(const TOptional<FString> ItemName);
        TSharedPtr<FSimpleItem> WithCount(const TOptional<int64> Count);
        TSharedPtr<FSimpleItem> WithRevision(const TOptional<int64> Revision);

        TOptional<FString> GetItemId() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetItemName() const;
        TOptional<int64> GetCount() const;
        FString GetCountString() const;
        TOptional<int64> GetRevision() const;
        FString GetRevisionString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetUserIdFromGrn(const FString Grn);
        static TOptional<FString> GetInventoryNameFromGrn(const FString Grn);
        static TOptional<FString> GetItemNameFromGrn(const FString Grn);

        static TSharedPtr<FSimpleItem> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FSimpleItem, ESPMode::ThreadSafe> FSimpleItemPtr;
}