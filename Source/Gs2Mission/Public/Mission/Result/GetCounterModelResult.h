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
#include "../Model/CounterModel.h"

namespace Gs2::Mission::Result
{
    class GS2MISSION_API FGetCounterModelResult final : public TSharedFromThis<FGetCounterModelResult>
    {
        TSharedPtr<Model::FCounterModel> ItemValue;
        
    public:
        
        FGetCounterModelResult();
        FGetCounterModelResult(
            const FGetCounterModelResult& From
        );
        ~FGetCounterModelResult() = default;

        TSharedPtr<FGetCounterModelResult> WithItem(const TSharedPtr<Model::FCounterModel> Item);

        TSharedPtr<Model::FCounterModel> GetItem() const;

        static TSharedPtr<FGetCounterModelResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetCounterModelResult, ESPMode::ThreadSafe> FGetCounterModelResultPtr;
}