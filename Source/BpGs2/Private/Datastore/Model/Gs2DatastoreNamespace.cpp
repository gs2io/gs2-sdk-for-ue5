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

#include "Datastore/Model/Gs2DatastoreNamespace.h"
#include "Datastore/Domain/EzGs2Datastore.h"
#include "Core/Model/Gs2AccessToken.h"
#include "Datastore/Model/Gs2DatastoreUser.h"
#include "Core/BpGs2Constant.h"

FGs2DatastoreUser UGs2DatastoreNamespaceFunctionLibrary::User(
    FGs2DatastoreNamespace Namespace,
    FString UserId
)
{
    FGs2DatastoreUser Return;
    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2DatastoreNamespaceFunctionLibrary::User] Namespace parameter specification is missing."))
        return Return;
    }
    if (UserId == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2DatastoreNamespaceFunctionLibrary::User] UserId parameter specification is missing."))
        return Return;
    }
    Return.Value = Namespace.Value->User(
        UserId
    );
    return Return;
}

FGs2DatastoreOwnUser UGs2DatastoreNamespaceFunctionLibrary::Me(
    FGs2DatastoreNamespace Namespace,
    FGs2AccessToken AccessToken
)
{
    FGs2DatastoreOwnUser Return;
    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2DatastoreNamespaceFunctionLibrary::Me] Namespace parameter specification is missing."))
        return Return;
    }
    if (AccessToken.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2DatastoreNamespaceFunctionLibrary::Me] AccessToken parameter specification is missing."))
        return Return;
    }
    Return.Value = Namespace.Value->Me(AccessToken.Value);
    return Return;
}