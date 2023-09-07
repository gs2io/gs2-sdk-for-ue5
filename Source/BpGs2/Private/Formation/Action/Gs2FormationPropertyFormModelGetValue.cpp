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

#include "Formation/Action/Gs2FormationPropertyFormModelGetValue.h"
#include "Core/BpGs2Constant.h"

UGs2FormationPropertyFormModelGetValueAsyncFunction::UGs2FormationPropertyFormModelGetValueAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2FormationPropertyFormModelGetValueAsyncFunction* UGs2FormationPropertyFormModelGetValueAsyncFunction::PropertyFormModelGetValue(
    UObject* WorldContextObject,
    FGs2FormationPropertyFormModel PropertyFormModel
)
{
    UGs2FormationPropertyFormModelGetValueAsyncFunction* Action = NewObject<UGs2FormationPropertyFormModelGetValueAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (PropertyFormModel.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2FormationPropertyFormModelGetValueAsyncFunction::PropertyFormModelGetValue] PropertyFormModel parameter specification is missing."))
        return Action;
    }
    Action->PropertyFormModel = PropertyFormModel;
    return Action;
}

void UGs2FormationPropertyFormModelGetValueAsyncFunction::Activate()
{
    auto Future = PropertyFormModel.Value->Model(
    );
    Future->GetTask().OnSuccessDelegate().BindLambda([&](const auto Result)
    {
        auto ReturnValue = EzPropertyFormModelToFGs2FormationPropertyFormModelValue(Result);
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnValue, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](const auto Error)
    {
        FGs2FormationPropertyFormModelValue ReturnPropertyFormModel;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnPropertyFormModel, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}