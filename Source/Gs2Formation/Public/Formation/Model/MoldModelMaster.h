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

namespace Gs2::Formation::Model
{
    class GS2FORMATION_API FMoldModelMaster final : public TSharedFromThis<FMoldModelMaster>
    {
        TOptional<FString> MoldModelIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        TOptional<int32> InitialMaxCapacityValue;
        TOptional<int32> MaxCapacityValue;
        TOptional<FString> FormModelNameValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> UpdatedAtValue;

    public:
        FMoldModelMaster();
        FMoldModelMaster(
            const FMoldModelMaster& From
        );
        ~FMoldModelMaster() = default;

        TSharedPtr<FMoldModelMaster> WithMoldModelId(const TOptional<FString> MoldModelId);
        TSharedPtr<FMoldModelMaster> WithName(const TOptional<FString> Name);
        TSharedPtr<FMoldModelMaster> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FMoldModelMaster> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FMoldModelMaster> WithInitialMaxCapacity(const TOptional<int32> InitialMaxCapacity);
        TSharedPtr<FMoldModelMaster> WithMaxCapacity(const TOptional<int32> MaxCapacity);
        TSharedPtr<FMoldModelMaster> WithFormModelName(const TOptional<FString> FormModelName);
        TSharedPtr<FMoldModelMaster> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FMoldModelMaster> WithUpdatedAt(const TOptional<int64> UpdatedAt);

        TOptional<FString> GetMoldModelId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMetadata() const;
        TOptional<int32> GetInitialMaxCapacity() const;
        FString GetInitialMaxCapacityString() const;
        TOptional<int32> GetMaxCapacity() const;
        FString GetMaxCapacityString() const;
        TOptional<FString> GetFormModelName() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;
        TOptional<int64> GetUpdatedAt() const;
        FString GetUpdatedAtString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetMoldNameFromGrn(const FString Grn);

        static TSharedPtr<FMoldModelMaster> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FMoldModelMaster, ESPMode::ThreadSafe> FMoldModelMasterPtr;
}