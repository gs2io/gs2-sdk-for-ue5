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

#include "Formation/Action/Gs2FormationMoldGetValue.h"
#include "Core/BpGs2Constant.h"

UGs2FormationMoldGetValueAsyncFunction::UGs2FormationMoldGetValueAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2FormationMoldGetValueAsyncFunction* UGs2FormationMoldGetValueAsyncFunction::MoldGetValue(
    UObject* WorldContextObject,
    FGs2FormationOwnMold Mold
)
{
    UGs2FormationMoldGetValueAsyncFunction* Action = NewObject<UGs2FormationMoldGetValueAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (Mold.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2FormationMoldGetValueAsyncFunction::MoldGetValue] Mold parameter specification is missing."))
        return Action;
    }
    Action->Mold = Mold;
    return Action;
}

void UGs2FormationMoldGetValueAsyncFunction::Activate()
{
    auto Future = Mold.Value->Model();
    Future->GetTask().OnSuccessDelegate().BindLambda([&](const auto Result)
    {
        auto ReturnValue = EzMoldToFGs2FormationMoldValue(Result);
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnValue, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](const auto Error)
    {
        FGs2FormationMoldValue ReturnMold;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnMold, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}