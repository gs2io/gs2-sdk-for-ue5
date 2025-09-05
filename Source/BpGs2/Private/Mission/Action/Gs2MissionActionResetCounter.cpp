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

#include "Mission/Action/Gs2MissionActionResetCounter.h"
#include "Core/BpGs2Constant.h"

UGs2MissionResetCounterAsyncFunction::UGs2MissionResetCounterAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2MissionResetCounterAsyncFunction* UGs2MissionResetCounterAsyncFunction::ResetCounter(
    UObject* WorldContextObject,
    FGs2MissionOwnCounter Counter,
    TArray<FGs2MissionScopedValue> Scopes
)
{
    UGs2MissionResetCounterAsyncFunction* Action = NewObject<UGs2MissionResetCounterAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (Counter.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2MissionResetCounterAsyncFunction::ResetCounter] Counter parameter specification is missing."))
        return Action;
    }
    Action->Counter = Counter;
    Action->Scopes = Scopes;
    return Action;
}

void UGs2MissionResetCounterAsyncFunction::Activate()
{
    if (Counter.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2MissionResetCounterAsyncFunction] Counter parameter specification is missing."))
        return;
    }

    auto Future = Counter.Value->ResetCounter(
        [&]
        {
            TArray<Gs2::UE5::Mission::Model::FEzScopedValuePtr> r;
            for (auto v : Scopes)
            {
                r.Add(FGs2MissionScopedValueToEzScopedValue(v));
            }
            return r;
        }()
    );
    Future->GetTask().OnSuccessDelegate().BindLambda([&](auto Result)
    {
        FGs2MissionOwnCounter ReturnCounter;
        ReturnCounter.Value = Result;
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnCounter, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](auto Error)
    {
        FGs2MissionOwnCounter ReturnCounter;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnCounter, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}