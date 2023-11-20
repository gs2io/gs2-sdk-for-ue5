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

#include "Stamina/Model/Gs2StaminaNamespace.h"
#include "Stamina/Model/Gs2StaminaStaminaModel.h"
#include "Core/Model/Gs2AccessToken.h"
#include "Stamina/Model/Gs2StaminaStaminaModel.h"
#include "Stamina/Model/Gs2StaminaUser.h"
#include "Core/BpGs2Constant.h"

FGs2StaminaStaminaModel UGs2StaminaNamespaceFunctionLibrary::StaminaModel(
    FGs2StaminaNamespace Namespace,
    FString StaminaName
)
{
    FGs2StaminaStaminaModel Return;
    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2StaminaNamespaceFunctionLibrary::StaminaModel] Namespace parameter specification is missing."))
        return Return;
    }
    if (StaminaName == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2StaminaNamespaceFunctionLibrary::StaminaModel] StaminaName parameter specification is missing."))
        return Return;
    }
    Return.Value = Namespace.Value->StaminaModel(
        StaminaName
    );
    return Return;
}

FGs2StaminaOwnUser UGs2StaminaNamespaceFunctionLibrary::Me(
    FGs2StaminaNamespace Namespace,
    FGs2AccessToken AccessToken
)
{
    FGs2StaminaOwnUser Return;
    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2StaminaNamespaceFunctionLibrary::Me] Namespace parameter specification is missing."))
        return Return;
    }
    if (AccessToken.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2StaminaNamespaceFunctionLibrary::Me] AccessToken parameter specification is missing."))
        return Return;
    }
    Return.Value = Namespace.Value->Me(AccessToken.Value);
    return Return;
}