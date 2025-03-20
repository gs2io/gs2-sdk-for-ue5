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
#include "WrittenBallot.h"

namespace Gs2::Matchmaking::Model
{
    class GS2MATCHMAKING_API FVote final : public FGs2Object, public TSharedFromThis<FVote>
    {
        TOptional<FString> VoteIdValue;
        TOptional<FString> RatingNameValue;
        TOptional<FString> GatheringNameValue;
        TSharedPtr<TArray<TSharedPtr<FWrittenBallot>>> WrittenBallotsValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> UpdatedAtValue;

    public:
        FVote();
        FVote(
            const FVote& From
        );
        virtual ~FVote() override = default;

        TSharedPtr<FVote> WithVoteId(const TOptional<FString> VoteId);
        TSharedPtr<FVote> WithRatingName(const TOptional<FString> RatingName);
        TSharedPtr<FVote> WithGatheringName(const TOptional<FString> GatheringName);
        TSharedPtr<FVote> WithWrittenBallots(const TSharedPtr<TArray<TSharedPtr<FWrittenBallot>>> WrittenBallots);
        TSharedPtr<FVote> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FVote> WithUpdatedAt(const TOptional<int64> UpdatedAt);

        TOptional<FString> GetVoteId() const;
        TOptional<FString> GetRatingName() const;
        TOptional<FString> GetGatheringName() const;
        TSharedPtr<TArray<TSharedPtr<FWrittenBallot>>> GetWrittenBallots() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;
        TOptional<int64> GetUpdatedAt() const;
        FString GetUpdatedAtString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetRatingNameFromGrn(const FString Grn);
        static TOptional<FString> GetGatheringNameFromGrn(const FString Grn);

        static TSharedPtr<FVote> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FVote, ESPMode::ThreadSafe> FVotePtr;
}