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
#include "../Model/RarityParameterModel.h"

namespace Gs2::Enchant::Result
{
    class GS2ENCHANT_API FGetRarityParameterModelResult final : public TSharedFromThis<FGetRarityParameterModelResult>
    {
        TSharedPtr<Model::FRarityParameterModel> ItemValue;
        
    public:
        
        FGetRarityParameterModelResult();
        FGetRarityParameterModelResult(
            const FGetRarityParameterModelResult& From
        );
        ~FGetRarityParameterModelResult() = default;

        TSharedPtr<FGetRarityParameterModelResult> WithItem(const TSharedPtr<Model::FRarityParameterModel> Item);

        TSharedPtr<Model::FRarityParameterModel> GetItem() const;

        static TSharedPtr<FGetRarityParameterModelResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetRarityParameterModelResult, ESPMode::ThreadSafe> FGetRarityParameterModelResultPtr;
}