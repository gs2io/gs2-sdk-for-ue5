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

#include "Enchant/Model/Gs2EnchantNamespace.h"
#include "Enchant/Model/Gs2EnchantBalanceParameterModel.h"
#include "Enchant/Model/Gs2EnchantRarityParameterModel.h"
#include "Core/Model/Gs2AccessToken.h"
#include "Enchant/Model/Gs2EnchantBalanceParameterModel.h"
#include "Enchant/Model/Gs2EnchantRarityParameterModel.h"
#include "Enchant/Model/Gs2EnchantUser.h"
#include "Core/BpGs2Constant.h"

FGs2EnchantBalanceParameterModel UGs2EnchantNamespaceFunctionLibrary::BalanceParameterModel(
    FGs2EnchantNamespace Namespace,
    FString ParameterName
)
{
    FGs2EnchantBalanceParameterModel Return;
    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2EnchantNamespaceFunctionLibrary::BalanceParameterModel] Namespace parameter specification is missing."))
        return Return;
    }
    if (ParameterName == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2EnchantNamespaceFunctionLibrary::BalanceParameterModel] ParameterName parameter specification is missing."))
        return Return;
    }
    Return.Value = Namespace.Value->BalanceParameterModel(
        ParameterName
    );
    return Return;
}

FGs2EnchantRarityParameterModel UGs2EnchantNamespaceFunctionLibrary::RarityParameterModel(
    FGs2EnchantNamespace Namespace,
    FString ParameterName
)
{
    FGs2EnchantRarityParameterModel Return;
    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2EnchantNamespaceFunctionLibrary::RarityParameterModel] Namespace parameter specification is missing."))
        return Return;
    }
    if (ParameterName == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2EnchantNamespaceFunctionLibrary::RarityParameterModel] ParameterName parameter specification is missing."))
        return Return;
    }
    Return.Value = Namespace.Value->RarityParameterModel(
        ParameterName
    );
    return Return;
}

FGs2EnchantOwnUser UGs2EnchantNamespaceFunctionLibrary::Me(
    FGs2EnchantNamespace Namespace,
    FGs2AccessToken AccessToken
)
{
    FGs2EnchantOwnUser Return;
    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2EnchantNamespaceFunctionLibrary::Me] Namespace parameter specification is missing."))
        return Return;
    }
    if (AccessToken.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2EnchantNamespaceFunctionLibrary::Me] AccessToken parameter specification is missing."))
        return Return;
    }
    Return.Value = Namespace.Value->Me(AccessToken.Value);
    return Return;
}