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
    class GS2EXPERIENCE_API FExperienceModelMaster final : public Gs2Object, public TSharedFromThis<FExperienceModelMaster>
    {
        TOptional<FString> ExperienceModelIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        TOptional<int64> DefaultExperienceValue;
        TOptional<int64> DefaultRankCapValue;
        TOptional<int64> MaxRankCapValue;
        TOptional<FString> RankThresholdNameValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> UpdatedAtValue;

    public:
        FExperienceModelMaster();
        FExperienceModelMaster(
            const FExperienceModelMaster& From
        );
        virtual ~FExperienceModelMaster() override = default;

        TSharedPtr<FExperienceModelMaster> WithExperienceModelId(const TOptional<FString> ExperienceModelId);
        TSharedPtr<FExperienceModelMaster> WithName(const TOptional<FString> Name);
        TSharedPtr<FExperienceModelMaster> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FExperienceModelMaster> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FExperienceModelMaster> WithDefaultExperience(const TOptional<int64> DefaultExperience);
        TSharedPtr<FExperienceModelMaster> WithDefaultRankCap(const TOptional<int64> DefaultRankCap);
        TSharedPtr<FExperienceModelMaster> WithMaxRankCap(const TOptional<int64> MaxRankCap);
        TSharedPtr<FExperienceModelMaster> WithRankThresholdName(const TOptional<FString> RankThresholdName);
        TSharedPtr<FExperienceModelMaster> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FExperienceModelMaster> WithUpdatedAt(const TOptional<int64> UpdatedAt);

        TOptional<FString> GetExperienceModelId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMetadata() const;
        TOptional<int64> GetDefaultExperience() const;
        FString GetDefaultExperienceString() const;
        TOptional<int64> GetDefaultRankCap() const;
        FString GetDefaultRankCapString() const;
        TOptional<int64> GetMaxRankCap() const;
        FString GetMaxRankCapString() const;
        TOptional<FString> GetRankThresholdName() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;
        TOptional<int64> GetUpdatedAt() const;
        FString GetUpdatedAtString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetExperienceNameFromGrn(const FString Grn);

        static TSharedPtr<FExperienceModelMaster> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FExperienceModelMaster, ESPMode::ThreadSafe> FExperienceModelMasterPtr;
}