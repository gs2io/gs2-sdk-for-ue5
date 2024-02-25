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
#include "../Model/SeasonModelMaster.h"

namespace Gs2::SeasonRating::Result
{
    class GS2SEASONRATING_API FDeleteSeasonModelMasterResult final : public TSharedFromThis<FDeleteSeasonModelMasterResult>
    {
        TSharedPtr<Model::FSeasonModelMaster> ItemValue;
        
    public:
        
        FDeleteSeasonModelMasterResult();
        FDeleteSeasonModelMasterResult(
            const FDeleteSeasonModelMasterResult& From
        );
        ~FDeleteSeasonModelMasterResult() = default;

        TSharedPtr<FDeleteSeasonModelMasterResult> WithItem(const TSharedPtr<Model::FSeasonModelMaster> Item);

        TSharedPtr<Model::FSeasonModelMaster> GetItem() const;

        static TSharedPtr<FDeleteSeasonModelMasterResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDeleteSeasonModelMasterResult, ESPMode::ThreadSafe> FDeleteSeasonModelMasterResultPtr;
}