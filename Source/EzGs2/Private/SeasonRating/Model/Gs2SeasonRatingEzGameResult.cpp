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

#include "SeasonRating/Model/Gs2SeasonRatingEzGameResult.h"

namespace Gs2::UE5::SeasonRating::Model
{

    TSharedPtr<FEzGameResult> FEzGameResult::WithRank(
        const TOptional<int32> Rank
    )
    {
        this->RankValue = Rank;
        return SharedThis(this);
    }

    TSharedPtr<FEzGameResult> FEzGameResult::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }
    TOptional<int32> FEzGameResult::GetRank() const
    {
        return RankValue;
    }

    FString FEzGameResult::GetRankString() const
    {
        if (!RankValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), RankValue.GetValue());
    }
    TOptional<FString> FEzGameResult::GetUserId() const
    {
        return UserIdValue;
    }

    Gs2::SeasonRating::Model::FGameResultPtr FEzGameResult::ToModel() const
    {
        return MakeShared<Gs2::SeasonRating::Model::FGameResult>()
            ->WithRank(RankValue)
            ->WithUserId(UserIdValue);
    }

    TSharedPtr<FEzGameResult> FEzGameResult::FromModel(const Gs2::SeasonRating::Model::FGameResultPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzGameResult>()
            ->WithRank(Model->GetRank())
            ->WithUserId(Model->GetUserId());
    }
}