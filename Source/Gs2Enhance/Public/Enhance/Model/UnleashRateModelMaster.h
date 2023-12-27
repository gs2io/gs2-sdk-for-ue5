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
#include "UnleashRateEntryModel.h"

namespace Gs2::Enhance::Model
{
    class GS2ENHANCE_API FUnleashRateModelMaster final : public Gs2Object, public TSharedFromThis<FUnleashRateModelMaster>
    {
        TOptional<FString> UnleashRateModelIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        TOptional<FString> TargetInventoryModelIdValue;
        TOptional<FString> GradeModelIdValue;
        TSharedPtr<TArray<TSharedPtr<FUnleashRateEntryModel>>> GradeEntriesValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> UpdatedAtValue;
        TOptional<int64> RevisionValue;

    public:
        FUnleashRateModelMaster();
        FUnleashRateModelMaster(
            const FUnleashRateModelMaster& From
        );
        virtual ~FUnleashRateModelMaster() override = default;

        TSharedPtr<FUnleashRateModelMaster> WithUnleashRateModelId(const TOptional<FString> UnleashRateModelId);
        TSharedPtr<FUnleashRateModelMaster> WithName(const TOptional<FString> Name);
        TSharedPtr<FUnleashRateModelMaster> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FUnleashRateModelMaster> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FUnleashRateModelMaster> WithTargetInventoryModelId(const TOptional<FString> TargetInventoryModelId);
        TSharedPtr<FUnleashRateModelMaster> WithGradeModelId(const TOptional<FString> GradeModelId);
        TSharedPtr<FUnleashRateModelMaster> WithGradeEntries(const TSharedPtr<TArray<TSharedPtr<FUnleashRateEntryModel>>> GradeEntries);
        TSharedPtr<FUnleashRateModelMaster> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FUnleashRateModelMaster> WithUpdatedAt(const TOptional<int64> UpdatedAt);
        TSharedPtr<FUnleashRateModelMaster> WithRevision(const TOptional<int64> Revision);

        TOptional<FString> GetUnleashRateModelId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMetadata() const;
        TOptional<FString> GetTargetInventoryModelId() const;
        TOptional<FString> GetGradeModelId() const;
        TSharedPtr<TArray<TSharedPtr<FUnleashRateEntryModel>>> GetGradeEntries() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;
        TOptional<int64> GetUpdatedAt() const;
        FString GetUpdatedAtString() const;
        TOptional<int64> GetRevision() const;
        FString GetRevisionString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetRateNameFromGrn(const FString Grn);

        static TSharedPtr<FUnleashRateModelMaster> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FUnleashRateModelMaster, ESPMode::ThreadSafe> FUnleashRateModelMasterPtr;
}