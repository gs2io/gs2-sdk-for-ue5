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

#include "LoginReward/Model/Gs2LoginRewardUser.h"
#include "LoginReward/Domain/EzGs2LoginReward.h"
#include "LoginReward/Model/Gs2LoginRewardReceiveStatus.h"
#include "Core/Model/Gs2AccessToken.h"
#include "LoginReward/Model/Gs2LoginRewardBonus.h"
#include "LoginReward/Model/Gs2LoginRewardReceiveStatus.h"
#include "Core/BpGs2Constant.h"

FGs2LoginRewardOwnBonus UGs2LoginRewardUserFunctionLibrary::OwnBonus(
    FGs2LoginRewardOwnUser User
)
{
    FGs2LoginRewardOwnBonus Return;
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2LoginRewardUserFunctionLibrary::OwnBonus] User parameter specification is missing."))
        return Return;
    }
    Return.Value = User.Value->Bonus(
    );
    return Return;
}

FGs2LoginRewardOwnReceiveStatus UGs2LoginRewardUserFunctionLibrary::OwnReceiveStatus(
    FGs2LoginRewardOwnUser User,
    FString BonusModelName
)
{
    FGs2LoginRewardOwnReceiveStatus Return;
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2LoginRewardUserFunctionLibrary::OwnReceiveStatus] User parameter specification is missing."))
        return Return;
    }
    if (BonusModelName == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2LoginRewardUserFunctionLibrary::OwnReceiveStatus] BonusModelName parameter specification is missing."))
        return Return;
    }
    Return.Value = User.Value->ReceiveStatus(
        BonusModelName
    );
    return Return;
}