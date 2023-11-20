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

#include "JobQueue/Model/Gs2JobQueue.h"
#include "JobQueue/Model/Gs2JobQueueNamespace.h"
#include "Core/BpGs2Constant.h"

FGs2JobQueue UGs2JobQueueFunctionLibrary::Service(
    FGs2Client Client,
    FBpJobQueuePushNotificationEvent PushNotification,
    FBpJobQueueRunNotificationEvent RunNotification
)
{
    FGs2JobQueue Return;
    if (Client.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2JobQueueFunctionLibrary::Service] Client parameter specification is missing."))
        return Return;
    }
    Client.Value->JobQueue->OnPushNotification().AddLambda([&PushNotification](auto Notification)
    {
        PushNotification.Value.Execute(EzPushNotificationToFGs2JobQueuePushNotification(Notification));
    });
    Client.Value->JobQueue->OnRunNotification().AddLambda([&RunNotification](auto Notification)
    {
        RunNotification.Value.Execute(EzRunNotificationToFGs2JobQueueRunNotification(Notification));
    });
    Return.Value = Client.Value->JobQueue;
    return Return;
}
FGs2JobQueueNamespace UGs2JobQueueFunctionLibrary::Namespace(
    FGs2JobQueue Service,
    FString NamespaceName
)
{
    FGs2JobQueueNamespace Return;
    if (Service.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2JobQueueFunctionLibrary::Namespace] Service parameter specification is missing."))
        return Return;
    }
    if (NamespaceName == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2JobQueueFunctionLibrary::Namespace] NamespaceName parameter specification is missing."))
        return Return;
    }
    Return.Value = Service.Value->Namespace(
        NamespaceName
    );
    return Return;
}