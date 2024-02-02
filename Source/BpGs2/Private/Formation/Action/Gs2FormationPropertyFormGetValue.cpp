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

#include "Formation/Action/Gs2FormationPropertyFormGetValue.h"
#include "Core/BpGs2Constant.h"

UGs2FormationPropertyFormGetValueAsyncFunction::UGs2FormationPropertyFormGetValueAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2FormationPropertyFormGetValueAsyncFunction* UGs2FormationPropertyFormGetValueAsyncFunction::PropertyFormGetValue(
    UObject* WorldContextObject,
    FGs2FormationOwnPropertyForm PropertyForm
)
{
    UGs2FormationPropertyFormGetValueAsyncFunction* Action = NewObject<UGs2FormationPropertyFormGetValueAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (PropertyForm.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2FormationPropertyFormGetValueAsyncFunction::PropertyFormGetValue] PropertyForm parameter specification is missing."))
        return Action;
    }
    Action->PropertyForm = PropertyForm;
    return Action;
}

void UGs2FormationPropertyFormGetValueAsyncFunction::Activate()
{
    auto Future = PropertyForm.Value->Model();
    Future->GetTask().OnSuccessDelegate().BindLambda([&](const auto Result)
    {
        auto ReturnValue = EzPropertyFormToFGs2FormationPropertyFormValue(Result);
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnValue, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](const auto Error)
    {
        FGs2FormationPropertyFormValue ReturnPropertyForm;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnPropertyForm, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}