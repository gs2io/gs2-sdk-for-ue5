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
#include "../Model/LimitModelMaster.h"

namespace Gs2::Limit::Result
{
    class GS2LIMIT_API FUpdateLimitModelMasterResult final : public TSharedFromThis<FUpdateLimitModelMasterResult>
    {
        TSharedPtr<Model::FLimitModelMaster> ItemValue;
        
    public:
        
        FUpdateLimitModelMasterResult();
        FUpdateLimitModelMasterResult(
            const FUpdateLimitModelMasterResult& From
        );
        ~FUpdateLimitModelMasterResult() = default;

        TSharedPtr<FUpdateLimitModelMasterResult> WithItem(const TSharedPtr<Model::FLimitModelMaster> Item);

        TSharedPtr<Model::FLimitModelMaster> GetItem() const;

        static TSharedPtr<FUpdateLimitModelMasterResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUpdateLimitModelMasterResult, ESPMode::ThreadSafe> FUpdateLimitModelMasterResultPtr;
}