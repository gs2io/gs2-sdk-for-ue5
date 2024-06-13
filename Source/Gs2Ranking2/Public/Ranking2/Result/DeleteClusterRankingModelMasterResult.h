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
#include "../Model/ClusterRankingModelMaster.h"

namespace Gs2::Ranking2::Result
{
    class GS2RANKING2_API FDeleteClusterRankingModelMasterResult final : public TSharedFromThis<FDeleteClusterRankingModelMasterResult>
    {
        TSharedPtr<Model::FClusterRankingModelMaster> ItemValue;
        
    public:
        
        FDeleteClusterRankingModelMasterResult();
        FDeleteClusterRankingModelMasterResult(
            const FDeleteClusterRankingModelMasterResult& From
        );
        ~FDeleteClusterRankingModelMasterResult() = default;

        TSharedPtr<FDeleteClusterRankingModelMasterResult> WithItem(const TSharedPtr<Model::FClusterRankingModelMaster> Item);

        TSharedPtr<Model::FClusterRankingModelMaster> GetItem() const;

        static TSharedPtr<FDeleteClusterRankingModelMasterResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDeleteClusterRankingModelMasterResult, ESPMode::ThreadSafe> FDeleteClusterRankingModelMasterResultPtr;
}