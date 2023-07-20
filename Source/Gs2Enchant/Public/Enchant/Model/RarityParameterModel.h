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
    class GS2ENCHANT_API FRarityParameterModel final : public Gs2Object, public TSharedFromThis<FRarityParameterModel>
    {
        TOptional<FString> RarityParameterModelIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;
        TOptional<int32> MaximumParameterCountValue;
        TSharedPtr<TArray<TSharedPtr<FRarityParameterCountModel>>> ParameterCountsValue;
        TSharedPtr<TArray<TSharedPtr<FRarityParameterValueModel>>> ParametersValue;

    public:
        FRarityParameterModel();
        FRarityParameterModel(
            const FRarityParameterModel& From
        );
        virtual ~FRarityParameterModel() override = default;

        TSharedPtr<FRarityParameterModel> WithRarityParameterModelId(const TOptional<FString> RarityParameterModelId);
        TSharedPtr<FRarityParameterModel> WithName(const TOptional<FString> Name);
        TSharedPtr<FRarityParameterModel> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FRarityParameterModel> WithMaximumParameterCount(const TOptional<int32> MaximumParameterCount);
        TSharedPtr<FRarityParameterModel> WithParameterCounts(const TSharedPtr<TArray<TSharedPtr<FRarityParameterCountModel>>> ParameterCounts);
        TSharedPtr<FRarityParameterModel> WithParameters(const TSharedPtr<TArray<TSharedPtr<FRarityParameterValueModel>>> Parameters);

        TOptional<FString> GetRarityParameterModelId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetMetadata() const;
        TOptional<int32> GetMaximumParameterCount() const;
        FString GetMaximumParameterCountString() const;
        TSharedPtr<TArray<TSharedPtr<FRarityParameterCountModel>>> GetParameterCounts() const;
        TSharedPtr<TArray<TSharedPtr<FRarityParameterValueModel>>> GetParameters() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetParameterNameFromGrn(const FString Grn);

        static TSharedPtr<FRarityParameterModel> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FRarityParameterModel, ESPMode::ThreadSafe> FRarityParameterModelPtr;
}