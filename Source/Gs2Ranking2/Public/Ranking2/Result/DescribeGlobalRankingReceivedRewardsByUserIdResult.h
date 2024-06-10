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
#include "../Model/GlobalRankingReceivedReward.h"

namespace Gs2::Ranking2::Result
{
    class GS2RANKING2_API FDescribeGlobalRankingReceivedRewardsByUserIdResult final : public TSharedFromThis<FDescribeGlobalRankingReceivedRewardsByUserIdResult>
    {
        TSharedPtr<TArray<TSharedPtr<Model::FGlobalRankingReceivedReward>>> ItemsValue;
        TOptional<FString> NextPageTokenValue;
        
    public:
        
        FDescribeGlobalRankingReceivedRewardsByUserIdResult();
        FDescribeGlobalRankingReceivedRewardsByUserIdResult(
            const FDescribeGlobalRankingReceivedRewardsByUserIdResult& From
        );
        ~FDescribeGlobalRankingReceivedRewardsByUserIdResult() = default;

        TSharedPtr<FDescribeGlobalRankingReceivedRewardsByUserIdResult> WithItems(const TSharedPtr<TArray<TSharedPtr<Model::FGlobalRankingReceivedReward>>> Items);
        TSharedPtr<FDescribeGlobalRankingReceivedRewardsByUserIdResult> WithNextPageToken(const TOptional<FString> NextPageToken);

        TSharedPtr<TArray<TSharedPtr<Model::FGlobalRankingReceivedReward>>> GetItems() const;
        TOptional<FString> GetNextPageToken() const;

        static TSharedPtr<FDescribeGlobalRankingReceivedRewardsByUserIdResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDescribeGlobalRankingReceivedRewardsByUserIdResult, ESPMode::ThreadSafe> FDescribeGlobalRankingReceivedRewardsByUserIdResultPtr;
}