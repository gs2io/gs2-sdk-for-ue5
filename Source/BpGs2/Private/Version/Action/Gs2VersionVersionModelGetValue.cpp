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

#include "Version/Action/Gs2VersionVersionModelGetValue.h"
#include "Core/BpGs2Constant.h"

UGs2VersionVersionModelGetValueAsyncFunction::UGs2VersionVersionModelGetValueAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2VersionVersionModelGetValueAsyncFunction* UGs2VersionVersionModelGetValueAsyncFunction::VersionModelGetValue(
    UObject* WorldContextObject,
    FGs2VersionVersionModel VersionModel
)
{
    UGs2VersionVersionModelGetValueAsyncFunction* Action = NewObject<UGs2VersionVersionModelGetValueAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (VersionModel.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2VersionVersionModelGetValueAsyncFunction::VersionModelGetValue] VersionModel parameter specification is missing."))
        return Action;
    }
    Action->VersionModel = VersionModel;
    return Action;
}

void UGs2VersionVersionModelGetValueAsyncFunction::Activate()
{
    auto Future = VersionModel.Value->Model(
    );
    Future->GetTask().OnSuccessDelegate().BindLambda([&](const auto Result)
    {
        auto ReturnValue = EzVersionModelToFGs2VersionVersionModelValue(Result);
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnValue, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](const auto Error)
    {
        FGs2VersionVersionModelValue ReturnVersionModel;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnVersionModel, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}