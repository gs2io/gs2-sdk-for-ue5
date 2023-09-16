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
#include "../Model/Point.h"

namespace Gs2::AdReward::Result
{
    class GS2ADREWARD_API FConsumePointResult final : public TSharedFromThis<FConsumePointResult>
    {
        TSharedPtr<Model::FPoint> ItemValue;
        
    public:
        
        FConsumePointResult();
        FConsumePointResult(
            const FConsumePointResult& From
        );
        ~FConsumePointResult() = default;

        TSharedPtr<FConsumePointResult> WithItem(const TSharedPtr<Model::FPoint> Item);

        TSharedPtr<Model::FPoint> GetItem() const;

        static TSharedPtr<FConsumePointResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FConsumePointResult, ESPMode::ThreadSafe> FConsumePointResultPtr;
}