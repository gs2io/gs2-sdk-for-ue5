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

namespace Gs2::Showcase::Model
{
    class GS2SHOWCASE_API FSalesItemGroupMaster final : public FGs2Object, public TSharedFromThis<FSalesItemGroupMaster>
    {
        TOptional<FString> SalesItemGroupIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        TSharedPtr<TArray<FString>> SalesItemNamesValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> UpdatedAtValue;
        TOptional<int64> RevisionValue;

    public:
        FSalesItemGroupMaster();
        FSalesItemGroupMaster(
            const FSalesItemGroupMaster& From
        );
        virtual ~FSalesItemGroupMaster() override = default;

        TSharedPtr<FSalesItemGroupMaster> WithSalesItemGroupId(const TOptional<FString> SalesItemGroupId);
        TSharedPtr<FSalesItemGroupMaster> WithName(const TOptional<FString> Name);
        TSharedPtr<FSalesItemGroupMaster> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FSalesItemGroupMaster> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FSalesItemGroupMaster> WithSalesItemNames(const TSharedPtr<TArray<FString>> SalesItemNames);
        TSharedPtr<FSalesItemGroupMaster> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FSalesItemGroupMaster> WithUpdatedAt(const TOptional<int64> UpdatedAt);
        TSharedPtr<FSalesItemGroupMaster> WithRevision(const TOptional<int64> Revision);

        TOptional<FString> GetSalesItemGroupId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMetadata() const;
        TSharedPtr<TArray<FString>> GetSalesItemNames() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;
        TOptional<int64> GetUpdatedAt() const;
        FString GetUpdatedAtString() const;
        TOptional<int64> GetRevision() const;
        FString GetRevisionString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetSalesItemGroupNameFromGrn(const FString Grn);

        static TSharedPtr<FSalesItemGroupMaster> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FSalesItemGroupMaster, ESPMode::ThreadSafe> FSalesItemGroupMasterPtr;
}