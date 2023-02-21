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

#include "BpGs2/Public/Account/Model/Gs2AccountNamespace.h"
#include "BpGs2/Public/Account/Model/Gs2AccountAccount.h"
#include "Core/Model/Gs2AccessToken.h"
#include "Account/Model/Gs2AccountAccount.h"
#include "Core/BpGs2Constant.h"

FGs2AccountAccount UGs2AccountNamespaceFunctionLibrary::Account(
    FGs2AccountNamespace Namespace,
    FString UserId
)
{
    FGs2AccountAccount Return;
    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2AccountNamespaceFunctionLibrary::Account] Namespace parameter specification is missing."))
        return Return;
    }
    if (UserId == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2AccountNamespaceFunctionLibrary::Account] UserId parameter specification is missing."))
        return Return;
    }
    Return.Value = Namespace.Value->Account(
        UserId
    );
    return Return;
}

FGs2AccountOwnAccount UGs2AccountNamespaceFunctionLibrary::Me(
    FGs2AccountNamespace Namespace,
    FGs2AccessToken AccessToken
)
{
    FGs2AccountOwnAccount Return;
    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2AccountNamespaceFunctionLibrary::Me] Namespace parameter specification is missing."))
        return Return;
    }
    if (AccessToken.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2AccountNamespaceFunctionLibrary::Me] AccessToken parameter specification is missing."))
        return Return;
    }
    Return.Value = Namespace.Value->Me(AccessToken.Value);
    return Return;
}