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

namespace Gs2::Ranking::Model
{
    class GS2RANKING_API FRanking final : public Gs2Object, public TSharedFromThis<FRanking>
    {
        TOptional<int64> RankValue;
        TOptional<int64> IndexValue;
        TOptional<FString> CategoryNameValue;
        TOptional<FString> UserIdValue;
        TOptional<int64> ScoreValue;
        TOptional<FString> MetadataValue;
        TOptional<int64> CreatedAtValue;

    public:
        FRanking();
        FRanking(
            const FRanking& From
        );
        virtual ~FRanking() override = default;

        TSharedPtr<FRanking> WithRank(const TOptional<int64> Rank);
        TSharedPtr<FRanking> WithIndex(const TOptional<int64> Index);
        TSharedPtr<FRanking> WithCategoryName(const TOptional<FString> CategoryName);
        TSharedPtr<FRanking> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FRanking> WithScore(const TOptional<int64> Score);
        TSharedPtr<FRanking> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FRanking> WithCreatedAt(const TOptional<int64> CreatedAt);

        TOptional<int64> GetRank() const;
        FString GetRankString() const;
        TOptional<int64> GetIndex() const;
        FString GetIndexString() const;
        TOptional<FString> GetCategoryName() const;
        TOptional<FString> GetUserId() const;
        TOptional<int64> GetScore() const;
        FString GetScoreString() const;
        TOptional<FString> GetMetadata() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;


        static TSharedPtr<FRanking> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FRanking, ESPMode::ThreadSafe> FRankingPtr;
}