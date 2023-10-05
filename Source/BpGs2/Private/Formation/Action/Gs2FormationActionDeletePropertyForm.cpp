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

#include "Formation/Action/Gs2FormationActionDeletePropertyForm.h"
#include "Core/BpGs2Constant.h"

UGs2FormationDeletePropertyFormAsyncFunction::UGs2FormationDeletePropertyFormAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2FormationDeletePropertyFormAsyncFunction* UGs2FormationDeletePropertyFormAsyncFunction::DeletePropertyForm(
    UObject* WorldContextObject,
    FGs2FormationOwnPropertyForm PropertyForm
)
{
    UGs2FormationDeletePropertyFormAsyncFunction* Action = NewObject<UGs2FormationDeletePropertyFormAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (PropertyForm.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2FormationDeletePropertyFormAsyncFunction::DeletePropertyForm] PropertyForm parameter specification is missing."))
        return Action;
    }
    Action->PropertyForm = PropertyForm;
    return Action;
}

void UGs2FormationDeletePropertyFormAsyncFunction::Activate()
{
    if (PropertyForm.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2FormationDeletePropertyFormAsyncFunction] PropertyForm parameter specification is missing."))
        return;
    }

    auto Future = PropertyForm.Value->DeletePropertyForm(
    );
    Future->GetTask().OnSuccessDelegate().BindLambda([&](auto Result)
    {
        FGs2FormationOwnPropertyForm ReturnPropertyForm;
        ReturnPropertyForm.Value = Result;
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnPropertyForm, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](auto Error)
    {
        FGs2FormationOwnPropertyForm ReturnPropertyForm;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnPropertyForm, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}