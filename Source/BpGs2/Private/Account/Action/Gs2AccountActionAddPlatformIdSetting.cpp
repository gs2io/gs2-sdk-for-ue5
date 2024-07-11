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
 *
 * deny overwrite
 */

#include "Account/Action/Gs2AccountActionAddPlatformIdSetting.h"
#include "Core/BpGs2Constant.h"

UGs2AccountAddPlatformIdSettingAsyncFunction::UGs2AccountAddPlatformIdSettingAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2AccountAddPlatformIdSettingAsyncFunction* UGs2AccountAddPlatformIdSettingAsyncFunction::AddPlatformIdSetting(
    UObject* WorldContextObject,
    FGs2AccountOwnPlatformId PlatformId
)
{
    UGs2AccountAddPlatformIdSettingAsyncFunction* Action = NewObject<UGs2AccountAddPlatformIdSettingAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (PlatformId.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2AccountAddPlatformIdSettingAsyncFunction::AddPlatformIdSetting] PlatformId parameter specification is missing."))
        return Action;
    }
    Action->PlatformId = PlatformId;
    return Action;
}

void UGs2AccountAddPlatformIdSettingAsyncFunction::Activate()
{
    if (PlatformId.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2AccountAddPlatformIdSettingAsyncFunction] PlatformId parameter specification is missing."))
        return;
    }

    auto Future = PlatformId.Value->AddPlatformIdSetting(
    );
    Future->GetTask().OnSuccessDelegate().BindLambda([&](auto Result)
    {
        FGs2AccountOwnPlatformId ReturnPlatformId;
        ReturnPlatformId.Value = Result;
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnPlatformId, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](auto Error)
    {
        FGs2AccountOwnPlatformId ReturnPlatformId;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnPlatformId, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}