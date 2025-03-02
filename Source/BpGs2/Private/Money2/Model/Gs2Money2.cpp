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

#include "Money2/Model/Gs2Money2.h"
#include "Money2/Domain/EzGs2Money2.h"
#include "Money2/Model/Gs2Money2Namespace.h"
#include "Core/BpGs2Constant.h"

FGs2Money2 UGs2Money2FunctionLibrary::Service(
    FGs2Client Client,
    FBpMoney2ChangeSubscriptionStatusNotificationEvent ChangeSubscriptionStatusNotification
)
{
    FGs2Money2 Return;
    if (Client.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2Money2FunctionLibrary::Service] Client parameter specification is missing."))
        return Return;
    }
    Client.Value->Money2->OnChangeSubscriptionStatusNotification().AddLambda([&ChangeSubscriptionStatusNotification](auto Notification)
    {
        ChangeSubscriptionStatusNotification.Value.Execute(EzChangeSubscriptionStatusNotificationToFGs2Money2ChangeSubscriptionStatusNotification(Notification));
    });
    Return.Value = Client.Value->Money2;
    return Return;
}
FGs2Money2Namespace UGs2Money2FunctionLibrary::Namespace(
    FGs2Money2 Service,
    FString NamespaceName
)
{
    FGs2Money2Namespace Return;
    if (Service.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2Money2FunctionLibrary::Namespace] Service parameter specification is missing."))
        return Return;
    }
    if (NamespaceName == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2Money2FunctionLibrary::Namespace] NamespaceName parameter specification is missing."))
        return Return;
    }
    Return.Value = Service.Value->Namespace(
        NamespaceName
    );
    return Return;
}