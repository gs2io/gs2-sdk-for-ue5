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
#include "../Model/IncrementalRateModelMaster.h"

namespace Gs2::Exchange::Result
{
    class GS2EXCHANGE_API FDeleteIncrementalRateModelMasterResult final : public TSharedFromThis<FDeleteIncrementalRateModelMasterResult>
    {
        TSharedPtr<Model::FIncrementalRateModelMaster> ItemValue;
        
    public:
        
        FDeleteIncrementalRateModelMasterResult();
        FDeleteIncrementalRateModelMasterResult(
            const FDeleteIncrementalRateModelMasterResult& From
        );
        ~FDeleteIncrementalRateModelMasterResult() = default;

        TSharedPtr<FDeleteIncrementalRateModelMasterResult> WithItem(const TSharedPtr<Model::FIncrementalRateModelMaster> Item);

        TSharedPtr<Model::FIncrementalRateModelMaster> GetItem() const;

        static TSharedPtr<FDeleteIncrementalRateModelMasterResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDeleteIncrementalRateModelMasterResult, ESPMode::ThreadSafe> FDeleteIncrementalRateModelMasterResultPtr;
}