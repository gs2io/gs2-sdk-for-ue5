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

#include "MegaField/Model/Gs2MegaFieldNamespace.h"
#include "MegaField/Domain/EzGs2MegaField.h"
#include "MegaField/Model/Gs2MegaFieldAreaModel.h"
#include "Core/Model/Gs2AccessToken.h"
#include "MegaField/Model/Gs2MegaFieldAreaModel.h"
#include "MegaField/Model/Gs2MegaFieldUser.h"
#include "Core/BpGs2Constant.h"

FGs2MegaFieldAreaModel UGs2MegaFieldNamespaceFunctionLibrary::AreaModel(
    FGs2MegaFieldNamespace Namespace,
    FString AreaModelName
)
{
    FGs2MegaFieldAreaModel Return;
    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2MegaFieldNamespaceFunctionLibrary::AreaModel] Namespace parameter specification is missing."))
        return Return;
    }
    if (AreaModelName == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2MegaFieldNamespaceFunctionLibrary::AreaModel] AreaModelName parameter specification is missing."))
        return Return;
    }
    Return.Value = Namespace.Value->AreaModel(
        AreaModelName
    );
    return Return;
}

FGs2MegaFieldOwnUser UGs2MegaFieldNamespaceFunctionLibrary::Me(
    FGs2MegaFieldNamespace Namespace,
    FGs2AccessToken AccessToken
)
{
    FGs2MegaFieldOwnUser Return;
    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2MegaFieldNamespaceFunctionLibrary::Me] Namespace parameter specification is missing."))
        return Return;
    }
    if (AccessToken.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2MegaFieldNamespaceFunctionLibrary::Me] AccessToken parameter specification is missing."))
        return Return;
    }
    Return.Value = Namespace.Value->Me(AccessToken.Value);
    return Return;
}