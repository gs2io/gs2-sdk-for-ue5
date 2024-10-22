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

#include "Mission/Model/Gs2MissionMissionGroupModel.h"
#include "Mission/Domain/EzGs2Mission.h"
#include "Mission/Model/Gs2MissionMissionTaskModel.h"
#include "Core/Model/Gs2AccessToken.h"
#include "Mission/Model/Gs2MissionMissionTaskModel.h"
#include "Core/BpGs2Constant.h"

FGs2MissionMissionTaskModel UGs2MissionMissionGroupModelFunctionLibrary::MissionTaskModel(
    FGs2MissionMissionGroupModel MissionGroupModel,
    FString MissionTaskName
)
{
    FGs2MissionMissionTaskModel Return;
    if (MissionGroupModel.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2MissionMissionGroupModelFunctionLibrary::MissionTaskModel] MissionGroupModel parameter specification is missing."))
        return Return;
    }
    if (MissionTaskName == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2MissionMissionGroupModelFunctionLibrary::MissionTaskModel] MissionTaskName parameter specification is missing."))
        return Return;
    }
    Return.Value = MissionGroupModel.Value->MissionTaskModel(
        MissionTaskName
    );
    return Return;
}