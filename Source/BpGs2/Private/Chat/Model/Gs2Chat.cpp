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

#include "Chat/Model/Gs2Chat.h"
#include "Chat/Domain/EzGs2Chat.h"
#include "Chat/Model/Gs2ChatNamespace.h"
#include "Core/BpGs2Constant.h"

FGs2Chat UGs2ChatFunctionLibrary::Service(
    FGs2Client Client,
    FBpChatPostNotificationEvent PostNotification
)
{
    FGs2Chat Return;
    if (Client.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2ChatFunctionLibrary::Service] Client parameter specification is missing."))
        return Return;
    }
    Client.Value->Chat->OnPostNotification().AddLambda([&PostNotification](auto Notification)
    {
        PostNotification.Value.Execute(EzPostNotificationToFGs2ChatPostNotification(Notification));
    });
    Return.Value = Client.Value->Chat;
    return Return;
}
FGs2ChatNamespace UGs2ChatFunctionLibrary::Namespace(
    FGs2Chat Service,
    FString NamespaceName
)
{
    FGs2ChatNamespace Return;
    if (Service.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2ChatFunctionLibrary::Namespace] Service parameter specification is missing."))
        return Return;
    }
    if (NamespaceName == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2ChatFunctionLibrary::Namespace] NamespaceName parameter specification is missing."))
        return Return;
    }
    Return.Value = Service.Value->Namespace(
        NamespaceName
    );
    return Return;
}