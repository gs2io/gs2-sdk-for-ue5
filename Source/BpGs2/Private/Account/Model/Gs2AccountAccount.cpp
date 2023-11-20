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
 *
 * deny overwrite
 */

#include "Account/Model/Gs2AccountAccount.h"
#include "Account/Model/Gs2AccountTakeOver.h"
#include "Core/Model/Gs2AccessToken.h"
#include "Account/Model/Gs2AccountTakeOver.h"
#include "Core/BpGs2Constant.h"

FGs2AccountTakeOver UGs2AccountAccountFunctionLibrary::TakeOver(
    FGs2AccountAccount Account,
    int32 Type
)
{
    FGs2AccountTakeOver Return;
    if (Account.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2AccountAccountFunctionLibrary::TakeOver] Account parameter specification is missing."))
        return Return;
    }
    Return.Value = Account.Value->TakeOver(
        Type
    );
    return Return;
}

FGs2AccountOwnTakeOver UGs2AccountAccountFunctionLibrary::OwnTakeOver(
    FGs2AccountOwnAccount Account,
    int32 Type
)
{
    FGs2AccountOwnTakeOver Return;
    if (Account.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2AccountAccountFunctionLibrary::OwnTakeOver] Account parameter specification is missing."))
        return Return;
    }
    Return.Value = Account.Value->TakeOver(
        Type
    );
    return Return;
}