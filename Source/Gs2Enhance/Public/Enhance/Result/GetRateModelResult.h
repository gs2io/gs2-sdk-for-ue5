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
#include "../Model/RateModel.h"

namespace Gs2::Enhance::Result
{
    class GS2ENHANCE_API FGetRateModelResult final : public TSharedFromThis<FGetRateModelResult>
    {
        TSharedPtr<Model::FRateModel> ItemValue;
        
    public:
        
        FGetRateModelResult();
        FGetRateModelResult(
            const FGetRateModelResult& From
        );
        ~FGetRateModelResult() = default;

        TSharedPtr<FGetRateModelResult> WithItem(const TSharedPtr<Model::FRateModel> Item);

        TSharedPtr<Model::FRateModel> GetItem() const;

        static TSharedPtr<FGetRateModelResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetRateModelResult, ESPMode::ThreadSafe> FGetRateModelResultPtr;
}