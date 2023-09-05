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
#include "../Model/Mold.h"
#include "../Model/MoldModel.h"

namespace Gs2::Formation::Result
{
    class GS2FORMATION_API FSubMoldCapacityByUserIdResult final : public TSharedFromThis<FSubMoldCapacityByUserIdResult>
    {
        TSharedPtr<Model::FMold> ItemValue;
        TSharedPtr<Model::FMoldModel> MoldModelValue;
        
    public:
        
        FSubMoldCapacityByUserIdResult();
        FSubMoldCapacityByUserIdResult(
            const FSubMoldCapacityByUserIdResult& From
        );
        ~FSubMoldCapacityByUserIdResult() = default;

        TSharedPtr<FSubMoldCapacityByUserIdResult> WithItem(const TSharedPtr<Model::FMold> Item);
        TSharedPtr<FSubMoldCapacityByUserIdResult> WithMoldModel(const TSharedPtr<Model::FMoldModel> MoldModel);

        TSharedPtr<Model::FMold> GetItem() const;
        TSharedPtr<Model::FMoldModel> GetMoldModel() const;

        static TSharedPtr<FSubMoldCapacityByUserIdResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FSubMoldCapacityByUserIdResult, ESPMode::ThreadSafe> FSubMoldCapacityByUserIdResultPtr;
}