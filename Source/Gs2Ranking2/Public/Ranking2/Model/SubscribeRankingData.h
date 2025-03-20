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
    class GS2RANKING2_API FSubscribeRankingData final : public FGs2Object, public TSharedFromThis<FSubscribeRankingData>
    {
        TOptional<FString> SubscribeRankingDataIdValue;
        TOptional<FString> RankingNameValue;
        TOptional<int64> SeasonValue;
        TOptional<FString> UserIdValue;
        TOptional<int32> IndexValue;
        TOptional<int32> RankValue;
        TOptional<FString> ScorerUserIdValue;
        TOptional<int64> ScoreValue;
        TOptional<FString> MetadataValue;
        TOptional<int64> InvertCreatedAtValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> UpdatedAtValue;
        TOptional<int64> RevisionValue;

    public:
        FSubscribeRankingData();
        FSubscribeRankingData(
            const FSubscribeRankingData& From
        );
        virtual ~FSubscribeRankingData() override = default;

        TSharedPtr<FSubscribeRankingData> WithSubscribeRankingDataId(const TOptional<FString> SubscribeRankingDataId);
        TSharedPtr<FSubscribeRankingData> WithRankingName(const TOptional<FString> RankingName);
        TSharedPtr<FSubscribeRankingData> WithSeason(const TOptional<int64> Season);
        TSharedPtr<FSubscribeRankingData> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FSubscribeRankingData> WithIndex(const TOptional<int32> Index);
        TSharedPtr<FSubscribeRankingData> WithRank(const TOptional<int32> Rank);
        TSharedPtr<FSubscribeRankingData> WithScorerUserId(const TOptional<FString> ScorerUserId);
        TSharedPtr<FSubscribeRankingData> WithScore(const TOptional<int64> Score);
        TSharedPtr<FSubscribeRankingData> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FSubscribeRankingData> WithInvertCreatedAt(const TOptional<int64> InvertCreatedAt);
        TSharedPtr<FSubscribeRankingData> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FSubscribeRankingData> WithUpdatedAt(const TOptional<int64> UpdatedAt);
        TSharedPtr<FSubscribeRankingData> WithRevision(const TOptional<int64> Revision);

        TOptional<FString> GetSubscribeRankingDataId() const;
        TOptional<FString> GetRankingName() const;
        TOptional<int64> GetSeason() const;
        FString GetSeasonString() const;
        TOptional<FString> GetUserId() const;
        TOptional<int32> GetIndex() const;
        FString GetIndexString() const;
        TOptional<int32> GetRank() const;
        FString GetRankString() const;
        TOptional<FString> GetScorerUserId() const;
        TOptional<int64> GetScore() const;
        FString GetScoreString() const;
        TOptional<FString> GetMetadata() const;
        TOptional<int64> GetInvertCreatedAt() const;
        FString GetInvertCreatedAtString() const;
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
        static TOptional<FString> GetScorerUserIdFromGrn(const FString Grn);

        static TSharedPtr<FSubscribeRankingData> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FSubscribeRankingData, ESPMode::ThreadSafe> FSubscribeRankingDataPtr;
}