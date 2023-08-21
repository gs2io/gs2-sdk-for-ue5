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
#include "RarityParameterCountModel.h"
#include "RarityParameterValueModel.h"

namespace Gs2::Enchant::Model
{
    class GS2ENCHANT_API FRarityParameterModelMaster final : public Gs2Object, public TSharedFromThis<FRarityParameterModelMaster>
    {
        TOptional<FString> RarityParameterModelIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        TOptional<int32> MaximumParameterCountValue;
        TSharedPtr<TArray<TSharedPtr<FRarityParameterCountModel>>> ParameterCountsValue;
        TSharedPtr<TArray<TSharedPtr<FRarityParameterValueModel>>> ParametersValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> UpdatedAtValue;
        TOptional<int64> RevisionValue;

    public:
        FRarityParameterModelMaster();
        FRarityParameterModelMaster(
            const FRarityParameterModelMaster& From
        );
        virtual ~FRarityParameterModelMaster() override = default;

        TSharedPtr<FRarityParameterModelMaster> WithRarityParameterModelId(const TOptional<FString> RarityParameterModelId);
        TSharedPtr<FRarityParameterModelMaster> WithName(const TOptional<FString> Name);
        TSharedPtr<FRarityParameterModelMaster> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FRarityParameterModelMaster> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FRarityParameterModelMaster> WithMaximumParameterCount(const TOptional<int32> MaximumParameterCount);
        TSharedPtr<FRarityParameterModelMaster> WithParameterCounts(const TSharedPtr<TArray<TSharedPtr<FRarityParameterCountModel>>> ParameterCounts);
        TSharedPtr<FRarityParameterModelMaster> WithParameters(const TSharedPtr<TArray<TSharedPtr<FRarityParameterValueModel>>> Parameters);
        TSharedPtr<FRarityParameterModelMaster> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FRarityParameterModelMaster> WithUpdatedAt(const TOptional<int64> UpdatedAt);
        TSharedPtr<FRarityParameterModelMaster> WithRevision(const TOptional<int64> Revision);

        TOptional<FString> GetRarityParameterModelId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMetadata() const;
        TOptional<int32> GetMaximumParameterCount() const;
        FString GetMaximumParameterCountString() const;
        TSharedPtr<TArray<TSharedPtr<FRarityParameterCountModel>>> GetParameterCounts() const;
        TSharedPtr<TArray<TSharedPtr<FRarityParameterValueModel>>> GetParameters() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;
        TOptional<int64> GetUpdatedAt() const;
        FString GetUpdatedAtString() const;
        TOptional<int64> GetRevision() const;
        FString GetRevisionString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetParameterNameFromGrn(const FString Grn);

        static TSharedPtr<FRarityParameterModelMaster> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FRarityParameterModelMaster, ESPMode::ThreadSafe> FRarityParameterModelMasterPtr;
}