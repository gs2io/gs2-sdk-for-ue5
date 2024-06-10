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
    class GS2RANKING2_API FClusterRankingData final : public Gs2Object, public TSharedFromThis<FClusterRankingData>
    {
        TOptional<FString> ClusterRankingDataIdValue;
        TOptional<FString> RankingNameValue;
        TOptional<FString> ClusterNameValue;
        TOptional<int64> SeasonValue;
        TOptional<FString> UserIdValue;
        TOptional<int32> IndexValue;
        TOptional<int32> RankValue;
        TOptional<int64> ScoreValue;
        TOptional<FString> MetadataValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> UpdatedAtValue;
        TOptional<int64> RevisionValue;

    public:
        FClusterRankingData();
        FClusterRankingData(
            const FClusterRankingData& From
        );
        virtual ~FClusterRankingData() override = default;

        TSharedPtr<FClusterRankingData> WithClusterRankingDataId(const TOptional<FString> ClusterRankingDataId);
        TSharedPtr<FClusterRankingData> WithRankingName(const TOptional<FString> RankingName);
        TSharedPtr<FClusterRankingData> WithClusterName(const TOptional<FString> ClusterName);
        TSharedPtr<FClusterRankingData> WithSeason(const TOptional<int64> Season);
        TSharedPtr<FClusterRankingData> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FClusterRankingData> WithIndex(const TOptional<int32> Index);
        TSharedPtr<FClusterRankingData> WithRank(const TOptional<int32> Rank);
        TSharedPtr<FClusterRankingData> WithScore(const TOptional<int64> Score);
        TSharedPtr<FClusterRankingData> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FClusterRankingData> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FClusterRankingData> WithUpdatedAt(const TOptional<int64> UpdatedAt);
        TSharedPtr<FClusterRankingData> WithRevision(const TOptional<int64> Revision);

        TOptional<FString> GetClusterRankingDataId() const;
        TOptional<FString> GetRankingName() const;
        TOptional<FString> GetClusterName() const;
        TOptional<int64> GetSeason() const;
        FString GetSeasonString() const;
        TOptional<FString> GetUserId() const;
        TOptional<int32> GetIndex() const;
        FString GetIndexString() const;
        TOptional<int32> GetRank() const;
        FString GetRankString() const;
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
        static TOptional<FString> GetRankingNameFromGrn(const FString Grn);
        static TOptional<FString> GetClusterNameFromGrn(const FString Grn);
        static TOptional<FString> GetSeasonFromGrn(const FString Grn);
        static TOptional<FString> GetUserIdFromGrn(const FString Grn);

        static TSharedPtr<FClusterRankingData> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FClusterRankingData, ESPMode::ThreadSafe> FClusterRankingDataPtr;
}