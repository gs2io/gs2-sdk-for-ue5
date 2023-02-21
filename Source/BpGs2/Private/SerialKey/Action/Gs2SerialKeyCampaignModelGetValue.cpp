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

#include "SerialKey/Action/Gs2SerialKeyCampaignModelGetValue.h"
#include "Core/BpGs2Constant.h"

UGs2SerialKeyCampaignModelGetValueAsyncFunction::UGs2SerialKeyCampaignModelGetValueAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2SerialKeyCampaignModelGetValueAsyncFunction* UGs2SerialKeyCampaignModelGetValueAsyncFunction::CampaignModelGetValue(
    UObject* WorldContextObject,
    FGs2SerialKeyCampaignModel CampaignModel
)
{
    UGs2SerialKeyCampaignModelGetValueAsyncFunction* Action = NewObject<UGs2SerialKeyCampaignModelGetValueAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (CampaignModel.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2SerialKeyCampaignModelGetValueAsyncFunction::CampaignModelGetValue] CampaignModel parameter specification is missing."))
        return Action;
    }
    Action->CampaignModel = CampaignModel;
    return Action;
}

void UGs2SerialKeyCampaignModelGetValueAsyncFunction::Activate()
{
    auto Future = CampaignModel.Value->Model(
    );
    Future->GetTask().OnSuccessDelegate().BindLambda([&](const auto Result)
    {
        auto ReturnValue = EzCampaignModelToFGs2SerialKeyCampaignModelValue(Result);
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnValue, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](const auto Error)
    {
        FGs2SerialKeyCampaignModelValue ReturnCampaignModel;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnCampaignModel, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}