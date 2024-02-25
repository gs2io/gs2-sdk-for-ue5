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
#include "TierModel.h"

namespace Gs2::SeasonRating::Model
{
    class GS2SEASONRATING_API FSeasonModel final : public Gs2Object, public TSharedFromThis<FSeasonModel>
    {
        TOptional<FString> SeasonModelIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;
        TSharedPtr<TArray<TSharedPtr<FTierModel>>> TiersValue;
        TOptional<FString> ExperienceModelIdValue;

    public:
        FSeasonModel();
        FSeasonModel(
            const FSeasonModel& From
        );
        virtual ~FSeasonModel() override = default;

        TSharedPtr<FSeasonModel> WithSeasonModelId(const TOptional<FString> SeasonModelId);
        TSharedPtr<FSeasonModel> WithName(const TOptional<FString> Name);
        TSharedPtr<FSeasonModel> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FSeasonModel> WithTiers(const TSharedPtr<TArray<TSharedPtr<FTierModel>>> Tiers);
        TSharedPtr<FSeasonModel> WithExperienceModelId(const TOptional<FString> ExperienceModelId);

        TOptional<FString> GetSeasonModelId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetMetadata() const;
        TSharedPtr<TArray<TSharedPtr<FTierModel>>> GetTiers() const;
        TOptional<FString> GetExperienceModelId() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetSeasonNameFromGrn(const FString Grn);

        static TSharedPtr<FSeasonModel> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FSeasonModel, ESPMode::ThreadSafe> FSeasonModelPtr;
}