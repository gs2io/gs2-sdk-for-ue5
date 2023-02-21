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
#include "../Model/ThresholdMaster.h"

namespace Gs2::Experience::Result
{
    class GS2EXPERIENCE_API FGetThresholdMasterResult final : public TSharedFromThis<FGetThresholdMasterResult>
    {
        TSharedPtr<Model::FThresholdMaster> ItemValue;
        
    public:
        
        FGetThresholdMasterResult();
        FGetThresholdMasterResult(
            const FGetThresholdMasterResult& From
        );
        ~FGetThresholdMasterResult() = default;

        TSharedPtr<FGetThresholdMasterResult> WithItem(const TSharedPtr<Model::FThresholdMaster> Item);

        TSharedPtr<Model::FThresholdMaster> GetItem() const;

        static TSharedPtr<FGetThresholdMasterResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetThresholdMasterResult, ESPMode::ThreadSafe> FGetThresholdMasterResultPtr;
}