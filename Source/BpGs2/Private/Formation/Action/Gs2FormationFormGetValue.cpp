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

#include "Formation/Action/Gs2FormationFormGetValue.h"
#include "Core/BpGs2Constant.h"

UGs2FormationFormGetValueAsyncFunction::UGs2FormationFormGetValueAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2FormationFormGetValueAsyncFunction* UGs2FormationFormGetValueAsyncFunction::FormGetValue(
    UObject* WorldContextObject,
    FGs2FormationOwnForm Form
)
{
    UGs2FormationFormGetValueAsyncFunction* Action = NewObject<UGs2FormationFormGetValueAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (Form.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2FormationFormGetValueAsyncFunction::FormGetValue] Form parameter specification is missing."))
        return Action;
    }
    Action->Form = Form;
    return Action;
}

void UGs2FormationFormGetValueAsyncFunction::Activate()
{
    auto Future = Form.Value->Model();
    Future->GetTask().OnSuccessDelegate().BindLambda([&](const auto Result)
    {
        auto ReturnValue = EzFormToFGs2FormationFormValue(Result);
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnValue, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](const auto Error)
    {
        FGs2FormationFormValue ReturnForm;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnForm, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}