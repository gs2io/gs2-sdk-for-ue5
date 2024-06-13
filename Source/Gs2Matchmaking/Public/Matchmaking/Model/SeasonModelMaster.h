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
    class GS2MATCHMAKING_API FSeasonModelMaster final : public Gs2Object, public TSharedFromThis<FSeasonModelMaster>
    {
        TOptional<FString> SeasonModelIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;
        TOptional<FString> DescriptionValue;
        TOptional<int32> MaximumParticipantsValue;
        TOptional<FString> ExperienceModelIdValue;
        TOptional<FString> ChallengePeriodEventIdValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> UpdatedAtValue;
        TOptional<int64> RevisionValue;

    public:
        FSeasonModelMaster();
        FSeasonModelMaster(
            const FSeasonModelMaster& From
        );
        virtual ~FSeasonModelMaster() override = default;

        TSharedPtr<FSeasonModelMaster> WithSeasonModelId(const TOptional<FString> SeasonModelId);
        TSharedPtr<FSeasonModelMaster> WithName(const TOptional<FString> Name);
        TSharedPtr<FSeasonModelMaster> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FSeasonModelMaster> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FSeasonModelMaster> WithMaximumParticipants(const TOptional<int32> MaximumParticipants);
        TSharedPtr<FSeasonModelMaster> WithExperienceModelId(const TOptional<FString> ExperienceModelId);
        TSharedPtr<FSeasonModelMaster> WithChallengePeriodEventId(const TOptional<FString> ChallengePeriodEventId);
        TSharedPtr<FSeasonModelMaster> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FSeasonModelMaster> WithUpdatedAt(const TOptional<int64> UpdatedAt);
        TSharedPtr<FSeasonModelMaster> WithRevision(const TOptional<int64> Revision);

        TOptional<FString> GetSeasonModelId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetMetadata() const;
        TOptional<FString> GetDescription() const;
        TOptional<int32> GetMaximumParticipants() const;
        FString GetMaximumParticipantsString() const;
        TOptional<FString> GetExperienceModelId() const;
        TOptional<FString> GetChallengePeriodEventId() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;
        TOptional<int64> GetUpdatedAt() const;
        FString GetUpdatedAtString() const;
        TOptional<int64> GetRevision() const;
        FString GetRevisionString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetSeasonNameFromGrn(const FString Grn);

        static TSharedPtr<FSeasonModelMaster> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FSeasonModelMaster, ESPMode::ThreadSafe> FSeasonModelMasterPtr;
}