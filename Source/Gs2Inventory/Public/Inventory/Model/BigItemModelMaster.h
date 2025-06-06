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
    class GS2INVENTORY_API FBigItemModelMaster final : public FGs2Object, public TSharedFromThis<FBigItemModelMaster>
    {
        TOptional<FString> ItemModelIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> UpdatedAtValue;
        TOptional<int64> RevisionValue;

    public:
        FBigItemModelMaster();
        FBigItemModelMaster(
            const FBigItemModelMaster& From
        );
        virtual ~FBigItemModelMaster() override = default;

        TSharedPtr<FBigItemModelMaster> WithItemModelId(const TOptional<FString> ItemModelId);
        TSharedPtr<FBigItemModelMaster> WithName(const TOptional<FString> Name);
        TSharedPtr<FBigItemModelMaster> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FBigItemModelMaster> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FBigItemModelMaster> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FBigItemModelMaster> WithUpdatedAt(const TOptional<int64> UpdatedAt);
        TSharedPtr<FBigItemModelMaster> WithRevision(const TOptional<int64> Revision);

        TOptional<FString> GetItemModelId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMetadata() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;
        TOptional<int64> GetUpdatedAt() const;
        FString GetUpdatedAtString() const;
        TOptional<int64> GetRevision() const;
        FString GetRevisionString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetInventoryNameFromGrn(const FString Grn);
        static TOptional<FString> GetItemNameFromGrn(const FString Grn);

        static TSharedPtr<FBigItemModelMaster> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FBigItemModelMaster, ESPMode::ThreadSafe> FBigItemModelMasterPtr;
}