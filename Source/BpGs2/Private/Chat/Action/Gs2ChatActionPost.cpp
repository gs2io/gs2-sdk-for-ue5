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

#include "Chat/Action/Gs2ChatActionPost.h"
#include "Core/BpGs2Constant.h"

UGs2ChatPostAsyncFunction::UGs2ChatPostAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2ChatPostAsyncFunction* UGs2ChatPostAsyncFunction::Post(
    UObject* WorldContextObject,
    FGs2ChatOwnRoom Room,
    FString Metadata,
    int32 Category
)
{
    UGs2ChatPostAsyncFunction* Action = NewObject<UGs2ChatPostAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (Room.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2ChatPostAsyncFunction::Post] Room parameter specification is missing."))
        return Action;
    }
    Action->Room = Room;
    Action->Category = Category;
    Action->Metadata = Metadata;
    return Action;
}

void UGs2ChatPostAsyncFunction::Activate()
{
    if (Room.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2ChatPostAsyncFunction] Room parameter specification is missing."))
        return;
    }

    auto Future = Room.Value->Post(
        Metadata,
        Category
    );
    Future->GetTask().OnSuccessDelegate().BindLambda([&](auto Result)
    {
        FGs2ChatOwnMessage ReturnMessage;
        ReturnMessage.Value = Result;
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnMessage, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](auto Error)
    {
        FGs2ChatOwnMessage ReturnMessage;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnMessage, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}