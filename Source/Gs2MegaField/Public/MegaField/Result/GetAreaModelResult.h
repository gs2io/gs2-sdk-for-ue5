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
#include "../Model/AreaModel.h"

namespace Gs2::MegaField::Result
{
    class GS2MEGAFIELD_API FGetAreaModelResult final : public TSharedFromThis<FGetAreaModelResult>
    {
        TSharedPtr<Model::FAreaModel> ItemValue;
        
    public:
        
        FGetAreaModelResult();
        FGetAreaModelResult(
            const FGetAreaModelResult& From
        );
        ~FGetAreaModelResult() = default;

        TSharedPtr<FGetAreaModelResult> WithItem(const TSharedPtr<Model::FAreaModel> Item);

        TSharedPtr<Model::FAreaModel> GetItem() const;

        static TSharedPtr<FGetAreaModelResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetAreaModelResult, ESPMode::ThreadSafe> FGetAreaModelResultPtr;
}