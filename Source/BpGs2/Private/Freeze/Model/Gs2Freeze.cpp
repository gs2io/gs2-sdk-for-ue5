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

#include "Freeze/Model/Gs2Freeze.h"
#include "Freeze/Domain/EzGs2Freeze.h"
#include "Freeze/Model/Gs2FreezeStage.h"
#include "Core/BpGs2Constant.h"

FGs2Freeze UGs2FreezeFunctionLibrary::Service(
    FGs2Client Client
)
{
    FGs2Freeze Return;
    if (Client.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2FreezeFunctionLibrary::Service] Client parameter specification is missing."))
        return Return;
    }
    Return.Value = Client.Value->Freeze;
    return Return;
}
FGs2FreezeStage UGs2FreezeFunctionLibrary::Stage(
    FGs2Freeze Service,
    FString StageName
)
{
    FGs2FreezeStage Return;
    if (Service.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2FreezeFunctionLibrary::Stage] Service parameter specification is missing."))
        return Return;
    }
    if (StageName == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2FreezeFunctionLibrary::Stage] StageName parameter specification is missing."))
        return Return;
    }
    Return.Value = Service.Value->Stage(
        StageName
    );
    return Return;
}