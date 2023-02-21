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
#include "../Model/CurrentRatingModelMaster.h"

namespace Gs2::Matchmaking::Result
{
    class GS2MATCHMAKING_API FUpdateCurrentRatingModelMasterResult final : public TSharedFromThis<FUpdateCurrentRatingModelMasterResult>
    {
        TSharedPtr<Model::FCurrentRatingModelMaster> ItemValue;
        
    public:
        
        FUpdateCurrentRatingModelMasterResult();
        FUpdateCurrentRatingModelMasterResult(
            const FUpdateCurrentRatingModelMasterResult& From
        );
        ~FUpdateCurrentRatingModelMasterResult() = default;

        TSharedPtr<FUpdateCurrentRatingModelMasterResult> WithItem(const TSharedPtr<Model::FCurrentRatingModelMaster> Item);

        TSharedPtr<Model::FCurrentRatingModelMaster> GetItem() const;

        static TSharedPtr<FUpdateCurrentRatingModelMasterResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUpdateCurrentRatingModelMasterResult, ESPMode::ThreadSafe> FUpdateCurrentRatingModelMasterResultPtr;
}