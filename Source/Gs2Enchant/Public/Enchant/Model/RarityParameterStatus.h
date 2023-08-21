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
#include "RarityParameterValue.h"

namespace Gs2::Enchant::Model
{
    class GS2ENCHANT_API FRarityParameterStatus final : public Gs2Object, public TSharedFromThis<FRarityParameterStatus>
    {
        TOptional<FString> RarityParameterStatusIdValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> ParameterNameValue;
        TOptional<FString> PropertyIdValue;
        TSharedPtr<TArray<TSharedPtr<FRarityParameterValue>>> ParameterValuesValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> UpdatedAtValue;
        TOptional<int64> RevisionValue;

    public:
        FRarityParameterStatus();
        FRarityParameterStatus(
            const FRarityParameterStatus& From
        );
        virtual ~FRarityParameterStatus() override = default;

        TSharedPtr<FRarityParameterStatus> WithRarityParameterStatusId(const TOptional<FString> RarityParameterStatusId);
        TSharedPtr<FRarityParameterStatus> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FRarityParameterStatus> WithParameterName(const TOptional<FString> ParameterName);
        TSharedPtr<FRarityParameterStatus> WithPropertyId(const TOptional<FString> PropertyId);
        TSharedPtr<FRarityParameterStatus> WithParameterValues(const TSharedPtr<TArray<TSharedPtr<FRarityParameterValue>>> ParameterValues);
        TSharedPtr<FRarityParameterStatus> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FRarityParameterStatus> WithUpdatedAt(const TOptional<int64> UpdatedAt);
        TSharedPtr<FRarityParameterStatus> WithRevision(const TOptional<int64> Revision);

        TOptional<FString> GetRarityParameterStatusId() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetParameterName() const;
        TOptional<FString> GetPropertyId() const;
        TSharedPtr<TArray<TSharedPtr<FRarityParameterValue>>> GetParameterValues() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;
        TOptional<int64> GetUpdatedAt() const;
        FString GetUpdatedAtString() const;
        TOptional<int64> GetRevision() const;
        FString GetRevisionString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetUserIdFromGrn(const FString Grn);
        static TOptional<FString> GetParameterNameFromGrn(const FString Grn);
        static TOptional<FString> GetPropertyIdFromGrn(const FString Grn);

        static TSharedPtr<FRarityParameterStatus> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FRarityParameterStatus, ESPMode::ThreadSafe> FRarityParameterStatusPtr;
}