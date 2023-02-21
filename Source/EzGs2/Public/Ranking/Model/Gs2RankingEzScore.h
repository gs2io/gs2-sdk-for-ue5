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
#include "Ranking/Model/Score.h"

namespace Gs2::UE5::Ranking::Model
{
	class EZGS2_API FEzScore final : public TSharedFromThis<FEzScore>
	{
        TOptional<FString> CategoryNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> UniqueIdValue;
        TOptional<FString> ScorerUserIdValue;
        TOptional<int64> ScoreValue;
        TOptional<FString> MetadataValue;

	public:
        TSharedPtr<FEzScore> WithCategoryName(const TOptional<FString> CategoryName);
        TSharedPtr<FEzScore> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FEzScore> WithUniqueId(const TOptional<FString> UniqueId);
        TSharedPtr<FEzScore> WithScorerUserId(const TOptional<FString> ScorerUserId);
        TSharedPtr<FEzScore> WithScore(const TOptional<int64> Score);
        TSharedPtr<FEzScore> WithMetadata(const TOptional<FString> Metadata);

        TOptional<FString> GetCategoryName() const;

        TOptional<FString> GetUserId() const;

        TOptional<FString> GetUniqueId() const;

        TOptional<FString> GetScorerUserId() const;

        TOptional<int64> GetScore() const;
        FString GetScoreString() const;

        TOptional<FString> GetMetadata() const;

        Gs2::Ranking::Model::FScorePtr ToModel() const;
        static TSharedPtr<FEzScore> FromModel(Gs2::Ranking::Model::FScorePtr Model);
    };
    typedef TSharedPtr<FEzScore> FEzScorePtr;
}