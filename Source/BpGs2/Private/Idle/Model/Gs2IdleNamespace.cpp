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

#include "Idle/Model/Gs2IdleNamespace.h"
#include "Idle/Model/Gs2IdleCategoryModel.h"
#include "Core/Model/Gs2AccessToken.h"
#include "Idle/Model/Gs2IdleCategoryModel.h"
#include "Idle/Model/Gs2IdleUser.h"
#include "Core/BpGs2Constant.h"

FGs2IdleCategoryModel UGs2IdleNamespaceFunctionLibrary::CategoryModel(
    FGs2IdleNamespace Namespace,
    FString CategoryName
)
{
    FGs2IdleCategoryModel Return;
    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2IdleNamespaceFunctionLibrary::CategoryModel] Namespace parameter specification is missing."))
        return Return;
    }
    if (CategoryName == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2IdleNamespaceFunctionLibrary::CategoryModel] CategoryName parameter specification is missing."))
        return Return;
    }
    Return.Value = Namespace.Value->CategoryModel(
        CategoryName
    );
    return Return;
}

FGs2IdleOwnUser UGs2IdleNamespaceFunctionLibrary::Me(
    FGs2IdleNamespace Namespace,
    FGs2AccessToken AccessToken
)
{
    FGs2IdleOwnUser Return;
    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2IdleNamespaceFunctionLibrary::Me] Namespace parameter specification is missing."))
        return Return;
    }
    if (AccessToken.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2IdleNamespaceFunctionLibrary::Me] AccessToken parameter specification is missing."))
        return Return;
    }
    Return.Value = Namespace.Value->Me(AccessToken.Value);
    return Return;
}