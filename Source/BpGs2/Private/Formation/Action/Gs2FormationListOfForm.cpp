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

#include "Formation/Action/Gs2FormationListOfForm.h"
#include "Formation/Model/Gs2FormationForm.h"
#include "Core/BpGs2Constant.h"

UGs2FormationListOfFormAsyncFunction::UGs2FormationListOfFormAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2FormationListOfFormAsyncFunction* UGs2FormationListOfFormAsyncFunction::ListOfForm(
    UObject* WorldContextObject,
    FGs2FormationOwnMold Mold
)
{
    UGs2FormationListOfFormAsyncFunction* Action = NewObject<UGs2FormationListOfFormAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (Mold.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2FormationListOfFormAsyncFunction::ListOfForm] Mold parameter specification is missing."))
        return Action;
    }
    Action->Mold = Mold;
    return Action;
}

void UGs2FormationListOfFormAsyncFunction::Activate()
{
    TArray<FGs2FormationFormValue> ReturnForms;
    FGs2Error ReturnError;
    const auto It = Mold.Value->Forms(
    );
    for (auto v : *It)
    {
        ReturnForms.Add(EzFormToFGs2FormationFormValue(v->Current()));
    }
    OnSuccess.Broadcast(ReturnForms, ReturnError);
}