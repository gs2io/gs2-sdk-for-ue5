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

#include "AdReward/Model/Gs2AdReward.h"
#include "AdReward/Domain/EzGs2AdReward.h"
#include "AdReward/Model/Gs2AdRewardNamespace.h"
#include "Core/BpGs2Constant.h"

FGs2AdReward UGs2AdRewardFunctionLibrary::Service(
    FGs2Client Client,
    FBpAdRewardChangePointNotificationEvent ChangePointNotification
)
{
    FGs2AdReward Return;
    if (Client.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2AdRewardFunctionLibrary::Service] Client parameter specification is missing."))
        return Return;
    }
    Client.Value->AdReward->OnChangePointNotification().AddLambda([&ChangePointNotification](auto Notification)
    {
        ChangePointNotification.Value.Execute(EzChangePointNotificationToFGs2AdRewardChangePointNotification(Notification));
    });
    Return.Value = Client.Value->AdReward;
    return Return;
}
FGs2AdRewardNamespace UGs2AdRewardFunctionLibrary::Namespace(
    FGs2AdReward Service,
    FString NamespaceName
)
{
    FGs2AdRewardNamespace Return;
    if (Service.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2AdRewardFunctionLibrary::Namespace] Service parameter specification is missing."))
        return Return;
    }
    if (NamespaceName == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2AdRewardFunctionLibrary::Namespace] NamespaceName parameter specification is missing."))
        return Return;
    }
    Return.Value = Service.Value->Namespace(
        NamespaceName
    );
    return Return;
}