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

#include "Exchange/Model/Gs2ExchangeUser.h"
#include "Exchange/Domain/EzGs2Exchange.h"
#include "Exchange/Model/Gs2ExchangeAwait.h"
#include "Core/Model/Gs2AccessToken.h"
#include "Exchange/Model/Gs2ExchangeExchange.h"
#include "Exchange/Model/Gs2ExchangeAwait.h"
#include "Core/BpGs2Constant.h"

FGs2ExchangeOwnExchange UGs2ExchangeUserFunctionLibrary::OwnExchange(
    FGs2ExchangeOwnUser User
)
{
    FGs2ExchangeOwnExchange Return;
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2ExchangeUserFunctionLibrary::OwnExchange] User parameter specification is missing."))
        return Return;
    }
    Return.Value = User.Value->Exchange(
    );
    return Return;
}

FGs2ExchangeOwnAwait UGs2ExchangeUserFunctionLibrary::OwnAwait(
    FGs2ExchangeOwnUser User,
    FString AwaitName
)
{
    FGs2ExchangeOwnAwait Return;
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2ExchangeUserFunctionLibrary::OwnAwait] User parameter specification is missing."))
        return Return;
    }
    if (AwaitName == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2ExchangeUserFunctionLibrary::OwnAwait] AwaitName parameter specification is missing."))
        return Return;
    }
    Return.Value = User.Value->Await(
        AwaitName
    );
    return Return;
}