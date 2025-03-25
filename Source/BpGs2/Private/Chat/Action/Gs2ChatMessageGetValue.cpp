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

#include "Chat/Action/Gs2ChatMessageGetValue.h"
#include "Core/BpGs2Constant.h"

UGs2ChatMessageGetValueAsyncFunction::UGs2ChatMessageGetValueAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2ChatMessageGetValueAsyncFunction* UGs2ChatMessageGetValueAsyncFunction::MessageGetValue(
    UObject* WorldContextObject,
    FGs2ChatOwnMessage Message
)
{
    UGs2ChatMessageGetValueAsyncFunction* Action = NewObject<UGs2ChatMessageGetValueAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (Message.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2ChatMessageGetValueAsyncFunction::MessageGetValue] Message parameter specification is missing."))
        return Action;
    }
    Action->Message = Message;
    return Action;
}

void UGs2ChatMessageGetValueAsyncFunction::Activate()
{
    auto Future = Message.Value->Model();
    Future->GetTask().OnSuccessDelegate().BindLambda([&](const auto Result)
    {
        auto ReturnValue = EzMessageToFGs2ChatMessageValue(Result);
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnValue, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](const auto Error)
    {
        FGs2ChatMessageValue ReturnMessage;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnMessage, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}