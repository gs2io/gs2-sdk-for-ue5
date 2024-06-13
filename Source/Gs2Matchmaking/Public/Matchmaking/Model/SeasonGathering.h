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
    class GS2MATCHMAKING_API FSeasonGathering final : public Gs2Object, public TSharedFromThis<FSeasonGathering>
    {
        TOptional<FString> SeasonGatheringIdValue;
        TOptional<FString> SeasonNameValue;
        TOptional<int64> SeasonValue;
        TOptional<int64> TierValue;
        TOptional<FString> NameValue;
        TSharedPtr<TArray<FString>> ParticipantsValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> RevisionValue;

    public:
        FSeasonGathering();
        FSeasonGathering(
            const FSeasonGathering& From
        );
        virtual ~FSeasonGathering() override = default;

        TSharedPtr<FSeasonGathering> WithSeasonGatheringId(const TOptional<FString> SeasonGatheringId);
        TSharedPtr<FSeasonGathering> WithSeasonName(const TOptional<FString> SeasonName);
        TSharedPtr<FSeasonGathering> WithSeason(const TOptional<int64> Season);
        TSharedPtr<FSeasonGathering> WithTier(const TOptional<int64> Tier);
        TSharedPtr<FSeasonGathering> WithName(const TOptional<FString> Name);
        TSharedPtr<FSeasonGathering> WithParticipants(const TSharedPtr<TArray<FString>> Participants);
        TSharedPtr<FSeasonGathering> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FSeasonGathering> WithRevision(const TOptional<int64> Revision);

        TOptional<FString> GetSeasonGatheringId() const;
        TOptional<FString> GetSeasonName() const;
        TOptional<int64> GetSeason() const;
        FString GetSeasonString() const;
        TOptional<int64> GetTier() const;
        FString GetTierString() const;
        TOptional<FString> GetName() const;
        TSharedPtr<TArray<FString>> GetParticipants() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;
        TOptional<int64> GetRevision() const;
        FString GetRevisionString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetSeasonNameFromGrn(const FString Grn);
        static TOptional<FString> GetSeasonFromGrn(const FString Grn);
        static TOptional<FString> GetTierFromGrn(const FString Grn);
        static TOptional<FString> GetSeasonGatheringNameFromGrn(const FString Grn);

        static TSharedPtr<FSeasonGathering> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FSeasonGathering, ESPMode::ThreadSafe> FSeasonGatheringPtr;
}