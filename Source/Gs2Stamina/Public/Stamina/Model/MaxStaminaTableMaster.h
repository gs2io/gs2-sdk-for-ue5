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

namespace Gs2::Stamina::Model
{
    class GS2STAMINA_API FMaxStaminaTableMaster final : public TSharedFromThis<FMaxStaminaTableMaster>
    {
        TOptional<FString> MaxStaminaTableIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> ExperienceModelIdValue;
        TSharedPtr<TArray<int32>> ValuesValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> UpdatedAtValue;

    public:
        FMaxStaminaTableMaster();
        FMaxStaminaTableMaster(
            const FMaxStaminaTableMaster& From
        );
        ~FMaxStaminaTableMaster() = default;

        TSharedPtr<FMaxStaminaTableMaster> WithMaxStaminaTableId(const TOptional<FString> MaxStaminaTableId);
        TSharedPtr<FMaxStaminaTableMaster> WithName(const TOptional<FString> Name);
        TSharedPtr<FMaxStaminaTableMaster> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FMaxStaminaTableMaster> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FMaxStaminaTableMaster> WithExperienceModelId(const TOptional<FString> ExperienceModelId);
        TSharedPtr<FMaxStaminaTableMaster> WithValues(const TSharedPtr<TArray<int32>> Values);
        TSharedPtr<FMaxStaminaTableMaster> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FMaxStaminaTableMaster> WithUpdatedAt(const TOptional<int64> UpdatedAt);

        TOptional<FString> GetMaxStaminaTableId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetMetadata() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetExperienceModelId() const;
        TSharedPtr<TArray<int32>> GetValues() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;
        TOptional<int64> GetUpdatedAt() const;
        FString GetUpdatedAtString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetMaxStaminaTableNameFromGrn(const FString Grn);

        static TSharedPtr<FMaxStaminaTableMaster> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FMaxStaminaTableMaster, ESPMode::ThreadSafe> FMaxStaminaTableMasterPtr;
}