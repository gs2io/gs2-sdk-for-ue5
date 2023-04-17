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

#include "SerialKey/Action/Gs2SerialKeyActionUseSerialCode.h"
#include "Core/BpGs2Constant.h"

UGs2SerialKeyUseSerialCodeAsyncFunction::UGs2SerialKeyUseSerialCodeAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2SerialKeyUseSerialCodeAsyncFunction* UGs2SerialKeyUseSerialCodeAsyncFunction::UseSerialCode(
    UObject* WorldContextObject,
    FGs2SerialKeyOwnSerialKey SerialKey,
    FString Code
)
{
    UGs2SerialKeyUseSerialCodeAsyncFunction* Action = NewObject<UGs2SerialKeyUseSerialCodeAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (SerialKey.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2SerialKeyUseSerialCodeAsyncFunction::UseSerialCode] SerialKey parameter specification is missing."))
        return Action;
    }
    Action->SerialKey = SerialKey;
    Action->Code = Code;
    return Action;
}

void UGs2SerialKeyUseSerialCodeAsyncFunction::Activate()
{
    if (SerialKey.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2SerialKeyUseSerialCodeAsyncFunction] SerialKey parameter specification is missing."))
        return;
    }

    auto Future = SerialKey.Value->UseSerialCode(
        Code
    );
    Future->GetTask().OnSuccessDelegate().BindLambda([&](auto Result)
    {
        FGs2SerialKeyOwnSerialKey ReturnSerialKey;
        ReturnSerialKey.Value = Result;
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnSerialKey, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](auto Error)
    {
        FGs2SerialKeyOwnSerialKey ReturnSerialKey;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnSerialKey, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}