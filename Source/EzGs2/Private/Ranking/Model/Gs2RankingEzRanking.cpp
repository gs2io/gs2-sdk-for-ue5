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

#include "EzGs2/Public/Ranking/Model/Gs2RankingEzRanking.h"

namespace Gs2::UE5::Ranking::Model
{

    TSharedPtr<FEzRanking> FEzRanking::WithRank(
        const TOptional<int64> Rank
    )
    {
        this->RankValue = Rank;
        return SharedThis(this);
    }

    TSharedPtr<FEzRanking> FEzRanking::WithIndex(
        const TOptional<int64> Index
    )
    {
        this->IndexValue = Index;
        return SharedThis(this);
    }

    TSharedPtr<FEzRanking> FEzRanking::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FEzRanking> FEzRanking::WithScore(
        const TOptional<int64> Score
    )
    {
        this->ScoreValue = Score;
        return SharedThis(this);
    }

    TSharedPtr<FEzRanking> FEzRanking::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FEzRanking> FEzRanking::WithCreatedAt(
        const TOptional<int64> CreatedAt
    )
    {
        this->CreatedAtValue = CreatedAt;
        return SharedThis(this);
    }
    TOptional<int64> FEzRanking::GetRank() const
    {
        return RankValue;
    }

    FString FEzRanking::GetRankString() const
    {
        if (!RankValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), RankValue.GetValue());
    }
    TOptional<int64> FEzRanking::GetIndex() const
    {
        return IndexValue;
    }

    FString FEzRanking::GetIndexString() const
    {
        if (!IndexValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), IndexValue.GetValue());
    }
    TOptional<FString> FEzRanking::GetUserId() const
    {
        return UserIdValue;
    }
    TOptional<int64> FEzRanking::GetScore() const
    {
        return ScoreValue;
    }

    FString FEzRanking::GetScoreString() const
    {
        if (!ScoreValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), ScoreValue.GetValue());
    }
    TOptional<FString> FEzRanking::GetMetadata() const
    {
        return MetadataValue;
    }
    TOptional<int64> FEzRanking::GetCreatedAt() const
    {
        return CreatedAtValue;
    }

    FString FEzRanking::GetCreatedAtString() const
    {
        if (!CreatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue());
    }

    Gs2::Ranking::Model::FRankingPtr FEzRanking::ToModel() const
    {
        return MakeShared<Gs2::Ranking::Model::FRanking>()
            ->WithRank(RankValue)
            ->WithIndex(IndexValue)
            ->WithUserId(UserIdValue)
            ->WithScore(ScoreValue)
            ->WithMetadata(MetadataValue)
            ->WithCreatedAt(CreatedAtValue);
    }

    TSharedPtr<FEzRanking> FEzRanking::FromModel(const Gs2::Ranking::Model::FRankingPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzRanking>()
            ->WithRank(Model->GetRank())
            ->WithIndex(Model->GetIndex())
            ->WithUserId(Model->GetUserId())
            ->WithScore(Model->GetScore())
            ->WithMetadata(Model->GetMetadata())
            ->WithCreatedAt(Model->GetCreatedAt());
    }
}