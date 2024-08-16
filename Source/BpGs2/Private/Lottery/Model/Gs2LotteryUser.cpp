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

#include "Lottery/Model/Gs2LotteryUser.h"
#include "Lottery/Domain/EzGs2Lottery.h"
#include "Lottery/Model/Gs2LotteryBoxItems.h"
#include "Core/Model/Gs2AccessToken.h"
#include "Lottery/Model/Gs2LotteryBoxItems.h"
#include "Core/BpGs2Constant.h"

FGs2LotteryOwnBoxItems UGs2LotteryUserFunctionLibrary::OwnBoxItems(
    FGs2LotteryOwnUser User,
    FString PrizeTableName
)
{
    FGs2LotteryOwnBoxItems Return;
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2LotteryUserFunctionLibrary::OwnBoxItems] User parameter specification is missing."))
        return Return;
    }
    if (PrizeTableName == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2LotteryUserFunctionLibrary::OwnBoxItems] PrizeTableName parameter specification is missing."))
        return Return;
    }
    Return.Value = User.Value->BoxItems(
        PrizeTableName
    );
    return Return;
}