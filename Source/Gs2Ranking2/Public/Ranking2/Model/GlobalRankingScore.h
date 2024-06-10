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

namespace Gs2::Ranking2::Model
{
    class GS2RANKING2_API FGlobalRankingScore final : public Gs2Object, public TSharedFromThis<FGlobalRankingScore>
    {
        TOptional<FString> GlobalRankingScoreIdValue;
        TOptional<FString> RankingNameValue;
        TOptional<FString> UserIdValue;
        TOptional<int64> SeasonValue;
        TOptional<int64> ScoreValue;
        TOptional<FString> MetadataValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> UpdatedAtValue;
        TOptional<int64> RevisionValue;

    public:
        FGlobalRankingScore();
        FGlobalRankingScore(
            const FGlobalRankingScore& From
        );
        virtual ~FGlobalRankingScore() override = default;

        TSharedPtr<FGlobalRankingScore> WithGlobalRankingScoreId(const TOptional<FString> GlobalRankingScoreId);
        TSharedPtr<FGlobalRankingScore> WithRankingName(const TOptional<FString> RankingName);
        TSharedPtr<FGlobalRankingScore> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FGlobalRankingScore> WithSeason(const TOptional<int64> Season);
        TSharedPtr<FGlobalRankingScore> WithScore(const TOptional<int64> Score);
        TSharedPtr<FGlobalRankingScore> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FGlobalRankingScore> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FGlobalRankingScore> WithUpdatedAt(const TOptional<int64> UpdatedAt);
        TSharedPtr<FGlobalRankingScore> WithRevision(const TOptional<int64> Revision);

        TOptional<FString> GetGlobalRankingScoreId() const;
        TOptional<FString> GetRankingName() const;
        TOptional<FString> GetUserId() const;
        TOptional<int64> GetSeason() const;
        FString GetSeasonString() const;
        TOptional<int64> GetScore() const;
        FString GetScoreString() const;
        TOptional<FString> GetMetadata() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;
        TOptional<int64> GetUpdatedAt() const;
        FString GetUpdatedAtString() const;
        TOptional<int64> GetRevision() const;
        FString GetRevisionString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetUserIdFromGrn(const FString Grn);
        static TOptional<FString> GetRankingNameFromGrn(const FString Grn);
        static TOptional<FString> GetSeasonFromGrn(const FString Grn);

        static TSharedPtr<FGlobalRankingScore> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FGlobalRankingScore, ESPMode::ThreadSafe> FGlobalRankingScorePtr;
}