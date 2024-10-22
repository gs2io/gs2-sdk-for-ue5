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

#include "Enchant/Model/Gs2EnchantUser.h"
#include "Enchant/Domain/EzGs2Enchant.h"
#include "Enchant/Model/Gs2EnchantBalanceParameterStatus.h"
#include "Enchant/Model/Gs2EnchantRarityParameterStatus.h"
#include "Core/Model/Gs2AccessToken.h"
#include "Enchant/Model/Gs2EnchantBalanceParameterStatus.h"
#include "Enchant/Model/Gs2EnchantRarityParameterStatus.h"
#include "Core/BpGs2Constant.h"

FGs2EnchantOwnBalanceParameterStatus UGs2EnchantUserFunctionLibrary::OwnBalanceParameterStatus(
    FGs2EnchantOwnUser User,
    FString ParameterName,
    FString PropertyId
)
{
    FGs2EnchantOwnBalanceParameterStatus Return;
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2EnchantUserFunctionLibrary::OwnBalanceParameterStatus] User parameter specification is missing."))
        return Return;
    }
    if (ParameterName == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2EnchantUserFunctionLibrary::OwnBalanceParameterStatus] ParameterName parameter specification is missing."))
        return Return;
    }
    if (PropertyId == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2EnchantUserFunctionLibrary::OwnBalanceParameterStatus] PropertyId parameter specification is missing."))
        return Return;
    }
    Return.Value = User.Value->BalanceParameterStatus(
        ParameterName,
        PropertyId
    );
    return Return;
}

FGs2EnchantOwnRarityParameterStatus UGs2EnchantUserFunctionLibrary::OwnRarityParameterStatus(
    FGs2EnchantOwnUser User,
    FString ParameterName,
    FString PropertyId
)
{
    FGs2EnchantOwnRarityParameterStatus Return;
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2EnchantUserFunctionLibrary::OwnRarityParameterStatus] User parameter specification is missing."))
        return Return;
    }
    if (ParameterName == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2EnchantUserFunctionLibrary::OwnRarityParameterStatus] ParameterName parameter specification is missing."))
        return Return;
    }
    if (PropertyId == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2EnchantUserFunctionLibrary::OwnRarityParameterStatus] PropertyId parameter specification is missing."))
        return Return;
    }
    Return.Value = User.Value->RarityParameterStatus(
        ParameterName,
        PropertyId
    );
    return Return;
}