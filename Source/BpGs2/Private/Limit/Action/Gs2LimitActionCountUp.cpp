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

#include "Limit/Action/Gs2LimitActionCountUp.h"
#include "Core/BpGs2Constant.h"

UGs2LimitCountUpAsyncFunction::UGs2LimitCountUpAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2LimitCountUpAsyncFunction* UGs2LimitCountUpAsyncFunction::CountUp(
    UObject* WorldContextObject,
    FGs2LimitOwnCounter Counter,
    int32 CountUpValue,
    int32 MaxValue
)
{
    UGs2LimitCountUpAsyncFunction* Action = NewObject<UGs2LimitCountUpAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (Counter.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2LimitCountUpAsyncFunction::CountUp] Counter parameter specification is missing."))
        return Action;
    }
    Action->Counter = Counter;
    Action->CountUpValue = CountUpValue;
    Action->MaxValue = MaxValue;
    return Action;
}

void UGs2LimitCountUpAsyncFunction::Activate()
{
    if (Counter.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2LimitCountUpAsyncFunction] Counter parameter specification is missing."))
        return;
    }

    auto Future = Counter.Value->CountUp(
        CountUpValue,
        MaxValue
    );
    Future->GetTask().OnSuccessDelegate().BindLambda([&](auto Result)
    {
        FGs2LimitOwnCounter ReturnCounter;
        ReturnCounter.Value = Result;
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnCounter, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](auto Error)
    {
        FGs2LimitOwnCounter ReturnCounter;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnCounter, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}