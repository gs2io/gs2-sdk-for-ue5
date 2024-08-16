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

#include "SerialKey/Model/Gs2SerialKeyNamespace.h"
#include "SerialKey/Domain/EzGs2SerialKey.h"
#include "SerialKey/Model/Gs2SerialKeyCampaignModel.h"
#include "Core/Model/Gs2AccessToken.h"
#include "SerialKey/Model/Gs2SerialKeyCampaignModel.h"
#include "SerialKey/Model/Gs2SerialKeyUser.h"
#include "Core/BpGs2Constant.h"

FGs2SerialKeyCampaignModel UGs2SerialKeyNamespaceFunctionLibrary::CampaignModel(
    FGs2SerialKeyNamespace Namespace,
    FString CampaignModelName
)
{
    FGs2SerialKeyCampaignModel Return;
    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2SerialKeyNamespaceFunctionLibrary::CampaignModel] Namespace parameter specification is missing."))
        return Return;
    }
    if (CampaignModelName == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2SerialKeyNamespaceFunctionLibrary::CampaignModel] CampaignModelName parameter specification is missing."))
        return Return;
    }
    Return.Value = Namespace.Value->CampaignModel(
        CampaignModelName
    );
    return Return;
}

FGs2SerialKeyUser UGs2SerialKeyNamespaceFunctionLibrary::User(
    FGs2SerialKeyNamespace Namespace,
    FString UserId
)
{
    FGs2SerialKeyUser Return;
    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2SerialKeyNamespaceFunctionLibrary::User] Namespace parameter specification is missing."))
        return Return;
    }
    if (UserId == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2SerialKeyNamespaceFunctionLibrary::User] UserId parameter specification is missing."))
        return Return;
    }
    Return.Value = Namespace.Value->User(
        UserId
    );
    return Return;
}

FGs2SerialKeyOwnUser UGs2SerialKeyNamespaceFunctionLibrary::Me(
    FGs2SerialKeyNamespace Namespace,
    FGs2AccessToken AccessToken
)
{
    FGs2SerialKeyOwnUser Return;
    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2SerialKeyNamespaceFunctionLibrary::Me] Namespace parameter specification is missing."))
        return Return;
    }
    if (AccessToken.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2SerialKeyNamespaceFunctionLibrary::Me] AccessToken parameter specification is missing."))
        return Return;
    }
    Return.Value = Namespace.Value->Me(AccessToken.Value);
    return Return;
}