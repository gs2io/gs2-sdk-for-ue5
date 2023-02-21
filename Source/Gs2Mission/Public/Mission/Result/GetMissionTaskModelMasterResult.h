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
#include "../Model/MissionTaskModelMaster.h"

namespace Gs2::Mission::Result
{
    class GS2MISSION_API FGetMissionTaskModelMasterResult final : public TSharedFromThis<FGetMissionTaskModelMasterResult>
    {
        TSharedPtr<Model::FMissionTaskModelMaster> ItemValue;
        
    public:
        
        FGetMissionTaskModelMasterResult();
        FGetMissionTaskModelMasterResult(
            const FGetMissionTaskModelMasterResult& From
        );
        ~FGetMissionTaskModelMasterResult() = default;

        TSharedPtr<FGetMissionTaskModelMasterResult> WithItem(const TSharedPtr<Model::FMissionTaskModelMaster> Item);

        TSharedPtr<Model::FMissionTaskModelMaster> GetItem() const;

        static TSharedPtr<FGetMissionTaskModelMasterResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetMissionTaskModelMasterResult, ESPMode::ThreadSafe> FGetMissionTaskModelMasterResultPtr;
}