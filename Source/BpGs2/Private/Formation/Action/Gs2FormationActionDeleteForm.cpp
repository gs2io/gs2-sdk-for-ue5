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

#include "Formation/Action/Gs2FormationActionDeleteForm.h"
#include "Core/BpGs2Constant.h"

UGs2FormationDeleteFormAsyncFunction::UGs2FormationDeleteFormAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2FormationDeleteFormAsyncFunction* UGs2FormationDeleteFormAsyncFunction::DeleteForm(
    UObject* WorldContextObject,
    FGs2FormationOwnForm Form
)
{
    UGs2FormationDeleteFormAsyncFunction* Action = NewObject<UGs2FormationDeleteFormAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (Form.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2FormationDeleteFormAsyncFunction::DeleteForm] Form parameter specification is missing."))
        return Action;
    }
    Action->Form = Form;
    return Action;
}

void UGs2FormationDeleteFormAsyncFunction::Activate()
{
    if (Form.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2FormationDeleteFormAsyncFunction] Form parameter specification is missing."))
        return;
    }

    auto Future = Form.Value->DeleteForm(
    );
    Future->GetTask().OnSuccessDelegate().BindLambda([&](auto Result)
    {
        FGs2FormationOwnForm ReturnForm;
        ReturnForm.Value = Result;
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnForm, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](auto Error)
    {
        FGs2FormationOwnForm ReturnForm;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnForm, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}