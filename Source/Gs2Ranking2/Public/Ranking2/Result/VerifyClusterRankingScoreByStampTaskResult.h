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
#include "../Model/ClusterRankingScore.h"

namespace Gs2::Ranking2::Result
{
    class GS2RANKING2_API FVerifyClusterRankingScoreByStampTaskResult final : public TSharedFromThis<FVerifyClusterRankingScoreByStampTaskResult>
    {
        TSharedPtr<Model::FClusterRankingScore> ItemValue;
        TOptional<FString> NewContextStackValue;
        
    public:
        
        FVerifyClusterRankingScoreByStampTaskResult();
        FVerifyClusterRankingScoreByStampTaskResult(
            const FVerifyClusterRankingScoreByStampTaskResult& From
        );
        ~FVerifyClusterRankingScoreByStampTaskResult() = default;

        TSharedPtr<FVerifyClusterRankingScoreByStampTaskResult> WithItem(const TSharedPtr<Model::FClusterRankingScore> Item);
        TSharedPtr<FVerifyClusterRankingScoreByStampTaskResult> WithNewContextStack(const TOptional<FString> NewContextStack);

        TSharedPtr<Model::FClusterRankingScore> GetItem() const;
        TOptional<FString> GetNewContextStack() const;

        static TSharedPtr<FVerifyClusterRankingScoreByStampTaskResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FVerifyClusterRankingScoreByStampTaskResult, ESPMode::ThreadSafe> FVerifyClusterRankingScoreByStampTaskResultPtr;
}