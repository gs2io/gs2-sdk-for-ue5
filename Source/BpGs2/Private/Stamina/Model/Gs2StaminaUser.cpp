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

#include "Stamina/Model/Gs2StaminaUser.h"
#include "Stamina/Domain/EzGs2Stamina.h"
#include "Stamina/Model/Gs2StaminaStamina.h"
#include "Core/Model/Gs2AccessToken.h"
#include "Stamina/Model/Gs2StaminaStamina.h"
#include "Core/BpGs2Constant.h"

FGs2StaminaOwnStamina UGs2StaminaUserFunctionLibrary::OwnStamina(
    FGs2StaminaOwnUser User,
    FString StaminaName
)
{
    FGs2StaminaOwnStamina Return;
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2StaminaUserFunctionLibrary::OwnStamina] User parameter specification is missing."))
        return Return;
    }
    if (StaminaName == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2StaminaUserFunctionLibrary::OwnStamina] StaminaName parameter specification is missing."))
        return Return;
    }
    Return.Value = User.Value->Stamina(
        StaminaName
    );
    return Return;
}