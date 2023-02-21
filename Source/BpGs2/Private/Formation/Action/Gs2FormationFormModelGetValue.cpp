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

#include "Formation/Action/Gs2FormationFormModelGetValue.h"
#include "Core/BpGs2Constant.h"

UGs2FormationFormModelGetValueAsyncFunction::UGs2FormationFormModelGetValueAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2FormationFormModelGetValueAsyncFunction* UGs2FormationFormModelGetValueAsyncFunction::FormModelGetValue(
    UObject* WorldContextObject,
    FGs2FormationFormModel FormModel
)
{
    UGs2FormationFormModelGetValueAsyncFunction* Action = NewObject<UGs2FormationFormModelGetValueAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (FormModel.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2FormationFormModelGetValueAsyncFunction::FormModelGetValue] FormModel parameter specification is missing."))
        return Action;
    }
    Action->FormModel = FormModel;
    return Action;
}

void UGs2FormationFormModelGetValueAsyncFunction::Activate()
{
    auto Future = FormModel.Value->Model(
    );
    Future->GetTask().OnSuccessDelegate().BindLambda([&](const auto Result)
    {
        auto ReturnValue = EzFormModelToFGs2FormationFormModelValue(Result);
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnValue, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](const auto Error)
    {
        FGs2FormationFormModelValue ReturnFormModel;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnFormModel, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}