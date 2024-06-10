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
    class GS2RANKING2_API FGetClusterRankingScoreResult final : public TSharedFromThis<FGetClusterRankingScoreResult>
    {
        TSharedPtr<Model::FClusterRankingScore> ItemValue;
        
    public:
        
        FGetClusterRankingScoreResult();
        FGetClusterRankingScoreResult(
            const FGetClusterRankingScoreResult& From
        );
        ~FGetClusterRankingScoreResult() = default;

        TSharedPtr<FGetClusterRankingScoreResult> WithItem(const TSharedPtr<Model::FClusterRankingScore> Item);

        TSharedPtr<Model::FClusterRankingScore> GetItem() const;

        static TSharedPtr<FGetClusterRankingScoreResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetClusterRankingScoreResult, ESPMode::ThreadSafe> FGetClusterRankingScoreResultPtr;
}