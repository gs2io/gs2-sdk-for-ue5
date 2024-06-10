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
#include "../Model/GlobalRankingData.h"

namespace Gs2::Ranking2::Result
{
    class GS2RANKING2_API FGetGlobalRankingByUserIdResult final : public TSharedFromThis<FGetGlobalRankingByUserIdResult>
    {
        TSharedPtr<Model::FGlobalRankingData> ItemValue;
        
    public:
        
        FGetGlobalRankingByUserIdResult();
        FGetGlobalRankingByUserIdResult(
            const FGetGlobalRankingByUserIdResult& From
        );
        ~FGetGlobalRankingByUserIdResult() = default;

        TSharedPtr<FGetGlobalRankingByUserIdResult> WithItem(const TSharedPtr<Model::FGlobalRankingData> Item);

        TSharedPtr<Model::FGlobalRankingData> GetItem() const;

        static TSharedPtr<FGetGlobalRankingByUserIdResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetGlobalRankingByUserIdResult, ESPMode::ThreadSafe> FGetGlobalRankingByUserIdResultPtr;
}