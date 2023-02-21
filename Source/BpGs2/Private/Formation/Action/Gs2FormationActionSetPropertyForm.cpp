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

#include "Formation/Action/Gs2FormationActionSetPropertyForm.h"
#include "Core/BpGs2Constant.h"

UGs2FormationSetPropertyFormAsyncFunction::UGs2FormationSetPropertyFormAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2FormationSetPropertyFormAsyncFunction* UGs2FormationSetPropertyFormAsyncFunction::SetPropertyForm(
    UObject* WorldContextObject,
    FGs2FormationOwnPropertyForm PropertyForm,
    TArray<FGs2FormationSlotWithSignature> Slots,
    FString KeyId
)
{
    UGs2FormationSetPropertyFormAsyncFunction* Action = NewObject<UGs2FormationSetPropertyFormAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (PropertyForm.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2FormationSetPropertyFormAsyncFunction::SetPropertyForm] PropertyForm parameter specification is missing."))
        return Action;
    }
    Action->PropertyForm = PropertyForm;
    Action->Slots = Slots;
    Action->KeyId = KeyId;
    return Action;
}

void UGs2FormationSetPropertyFormAsyncFunction::Activate()
{
    if (PropertyForm.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2FormationSetPropertyFormAsyncFunction] PropertyForm parameter specification is missing."))
        return;
    }

    auto Future = PropertyForm.Value->SetPropertyForm(
        [&]
        {
            TArray<Gs2::UE5::Formation::Model::FEzSlotWithSignaturePtr> r;
            for (auto v : Slots)
            {
                r.Add(FGs2FormationSlotWithSignatureToEzSlotWithSignature(v));
            }
            return r;
        }(),
        KeyId
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