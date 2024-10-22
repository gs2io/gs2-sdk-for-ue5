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

#include "Realtime/Model/Gs2RealtimeNamespace.h"
#include "Realtime/Domain/EzGs2Realtime.h"
#include "Realtime/Model/Gs2RealtimeRoom.h"
#include "Core/Model/Gs2AccessToken.h"
#include "Realtime/Model/Gs2RealtimeRoom.h"
#include "Core/BpGs2Constant.h"

FGs2RealtimeRoom UGs2RealtimeNamespaceFunctionLibrary::Room(
    FGs2RealtimeNamespace Namespace,
    FString RoomName
)
{
    FGs2RealtimeRoom Return;
    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2RealtimeNamespaceFunctionLibrary::Room] Namespace parameter specification is missing."))
        return Return;
    }
    if (RoomName == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2RealtimeNamespaceFunctionLibrary::Room] RoomName parameter specification is missing."))
        return Return;
    }
    Return.Value = Namespace.Value->Room(
        RoomName
    );
    return Return;
}