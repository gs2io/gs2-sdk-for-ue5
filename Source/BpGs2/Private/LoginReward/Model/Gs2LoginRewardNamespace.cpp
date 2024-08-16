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

#include "LoginReward/Model/Gs2LoginRewardNamespace.h"
#include "LoginReward/Domain/EzGs2LoginReward.h"
#include "LoginReward/Model/Gs2LoginRewardBonusModel.h"
#include "Core/Model/Gs2AccessToken.h"
#include "LoginReward/Model/Gs2LoginRewardUser.h"
#include "LoginReward/Model/Gs2LoginRewardBonusModel.h"
#include "Core/BpGs2Constant.h"

FGs2LoginRewardOwnUser UGs2LoginRewardNamespaceFunctionLibrary::Me(
    FGs2LoginRewardNamespace Namespace,
    FGs2AccessToken AccessToken
)
{
    FGs2LoginRewardOwnUser Return;
    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2LoginRewardNamespaceFunctionLibrary::Me] Namespace parameter specification is missing."))
        return Return;
    }
    if (AccessToken.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2LoginRewardNamespaceFunctionLibrary::Me] AccessToken parameter specification is missing."))
        return Return;
    }
    Return.Value = Namespace.Value->Me(AccessToken.Value);
    return Return;
}

FGs2LoginRewardBonusModel UGs2LoginRewardNamespaceFunctionLibrary::BonusModel(
    FGs2LoginRewardNamespace Namespace,
    FString BonusModelName
)
{
    FGs2LoginRewardBonusModel Return;
    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2LoginRewardNamespaceFunctionLibrary::BonusModel] Namespace parameter specification is missing."))
        return Return;
    }
    if (BonusModelName == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2LoginRewardNamespaceFunctionLibrary::BonusModel] BonusModelName parameter specification is missing."))
        return Return;
    }
    Return.Value = Namespace.Value->BonusModel(
        BonusModelName
    );
    return Return;
}