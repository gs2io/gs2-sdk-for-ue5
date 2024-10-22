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

#include "Limit/Model/Gs2LimitNamespace.h"
#include "Limit/Domain/EzGs2Limit.h"
#include "Limit/Model/Gs2LimitLimitModel.h"
#include "Core/Model/Gs2AccessToken.h"
#include "Limit/Model/Gs2LimitLimitModel.h"
#include "Limit/Model/Gs2LimitUser.h"
#include "Core/BpGs2Constant.h"

FGs2LimitLimitModel UGs2LimitNamespaceFunctionLibrary::LimitModel(
    FGs2LimitNamespace Namespace,
    FString LimitName
)
{
    FGs2LimitLimitModel Return;
    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2LimitNamespaceFunctionLibrary::LimitModel] Namespace parameter specification is missing."))
        return Return;
    }
    if (LimitName == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2LimitNamespaceFunctionLibrary::LimitModel] LimitName parameter specification is missing."))
        return Return;
    }
    Return.Value = Namespace.Value->LimitModel(
        LimitName
    );
    return Return;
}

FGs2LimitOwnUser UGs2LimitNamespaceFunctionLibrary::Me(
    FGs2LimitNamespace Namespace,
    FGs2AccessToken AccessToken
)
{
    FGs2LimitOwnUser Return;
    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2LimitNamespaceFunctionLibrary::Me] Namespace parameter specification is missing."))
        return Return;
    }
    if (AccessToken.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2LimitNamespaceFunctionLibrary::Me] AccessToken parameter specification is missing."))
        return Return;
    }
    Return.Value = Namespace.Value->Me(AccessToken.Value);
    return Return;
}