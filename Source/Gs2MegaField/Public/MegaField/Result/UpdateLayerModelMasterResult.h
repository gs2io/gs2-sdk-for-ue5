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
#include "../Model/LayerModelMaster.h"

namespace Gs2::MegaField::Result
{
    class GS2MEGAFIELD_API FUpdateLayerModelMasterResult final : public TSharedFromThis<FUpdateLayerModelMasterResult>
    {
        TSharedPtr<Model::FLayerModelMaster> ItemValue;
        
    public:
        
        FUpdateLayerModelMasterResult();
        FUpdateLayerModelMasterResult(
            const FUpdateLayerModelMasterResult& From
        );
        ~FUpdateLayerModelMasterResult() = default;

        TSharedPtr<FUpdateLayerModelMasterResult> WithItem(const TSharedPtr<Model::FLayerModelMaster> Item);

        TSharedPtr<Model::FLayerModelMaster> GetItem() const;

        static TSharedPtr<FUpdateLayerModelMasterResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUpdateLayerModelMasterResult, ESPMode::ThreadSafe> FUpdateLayerModelMasterResultPtr;
}