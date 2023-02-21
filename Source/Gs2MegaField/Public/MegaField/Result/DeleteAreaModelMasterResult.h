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
#include "../Model/AreaModelMaster.h"

namespace Gs2::MegaField::Result
{
    class GS2MEGAFIELD_API FDeleteAreaModelMasterResult final : public TSharedFromThis<FDeleteAreaModelMasterResult>
    {
        TSharedPtr<Model::FAreaModelMaster> ItemValue;
        
    public:
        
        FDeleteAreaModelMasterResult();
        FDeleteAreaModelMasterResult(
            const FDeleteAreaModelMasterResult& From
        );
        ~FDeleteAreaModelMasterResult() = default;

        TSharedPtr<FDeleteAreaModelMasterResult> WithItem(const TSharedPtr<Model::FAreaModelMaster> Item);

        TSharedPtr<Model::FAreaModelMaster> GetItem() const;

        static TSharedPtr<FDeleteAreaModelMasterResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDeleteAreaModelMasterResult, ESPMode::ThreadSafe> FDeleteAreaModelMasterResultPtr;
}