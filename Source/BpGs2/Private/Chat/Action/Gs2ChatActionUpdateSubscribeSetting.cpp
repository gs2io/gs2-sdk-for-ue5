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

#include "Chat/Action/Gs2ChatActionUpdateSubscribeSetting.h"
#include "Core/BpGs2Constant.h"

UGs2ChatUpdateSubscribeSettingAsyncFunction::UGs2ChatUpdateSubscribeSettingAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2ChatUpdateSubscribeSettingAsyncFunction* UGs2ChatUpdateSubscribeSettingAsyncFunction::UpdateSubscribeSetting(
    UObject* WorldContextObject,
    FGs2ChatOwnSubscribe Subscribe,
    TArray<FGs2ChatNotificationType> NotificationTypes
)
{
    UGs2ChatUpdateSubscribeSettingAsyncFunction* Action = NewObject<UGs2ChatUpdateSubscribeSettingAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (Subscribe.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2ChatUpdateSubscribeSettingAsyncFunction::UpdateSubscribeSetting] Subscribe parameter specification is missing."))
        return Action;
    }
    Action->Subscribe = Subscribe;
    Action->NotificationTypes = NotificationTypes;
    return Action;
}

void UGs2ChatUpdateSubscribeSettingAsyncFunction::Activate()
{
    if (Subscribe.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2ChatUpdateSubscribeSettingAsyncFunction] Subscribe parameter specification is missing."))
        return;
    }

    auto Future = Subscribe.Value->UpdateSubscribeSetting(
        [&]
        {
            TArray<Gs2::UE5::Chat::Model::FEzNotificationTypePtr> r;
            for (auto v : NotificationTypes)
            {
                r.Add(FGs2ChatNotificationTypeToEzNotificationType(v));
            }
            return r;
        }()
    );
    Future->GetTask().OnSuccessDelegate().BindLambda([&](auto Result)
    {
        FGs2ChatOwnSubscribe ReturnSubscribe;
        ReturnSubscribe.Value = Result;
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnSubscribe, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](auto Error)
    {
        FGs2ChatOwnSubscribe ReturnSubscribe;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnSubscribe, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}