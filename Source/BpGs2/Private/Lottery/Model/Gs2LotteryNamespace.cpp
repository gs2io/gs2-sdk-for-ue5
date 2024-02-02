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

#include "Lottery/Model/Gs2LotteryNamespace.h"
#include "Lottery/Model/Gs2LotteryLotteryModel.h"
#include "Lottery/Model/Gs2LotteryDrawnPrize.h"
#include "Core/Model/Gs2AccessToken.h"
#include "Lottery/Model/Gs2LotteryLotteryModel.h"
#include "Lottery/Model/Gs2LotteryUser.h"
#include "Core/BpGs2Constant.h"

FGs2LotteryLotteryModel UGs2LotteryNamespaceFunctionLibrary::LotteryModel(
    FGs2LotteryNamespace Namespace,
    FString LotteryName
)
{
    FGs2LotteryLotteryModel Return;
    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2LotteryNamespaceFunctionLibrary::LotteryModel] Namespace parameter specification is missing."))
        return Return;
    }
    if (LotteryName == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2LotteryNamespaceFunctionLibrary::LotteryModel] LotteryName parameter specification is missing."))
        return Return;
    }
    Return.Value = Namespace.Value->LotteryModel(
        LotteryName
    );
    return Return;
}

FGs2LotteryOwnUser UGs2LotteryNamespaceFunctionLibrary::Me(
    FGs2LotteryNamespace Namespace,
    FGs2AccessToken AccessToken
)
{
    FGs2LotteryOwnUser Return;
    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2LotteryNamespaceFunctionLibrary::Me] Namespace parameter specification is missing."))
        return Return;
    }
    if (AccessToken.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2LotteryNamespaceFunctionLibrary::Me] AccessToken parameter specification is missing."))
        return Return;
    }
    Return.Value = Namespace.Value->Me(AccessToken.Value);
    return Return;
}