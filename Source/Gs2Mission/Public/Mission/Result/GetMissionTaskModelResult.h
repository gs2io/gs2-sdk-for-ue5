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
#include "../Model/MissionTaskModel.h"

namespace Gs2::Mission::Result
{
    class GS2MISSION_API FGetMissionTaskModelResult final : public TSharedFromThis<FGetMissionTaskModelResult>
    {
        TSharedPtr<Model::FMissionTaskModel> ItemValue;
        
    public:
        
        FGetMissionTaskModelResult();
        FGetMissionTaskModelResult(
            const FGetMissionTaskModelResult& From
        );
        ~FGetMissionTaskModelResult() = default;

        TSharedPtr<FGetMissionTaskModelResult> WithItem(const TSharedPtr<Model::FMissionTaskModel> Item);

        TSharedPtr<Model::FMissionTaskModel> GetItem() const;

        static TSharedPtr<FGetMissionTaskModelResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetMissionTaskModelResult, ESPMode::ThreadSafe> FGetMissionTaskModelResultPtr;
}