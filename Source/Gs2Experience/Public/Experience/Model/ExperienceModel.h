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
#include "Threshold.h"
#include "AcquireActionRate.h"

namespace Gs2::Experience::Model
{
    class GS2EXPERIENCE_API FExperienceModel final : public Gs2Object, public TSharedFromThis<FExperienceModel>
    {
        TOptional<FString> ExperienceModelIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;
        TOptional<int64> DefaultExperienceValue;
        TOptional<int64> DefaultRankCapValue;
        TOptional<int64> MaxRankCapValue;
        TSharedPtr<FThreshold> RankThresholdValue;
        TSharedPtr<TArray<TSharedPtr<FAcquireActionRate>>> AcquireActionRatesValue;

    public:
        FExperienceModel();
        FExperienceModel(
            const FExperienceModel& From
        );
        virtual ~FExperienceModel() override = default;

        TSharedPtr<FExperienceModel> WithExperienceModelId(const TOptional<FString> ExperienceModelId);
        TSharedPtr<FExperienceModel> WithName(const TOptional<FString> Name);
        TSharedPtr<FExperienceModel> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FExperienceModel> WithDefaultExperience(const TOptional<int64> DefaultExperience);
        TSharedPtr<FExperienceModel> WithDefaultRankCap(const TOptional<int64> DefaultRankCap);
        TSharedPtr<FExperienceModel> WithMaxRankCap(const TOptional<int64> MaxRankCap);
        TSharedPtr<FExperienceModel> WithRankThreshold(const TSharedPtr<FThreshold> RankThreshold);
        TSharedPtr<FExperienceModel> WithAcquireActionRates(const TSharedPtr<TArray<TSharedPtr<FAcquireActionRate>>> AcquireActionRates);

        TOptional<FString> GetExperienceModelId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetMetadata() const;
        TOptional<int64> GetDefaultExperience() const;
        FString GetDefaultExperienceString() const;
        TOptional<int64> GetDefaultRankCap() const;
        FString GetDefaultRankCapString() const;
        TOptional<int64> GetMaxRankCap() const;
        FString GetMaxRankCapString() const;
        TSharedPtr<FThreshold> GetRankThreshold() const;
        TSharedPtr<TArray<TSharedPtr<FAcquireActionRate>>> GetAcquireActionRates() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetExperienceNameFromGrn(const FString Grn);

        static TSharedPtr<FExperienceModel> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FExperienceModel, ESPMode::ThreadSafe> FExperienceModelPtr;
}