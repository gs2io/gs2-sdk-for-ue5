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
#include "../Model/GlobalRankingScore.h"

namespace Gs2::Ranking2::Result
{
    class GS2RANKING2_API FDescribeGlobalRankingScoresResult final : public TSharedFromThis<FDescribeGlobalRankingScoresResult>
    {
        TSharedPtr<TArray<TSharedPtr<Model::FGlobalRankingScore>>> ItemsValue;
        TOptional<FString> NextPageTokenValue;
        
    public:
        
        FDescribeGlobalRankingScoresResult();
        FDescribeGlobalRankingScoresResult(
            const FDescribeGlobalRankingScoresResult& From
        );
        ~FDescribeGlobalRankingScoresResult() = default;

        TSharedPtr<FDescribeGlobalRankingScoresResult> WithItems(const TSharedPtr<TArray<TSharedPtr<Model::FGlobalRankingScore>>> Items);
        TSharedPtr<FDescribeGlobalRankingScoresResult> WithNextPageToken(const TOptional<FString> NextPageToken);

        TSharedPtr<TArray<TSharedPtr<Model::FGlobalRankingScore>>> GetItems() const;
        TOptional<FString> GetNextPageToken() const;

        static TSharedPtr<FDescribeGlobalRankingScoresResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDescribeGlobalRankingScoresResult, ESPMode::ThreadSafe> FDescribeGlobalRankingScoresResultPtr;
}