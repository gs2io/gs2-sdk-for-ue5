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
#include "SeasonRating/Model/GameResult.h"

namespace Gs2::UE5::SeasonRating::Model
{
	class EZGS2_API FEzGameResult final : public TSharedFromThis<FEzGameResult>
	{
        TOptional<int32> RankValue;
        TOptional<FString> UserIdValue;

	public:
        TSharedPtr<FEzGameResult> WithRank(const TOptional<int32> Rank);
        TSharedPtr<FEzGameResult> WithUserId(const TOptional<FString> UserId);

        TOptional<int32> GetRank() const;
        FString GetRankString() const;

        TOptional<FString> GetUserId() const;

        Gs2::SeasonRating::Model::FGameResultPtr ToModel() const;
        static TSharedPtr<FEzGameResult> FromModel(Gs2::SeasonRating::Model::FGameResultPtr Model);
    };
    typedef TSharedPtr<FEzGameResult> FEzGameResultPtr;
}