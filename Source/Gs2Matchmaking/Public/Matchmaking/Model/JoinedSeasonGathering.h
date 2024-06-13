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
    class GS2MATCHMAKING_API FJoinedSeasonGathering final : public Gs2Object, public TSharedFromThis<FJoinedSeasonGathering>
    {
        TOptional<FString> JoinedSeasonGatheringIdValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> SeasonNameValue;
        TOptional<int64> SeasonValue;
        TOptional<int64> TierValue;
        TOptional<FString> SeasonGatheringNameValue;
        TOptional<int64> CreatedAtValue;

    public:
        FJoinedSeasonGathering();
        FJoinedSeasonGathering(
            const FJoinedSeasonGathering& From
        );
        virtual ~FJoinedSeasonGathering() override = default;

        TSharedPtr<FJoinedSeasonGathering> WithJoinedSeasonGatheringId(const TOptional<FString> JoinedSeasonGatheringId);
        TSharedPtr<FJoinedSeasonGathering> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FJoinedSeasonGathering> WithSeasonName(const TOptional<FString> SeasonName);
        TSharedPtr<FJoinedSeasonGathering> WithSeason(const TOptional<int64> Season);
        TSharedPtr<FJoinedSeasonGathering> WithTier(const TOptional<int64> Tier);
        TSharedPtr<FJoinedSeasonGathering> WithSeasonGatheringName(const TOptional<FString> SeasonGatheringName);
        TSharedPtr<FJoinedSeasonGathering> WithCreatedAt(const TOptional<int64> CreatedAt);

        TOptional<FString> GetJoinedSeasonGatheringId() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetSeasonName() const;
        TOptional<int64> GetSeason() const;
        FString GetSeasonString() const;
        TOptional<int64> GetTier() const;
        FString GetTierString() const;
        TOptional<FString> GetSeasonGatheringName() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetSeasonNameFromGrn(const FString Grn);
        static TOptional<FString> GetSeasonFromGrn(const FString Grn);
        static TOptional<FString> GetUserIdFromGrn(const FString Grn);

        static TSharedPtr<FJoinedSeasonGathering> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FJoinedSeasonGathering, ESPMode::ThreadSafe> FJoinedSeasonGatheringPtr;
}