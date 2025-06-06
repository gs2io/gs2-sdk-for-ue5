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

#include "Money2/Model/Gs2Money2User.h"
#include "Money2/Domain/EzGs2Money2.h"
#include "Money2/Model/Gs2Money2Wallet.h"
#include "Money2/Model/Gs2Money2SubscriptionStatus.h"
#include "Core/Model/Gs2AccessToken.h"
#include "Money2/Model/Gs2Money2Wallet.h"
#include "Money2/Model/Gs2Money2SubscriptionStatus.h"
#include "Core/BpGs2Constant.h"

FGs2Money2OwnWallet UGs2Money2UserFunctionLibrary::OwnWallet(
    FGs2Money2OwnUser User,
    int32 Slot
)
{
    FGs2Money2OwnWallet Return;
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2Money2UserFunctionLibrary::OwnWallet] User parameter specification is missing."))
        return Return;
    }
    Return.Value = User.Value->Wallet(
        Slot
    );
    return Return;
}

FGs2Money2OwnSubscriptionStatus UGs2Money2UserFunctionLibrary::OwnSubscriptionStatus(
    FGs2Money2OwnUser User,
    FString ContentName
)
{
    FGs2Money2OwnSubscriptionStatus Return;
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2Money2UserFunctionLibrary::OwnSubscriptionStatus] User parameter specification is missing."))
        return Return;
    }
    if (ContentName == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2Money2UserFunctionLibrary::OwnSubscriptionStatus] ContentName parameter specification is missing."))
        return Return;
    }
    Return.Value = User.Value->SubscriptionStatus(
        ContentName
    );
    return Return;
}