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

namespace Gs2::Matchmaking::Model
{
    class GS2MATCHMAKING_API FSeasonModel final : public FGs2Object, public TSharedFromThis<FSeasonModel>
    {
        TOptional<FString> SeasonModelIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;
        TOptional<int32> MaximumParticipantsValue;
        TOptional<FString> ExperienceModelIdValue;
        TOptional<FString> ChallengePeriodEventIdValue;

    public:
        FSeasonModel();
        FSeasonModel(
            const FSeasonModel& From
        );
        virtual ~FSeasonModel() override = default;

        TSharedPtr<FSeasonModel> WithSeasonModelId(const TOptional<FString> SeasonModelId);
        TSharedPtr<FSeasonModel> WithName(const TOptional<FString> Name);
        TSharedPtr<FSeasonModel> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FSeasonModel> WithMaximumParticipants(const TOptional<int32> MaximumParticipants);
        TSharedPtr<FSeasonModel> WithExperienceModelId(const TOptional<FString> ExperienceModelId);
        TSharedPtr<FSeasonModel> WithChallengePeriodEventId(const TOptional<FString> ChallengePeriodEventId);

        TOptional<FString> GetSeasonModelId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetMetadata() const;
        TOptional<int32> GetMaximumParticipants() const;
        FString GetMaximumParticipantsString() const;
        TOptional<FString> GetExperienceModelId() const;
        TOptional<FString> GetChallengePeriodEventId() const;

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