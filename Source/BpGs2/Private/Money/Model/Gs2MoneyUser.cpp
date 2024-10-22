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

#include "Money/Model/Gs2MoneyUser.h"
#include "Money/Domain/EzGs2Money.h"
#include "Money/Model/Gs2MoneyWallet.h"
#include "Core/Model/Gs2AccessToken.h"
#include "Money/Model/Gs2MoneyWallet.h"
#include "Core/BpGs2Constant.h"

FGs2MoneyOwnWallet UGs2MoneyUserFunctionLibrary::OwnWallet(
    FGs2MoneyOwnUser User,
    int32 Slot
)
{
    FGs2MoneyOwnWallet Return;
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2MoneyUserFunctionLibrary::OwnWallet] User parameter specification is missing."))
        return Return;
    }
    Return.Value = User.Value->Wallet(
        Slot
    );
    return Return;
}