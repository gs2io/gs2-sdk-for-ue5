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

#include "Chat/Model/Gs2ChatNamespace.h"
#include "Core/Model/Gs2AccessToken.h"
#include "Chat/Model/Gs2ChatUser.h"
#include "Core/BpGs2Constant.h"

FGs2ChatUser UGs2ChatNamespaceFunctionLibrary::User(
    FGs2ChatNamespace Namespace,
    FString UserId
)
{
    FGs2ChatUser Return;
    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2ChatNamespaceFunctionLibrary::User] Namespace parameter specification is missing."))
        return Return;
    }
    if (UserId == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2ChatNamespaceFunctionLibrary::User] UserId parameter specification is missing."))
        return Return;
    }
    Return.Value = Namespace.Value->User(
        UserId
    );
    return Return;
}

FGs2ChatOwnUser UGs2ChatNamespaceFunctionLibrary::Me(
    FGs2ChatNamespace Namespace,
    FGs2AccessToken AccessToken
)
{
    FGs2ChatOwnUser Return;
    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2ChatNamespaceFunctionLibrary::Me] Namespace parameter specification is missing."))
        return Return;
    }
    if (AccessToken.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2ChatNamespaceFunctionLibrary::Me] AccessToken parameter specification is missing."))
        return Return;
    }
    Return.Value = Namespace.Value->Me(AccessToken.Value);
    return Return;
}