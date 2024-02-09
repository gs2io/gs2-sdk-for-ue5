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

#include "SerialKey/Action/Gs2SerialKeySerialKeyGetValue.h"
#include "Core/BpGs2Constant.h"

UGs2SerialKeySerialKeyGetValueAsyncFunction::UGs2SerialKeySerialKeyGetValueAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2SerialKeySerialKeyGetValueAsyncFunction* UGs2SerialKeySerialKeyGetValueAsyncFunction::SerialKeyGetValue(
    UObject* WorldContextObject,
    FGs2SerialKeySerialKey SerialKey
)
{
    UGs2SerialKeySerialKeyGetValueAsyncFunction* Action = NewObject<UGs2SerialKeySerialKeyGetValueAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (SerialKey.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2SerialKeySerialKeyGetValueAsyncFunction::SerialKeyGetValue] SerialKey parameter specification is missing."))
        return Action;
    }
    Action->SerialKey = SerialKey;
    return Action;
}

void UGs2SerialKeySerialKeyGetValueAsyncFunction::Activate()
{
    auto Future = SerialKey.Value->Model();
    Future->GetTask().OnSuccessDelegate().BindLambda([&](const auto Result)
    {
        auto ReturnValue = EzSerialKeyToFGs2SerialKeySerialKeyValue(Result);
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnValue, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](const auto Error)
    {
        FGs2SerialKeySerialKeyValue ReturnSerialKey;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnSerialKey, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}