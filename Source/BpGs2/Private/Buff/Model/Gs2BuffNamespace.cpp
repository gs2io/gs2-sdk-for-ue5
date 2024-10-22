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

#include "Buff/Model/Gs2BuffNamespace.h"
#include "Buff/Domain/EzGs2Buff.h"
#include "Buff/Model/Gs2BuffBuffEntryModel.h"
#include "Core/Model/Gs2AccessToken.h"
#include "Buff/Model/Gs2BuffBuffEntryModel.h"
#include "Buff/Model/Gs2BuffUser.h"
#include "Core/BpGs2Constant.h"

FGs2BuffBuffEntryModel UGs2BuffNamespaceFunctionLibrary::BuffEntryModel(
    FGs2BuffNamespace Namespace,
    FString BuffEntryName
)
{
    FGs2BuffBuffEntryModel Return;
    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2BuffNamespaceFunctionLibrary::BuffEntryModel] Namespace parameter specification is missing."))
        return Return;
    }
    if (BuffEntryName == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2BuffNamespaceFunctionLibrary::BuffEntryModel] BuffEntryName parameter specification is missing."))
        return Return;
    }
    Return.Value = Namespace.Value->BuffEntryModel(
        BuffEntryName
    );
    return Return;
}

FGs2BuffOwnUser UGs2BuffNamespaceFunctionLibrary::Me(
    FGs2BuffNamespace Namespace,
    FGs2AccessToken AccessToken
)
{
    FGs2BuffOwnUser Return;
    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2BuffNamespaceFunctionLibrary::Me] Namespace parameter specification is missing."))
        return Return;
    }
    if (AccessToken.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2BuffNamespaceFunctionLibrary::Me] AccessToken parameter specification is missing."))
        return Return;
    }
    Return.Value = Namespace.Value->Me(AccessToken.Value);
    return Return;
}