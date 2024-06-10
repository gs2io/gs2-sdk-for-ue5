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
#include "../Model/SubscribeRankingModelMaster.h"

namespace Gs2::Ranking2::Result
{
    class GS2RANKING2_API FCreateSubscribeRankingModelMasterResult final : public TSharedFromThis<FCreateSubscribeRankingModelMasterResult>
    {
        TSharedPtr<Model::FSubscribeRankingModelMaster> ItemValue;
        
    public:
        
        FCreateSubscribeRankingModelMasterResult();
        FCreateSubscribeRankingModelMasterResult(
            const FCreateSubscribeRankingModelMasterResult& From
        );
        ~FCreateSubscribeRankingModelMasterResult() = default;

        TSharedPtr<FCreateSubscribeRankingModelMasterResult> WithItem(const TSharedPtr<Model::FSubscribeRankingModelMaster> Item);

        TSharedPtr<Model::FSubscribeRankingModelMaster> GetItem() const;

        static TSharedPtr<FCreateSubscribeRankingModelMasterResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FCreateSubscribeRankingModelMasterResult, ESPMode::ThreadSafe> FCreateSubscribeRankingModelMasterResultPtr;
}