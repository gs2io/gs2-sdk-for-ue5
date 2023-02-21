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

#include "Chat/Action/Gs2ChatActionDeleteRoom.h"
#include "Core/BpGs2Constant.h"

UGs2ChatDeleteRoomAsyncFunction::UGs2ChatDeleteRoomAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2ChatDeleteRoomAsyncFunction* UGs2ChatDeleteRoomAsyncFunction::DeleteRoom(
    UObject* WorldContextObject,
    FGs2ChatOwnRoom Room
)
{
    UGs2ChatDeleteRoomAsyncFunction* Action = NewObject<UGs2ChatDeleteRoomAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (Room.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2ChatDeleteRoomAsyncFunction::DeleteRoom] Room parameter specification is missing."))
        return Action;
    }
    Action->Room = Room;
    return Action;
}

void UGs2ChatDeleteRoomAsyncFunction::Activate()
{
    if (Room.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2ChatDeleteRoomAsyncFunction] Room parameter specification is missing."))
        return;
    }

    auto Future = Room.Value->DeleteRoom(
    );
    Future->GetTask().OnSuccessDelegate().BindLambda([&](auto Result)
    {
        FGs2ChatOwnRoom ReturnRoom;
        ReturnRoom.Value = Result;
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnRoom, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](auto Error)
    {
        FGs2ChatOwnRoom ReturnRoom;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnRoom, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}