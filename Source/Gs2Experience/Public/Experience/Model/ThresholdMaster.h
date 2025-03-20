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

namespace Gs2::Experience::Model
{
    class GS2EXPERIENCE_API FThresholdMaster final : public FGs2Object, public TSharedFromThis<FThresholdMaster>
    {
        TOptional<FString> ThresholdIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        TSharedPtr<TArray<int64>> ValuesValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> UpdatedAtValue;
        TOptional<int64> RevisionValue;

    public:
        FThresholdMaster();
        FThresholdMaster(
            const FThresholdMaster& From
        );
        virtual ~FThresholdMaster() override = default;

        TSharedPtr<FThresholdMaster> WithThresholdId(const TOptional<FString> ThresholdId);
        TSharedPtr<FThresholdMaster> WithName(const TOptional<FString> Name);
        TSharedPtr<FThresholdMaster> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FThresholdMaster> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FThresholdMaster> WithValues(const TSharedPtr<TArray<int64>> Values);
        TSharedPtr<FThresholdMaster> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FThresholdMaster> WithUpdatedAt(const TOptional<int64> UpdatedAt);
        TSharedPtr<FThresholdMaster> WithRevision(const TOptional<int64> Revision);

        TOptional<FString> GetThresholdId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMetadata() const;
        TSharedPtr<TArray<int64>> GetValues() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;
        TOptional<int64> GetUpdatedAt() const;
        FString GetUpdatedAtString() const;
        TOptional<int64> GetRevision() const;
        FString GetRevisionString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetThresholdNameFromGrn(const FString Grn);

        static TSharedPtr<FThresholdMaster> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FThresholdMaster, ESPMode::ThreadSafe> FThresholdMasterPtr;
}