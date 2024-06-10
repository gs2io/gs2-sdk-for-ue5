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
#include "../Model/GlobalRankingModel.h"

namespace Gs2::Ranking2::Result
{
    class GS2RANKING2_API FGetGlobalRankingModelResult final : public TSharedFromThis<FGetGlobalRankingModelResult>
    {
        TSharedPtr<Model::FGlobalRankingModel> ItemValue;
        
    public:
        
        FGetGlobalRankingModelResult();
        FGetGlobalRankingModelResult(
            const FGetGlobalRankingModelResult& From
        );
        ~FGetGlobalRankingModelResult() = default;

        TSharedPtr<FGetGlobalRankingModelResult> WithItem(const TSharedPtr<Model::FGlobalRankingModel> Item);

        TSharedPtr<Model::FGlobalRankingModel> GetItem() const;

        static TSharedPtr<FGetGlobalRankingModelResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetGlobalRankingModelResult, ESPMode::ThreadSafe> FGetGlobalRankingModelResultPtr;
}