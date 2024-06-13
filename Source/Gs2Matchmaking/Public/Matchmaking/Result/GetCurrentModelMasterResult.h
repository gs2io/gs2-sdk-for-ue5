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
#include "../Model/CurrentModelMaster.h"

namespace Gs2::Matchmaking::Result
{
    class GS2MATCHMAKING_API FGetCurrentModelMasterResult final : public TSharedFromThis<FGetCurrentModelMasterResult>
    {
        TSharedPtr<Model::FCurrentModelMaster> ItemValue;
        
    public:
        
        FGetCurrentModelMasterResult();
        FGetCurrentModelMasterResult(
            const FGetCurrentModelMasterResult& From
        );
        ~FGetCurrentModelMasterResult() = default;

        TSharedPtr<FGetCurrentModelMasterResult> WithItem(const TSharedPtr<Model::FCurrentModelMaster> Item);

        TSharedPtr<Model::FCurrentModelMaster> GetItem() const;

        static TSharedPtr<FGetCurrentModelMasterResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetCurrentModelMasterResult, ESPMode::ThreadSafe> FGetCurrentModelMasterResultPtr;
}