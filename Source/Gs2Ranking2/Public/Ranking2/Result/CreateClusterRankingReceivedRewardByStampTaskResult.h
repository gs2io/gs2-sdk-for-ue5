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
#include "../Model/ClusterRankingReceivedReward.h"

namespace Gs2::Ranking2::Result
{
    class GS2RANKING2_API FCreateClusterRankingReceivedRewardByStampTaskResult final : public TSharedFromThis<FCreateClusterRankingReceivedRewardByStampTaskResult>
    {
        TSharedPtr<Model::FClusterRankingReceivedReward> ItemValue;
        TOptional<FString> NewContextStackValue;
        
    public:
        
        FCreateClusterRankingReceivedRewardByStampTaskResult();
        FCreateClusterRankingReceivedRewardByStampTaskResult(
            const FCreateClusterRankingReceivedRewardByStampTaskResult& From
        );
        ~FCreateClusterRankingReceivedRewardByStampTaskResult() = default;

        TSharedPtr<FCreateClusterRankingReceivedRewardByStampTaskResult> WithItem(const TSharedPtr<Model::FClusterRankingReceivedReward> Item);
        TSharedPtr<FCreateClusterRankingReceivedRewardByStampTaskResult> WithNewContextStack(const TOptional<FString> NewContextStack);

        TSharedPtr<Model::FClusterRankingReceivedReward> GetItem() const;
        TOptional<FString> GetNewContextStack() const;

        static TSharedPtr<FCreateClusterRankingReceivedRewardByStampTaskResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FCreateClusterRankingReceivedRewardByStampTaskResult, ESPMode::ThreadSafe> FCreateClusterRankingReceivedRewardByStampTaskResultPtr;
}