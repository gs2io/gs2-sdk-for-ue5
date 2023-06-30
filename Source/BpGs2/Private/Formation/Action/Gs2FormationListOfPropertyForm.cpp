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

#include "Formation/Action/Gs2FormationListOfPropertyForm.h"
#include "Formation/Model/Gs2FormationPropertyForm.h"
#include "Core/BpGs2Constant.h"

UGs2FormationListOfPropertyFormAsyncFunction::UGs2FormationListOfPropertyFormAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2FormationListOfPropertyFormAsyncFunction* UGs2FormationListOfPropertyFormAsyncFunction::ListOfPropertyForm(
    UObject* WorldContextObject,
    FGs2FormationOwnUser User,
    FString FormModelName
)
{
    UGs2FormationListOfPropertyFormAsyncFunction* Action = NewObject<UGs2FormationListOfPropertyFormAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2FormationListOfPropertyFormAsyncFunction::ListOfPropertyForm] User parameter specification is missing."))
        return Action;
    }
    Action->User = User;
    Action->FormModelName = FormModelName;
    return Action;
}

void UGs2FormationListOfPropertyFormAsyncFunction::Activate()
{
    TArray<FGs2FormationPropertyFormValue> ReturnPropertyForms;
    FGs2Error ReturnError;

    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2FormationListOfPropertyFormAsyncFunction::Activate] User parameter specification is missing."))
        return;
    }
    const auto It = User.Value->PropertyForms(
        FormModelName
    );
    for (auto v : *It)
    {
        ReturnPropertyForms.Add(EzPropertyFormToFGs2FormationPropertyFormValue(v->Current()));
    }
    OnSuccess.Broadcast(ReturnPropertyForms, ReturnError);
}