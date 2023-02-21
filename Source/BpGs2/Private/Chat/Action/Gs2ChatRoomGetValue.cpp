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

#include "Chat/Action/Gs2ChatRoomGetValue.h"
#include "Core/BpGs2Constant.h"

UGs2ChatRoomGetValueAsyncFunction::UGs2ChatRoomGetValueAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2ChatRoomGetValueAsyncFunction* UGs2ChatRoomGetValueAsyncFunction::RoomGetValue(
    UObject* WorldContextObject,
    FGs2ChatRoom Room
)
{
    UGs2ChatRoomGetValueAsyncFunction* Action = NewObject<UGs2ChatRoomGetValueAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (Room.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2ChatRoomGetValueAsyncFunction::RoomGetValue] Room parameter specification is missing."))
        return Action;
    }
    Action->Room = Room;
    return Action;
}

void UGs2ChatRoomGetValueAsyncFunction::Activate()
{
    auto Future = Room.Value->Model(
    );
    Future->GetTask().OnSuccessDelegate().BindLambda([&](const auto Result)
    {
        auto ReturnValue = EzRoomToFGs2ChatRoomValue(Result);
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnValue, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](const auto Error)
    {
        FGs2ChatRoomValue ReturnRoom;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnRoom, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}