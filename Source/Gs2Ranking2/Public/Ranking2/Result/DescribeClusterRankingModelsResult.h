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
#include "../Model/ClusterRankingModel.h"

namespace Gs2::Ranking2::Result
{
    class GS2RANKING2_API FDescribeClusterRankingModelsResult final : public TSharedFromThis<FDescribeClusterRankingModelsResult>
    {
        TSharedPtr<TArray<TSharedPtr<Model::FClusterRankingModel>>> ItemsValue;
        
    public:
        
        FDescribeClusterRankingModelsResult();
        FDescribeClusterRankingModelsResult(
            const FDescribeClusterRankingModelsResult& From
        );
        ~FDescribeClusterRankingModelsResult() = default;

        TSharedPtr<FDescribeClusterRankingModelsResult> WithItems(const TSharedPtr<TArray<TSharedPtr<Model::FClusterRankingModel>>> Items);

        TSharedPtr<TArray<TSharedPtr<Model::FClusterRankingModel>>> GetItems() const;

        static TSharedPtr<FDescribeClusterRankingModelsResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDescribeClusterRankingModelsResult, ESPMode::ThreadSafe> FDescribeClusterRankingModelsResultPtr;
}