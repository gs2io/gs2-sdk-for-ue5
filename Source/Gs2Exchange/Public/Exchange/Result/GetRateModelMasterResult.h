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
#include "../Model/RateModelMaster.h"

namespace Gs2::Exchange::Result
{
    class GS2EXCHANGE_API FGetRateModelMasterResult final : public TSharedFromThis<FGetRateModelMasterResult>
    {
        TSharedPtr<Model::FRateModelMaster> ItemValue;
        
    public:
        
        FGetRateModelMasterResult();
        FGetRateModelMasterResult(
            const FGetRateModelMasterResult& From
        );
        ~FGetRateModelMasterResult() = default;

        TSharedPtr<FGetRateModelMasterResult> WithItem(const TSharedPtr<Model::FRateModelMaster> Item);

        TSharedPtr<Model::FRateModelMaster> GetItem() const;

        static TSharedPtr<FGetRateModelMasterResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetRateModelMasterResult, ESPMode::ThreadSafe> FGetRateModelMasterResultPtr;
}