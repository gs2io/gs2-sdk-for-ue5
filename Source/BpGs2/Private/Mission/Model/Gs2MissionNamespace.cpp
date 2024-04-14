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

#include "Mission/Model/Gs2MissionNamespace.h"
#include "Mission/Model/Gs2MissionMissionGroupModel.h"
#include "Mission/Model/Gs2MissionCounterModel.h"
#include "Core/Model/Gs2AccessToken.h"
#include "Mission/Model/Gs2MissionMissionGroupModel.h"
#include "Mission/Model/Gs2MissionUser.h"
#include "Mission/Model/Gs2MissionCounterModel.h"
#include "Core/BpGs2Constant.h"

FGs2MissionMissionGroupModel UGs2MissionNamespaceFunctionLibrary::MissionGroupModel(
    FGs2MissionNamespace Namespace,
    FString MissionGroupName
)
{
    FGs2MissionMissionGroupModel Return;
    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2MissionNamespaceFunctionLibrary::MissionGroupModel] Namespace parameter specification is missing."))
        return Return;
    }
    if (MissionGroupName == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2MissionNamespaceFunctionLibrary::MissionGroupModel] MissionGroupName parameter specification is missing."))
        return Return;
    }
    Return.Value = Namespace.Value->MissionGroupModel(
        MissionGroupName
    );
    return Return;
}

FGs2MissionOwnUser UGs2MissionNamespaceFunctionLibrary::Me(
    FGs2MissionNamespace Namespace,
    FGs2AccessToken AccessToken
)
{
    FGs2MissionOwnUser Return;
    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2MissionNamespaceFunctionLibrary::Me] Namespace parameter specification is missing."))
        return Return;
    }
    if (AccessToken.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2MissionNamespaceFunctionLibrary::Me] AccessToken parameter specification is missing."))
        return Return;
    }
    Return.Value = Namespace.Value->Me(AccessToken.Value);
    return Return;
}

FGs2MissionCounterModel UGs2MissionNamespaceFunctionLibrary::CounterModel(
    FGs2MissionNamespace Namespace,
    FString CounterName
)
{
    FGs2MissionCounterModel Return;
    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2MissionNamespaceFunctionLibrary::CounterModel] Namespace parameter specification is missing."))
        return Return;
    }
    if (CounterName == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2MissionNamespaceFunctionLibrary::CounterModel] CounterName parameter specification is missing."))
        return Return;
    }
    Return.Value = Namespace.Value->CounterModel(
        CounterName
    );
    return Return;
}