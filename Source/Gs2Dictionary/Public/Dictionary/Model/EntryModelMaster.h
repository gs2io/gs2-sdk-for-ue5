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

namespace Gs2::Dictionary::Model
{
    class GS2DICTIONARY_API FEntryModelMaster final : public Gs2Object, public TSharedFromThis<FEntryModelMaster>
    {
        TOptional<FString> EntryModelIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> UpdatedAtValue;
        TOptional<int64> RevisionValue;

    public:
        FEntryModelMaster();
        FEntryModelMaster(
            const FEntryModelMaster& From
        );
        virtual ~FEntryModelMaster() override = default;

        TSharedPtr<FEntryModelMaster> WithEntryModelId(const TOptional<FString> EntryModelId);
        TSharedPtr<FEntryModelMaster> WithName(const TOptional<FString> Name);
        TSharedPtr<FEntryModelMaster> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FEntryModelMaster> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FEntryModelMaster> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FEntryModelMaster> WithUpdatedAt(const TOptional<int64> UpdatedAt);
        TSharedPtr<FEntryModelMaster> WithRevision(const TOptional<int64> Revision);

        TOptional<FString> GetEntryModelId() const;
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
        static TOptional<FString> GetEntryModelNameFromGrn(const FString Grn);

        static TSharedPtr<FEntryModelMaster> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FEntryModelMaster, ESPMode::ThreadSafe> FEntryModelMasterPtr;
}