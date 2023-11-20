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

#include "Ranking/Model/Gs2RankingEzScore.h"

namespace Gs2::UE5::Ranking::Model
{

    TSharedPtr<FEzScore> FEzScore::WithCategoryName(
        const TOptional<FString> CategoryName
    )
    {
        this->CategoryNameValue = CategoryName;
        return SharedThis(this);
    }

    TSharedPtr<FEzScore> FEzScore::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FEzScore> FEzScore::WithUniqueId(
        const TOptional<FString> UniqueId
    )
    {
        this->UniqueIdValue = UniqueId;
        return SharedThis(this);
    }

    TSharedPtr<FEzScore> FEzScore::WithScorerUserId(
        const TOptional<FString> ScorerUserId
    )
    {
        this->ScorerUserIdValue = ScorerUserId;
        return SharedThis(this);
    }

    TSharedPtr<FEzScore> FEzScore::WithScore(
        const TOptional<int64> Score
    )
    {
        this->ScoreValue = Score;
        return SharedThis(this);
    }

    TSharedPtr<FEzScore> FEzScore::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }
    TOptional<FString> FEzScore::GetCategoryName() const
    {
        return CategoryNameValue;
    }
    TOptional<FString> FEzScore::GetUserId() const
    {
        return UserIdValue;
    }
    TOptional<FString> FEzScore::GetUniqueId() const
    {
        return UniqueIdValue;
    }
    TOptional<FString> FEzScore::GetScorerUserId() const
    {
        return ScorerUserIdValue;
    }
    TOptional<int64> FEzScore::GetScore() const
    {
        return ScoreValue;
    }

    FString FEzScore::GetScoreString() const
    {
        if (!ScoreValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), ScoreValue.GetValue());
    }
    TOptional<FString> FEzScore::GetMetadata() const
    {
        return MetadataValue;
    }

    Gs2::Ranking::Model::FScorePtr FEzScore::ToModel() const
    {
        return MakeShared<Gs2::Ranking::Model::FScore>()
            ->WithCategoryName(CategoryNameValue)
            ->WithUserId(UserIdValue)
            ->WithUniqueId(UniqueIdValue)
            ->WithScorerUserId(ScorerUserIdValue)
            ->WithScore(ScoreValue)
            ->WithMetadata(MetadataValue);
    }

    TSharedPtr<FEzScore> FEzScore::FromModel(const Gs2::Ranking::Model::FScorePtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzScore>()
            ->WithCategoryName(Model->GetCategoryName())
            ->WithUserId(Model->GetUserId())
            ->WithUniqueId(Model->GetUniqueId())
            ->WithScorerUserId(Model->GetScorerUserId())
            ->WithScore(Model->GetScore())
            ->WithMetadata(Model->GetMetadata());
    }
}