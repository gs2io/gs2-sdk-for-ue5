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

#include "Mission/Model/Gs2MissionUser.h"
#include "Mission/Model/Gs2MissionCounter.h"
#include "Mission/Model/Gs2MissionComplete.h"
#include "Core/Model/Gs2AccessToken.h"
#include "Mission/Model/Gs2MissionCounter.h"
#include "Mission/Model/Gs2MissionComplete.h"
#include "Core/BpGs2Constant.h"

FGs2MissionOwnCounter UGs2MissionUserFunctionLibrary::OwnCounter(
    FGs2MissionOwnUser User,
    FString CounterName
)
{
    FGs2MissionOwnCounter Return;
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2MissionUserFunctionLibrary::OwnCounter] User parameter specification is missing."))
        return Return;
    }
    if (CounterName == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2MissionUserFunctionLibrary::OwnCounter] CounterName parameter specification is missing."))
        return Return;
    }
    Return.Value = User.Value->Counter(
        CounterName
    );
    return Return;
}

FGs2MissionOwnComplete UGs2MissionUserFunctionLibrary::OwnComplete(
    FGs2MissionOwnUser User,
    FString MissionGroupName
)
{
    FGs2MissionOwnComplete Return;
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2MissionUserFunctionLibrary::OwnComplete] User parameter specification is missing."))
        return Return;
    }
    if (MissionGroupName == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2MissionUserFunctionLibrary::OwnComplete] MissionGroupName parameter specification is missing."))
        return Return;
    }
    Return.Value = User.Value->Complete(
        MissionGroupName
    );
    return Return;
}