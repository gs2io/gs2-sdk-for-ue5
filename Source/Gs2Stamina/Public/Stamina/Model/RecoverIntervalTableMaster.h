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

namespace Gs2::Stamina::Model
{
    class GS2STAMINA_API FRecoverIntervalTableMaster final : public Gs2Object, public TSharedFromThis<FRecoverIntervalTableMaster>
    {
        TOptional<FString> RecoverIntervalTableIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> ExperienceModelIdValue;
        TSharedPtr<TArray<int32>> ValuesValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> UpdatedAtValue;
        TOptional<int64> RevisionValue;

    public:
        FRecoverIntervalTableMaster();
        FRecoverIntervalTableMaster(
            const FRecoverIntervalTableMaster& From
        );
        virtual ~FRecoverIntervalTableMaster() override = default;

        TSharedPtr<FRecoverIntervalTableMaster> WithRecoverIntervalTableId(const TOptional<FString> RecoverIntervalTableId);
        TSharedPtr<FRecoverIntervalTableMaster> WithName(const TOptional<FString> Name);
        TSharedPtr<FRecoverIntervalTableMaster> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FRecoverIntervalTableMaster> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FRecoverIntervalTableMaster> WithExperienceModelId(const TOptional<FString> ExperienceModelId);
        TSharedPtr<FRecoverIntervalTableMaster> WithValues(const TSharedPtr<TArray<int32>> Values);
        TSharedPtr<FRecoverIntervalTableMaster> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FRecoverIntervalTableMaster> WithUpdatedAt(const TOptional<int64> UpdatedAt);
        TSharedPtr<FRecoverIntervalTableMaster> WithRevision(const TOptional<int64> Revision);

        TOptional<FString> GetRecoverIntervalTableId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetMetadata() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetExperienceModelId() const;
        TSharedPtr<TArray<int32>> GetValues() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;
        TOptional<int64> GetUpdatedAt() const;
        FString GetUpdatedAtString() const;
        TOptional<int64> GetRevision() const;
        FString GetRevisionString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetRecoverIntervalTableNameFromGrn(const FString Grn);

        static TSharedPtr<FRecoverIntervalTableMaster> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FRecoverIntervalTableMaster, ESPMode::ThreadSafe> FRecoverIntervalTableMasterPtr;
}