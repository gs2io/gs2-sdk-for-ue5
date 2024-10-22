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

#include "Version/Model/Gs2VersionNamespace.h"
#include "Version/Domain/EzGs2Version.h"
#include "Version/Model/Gs2VersionVersionModel.h"
#include "Core/Model/Gs2AccessToken.h"
#include "Version/Model/Gs2VersionVersionModel.h"
#include "Version/Model/Gs2VersionUser.h"
#include "Core/BpGs2Constant.h"

FGs2VersionVersionModel UGs2VersionNamespaceFunctionLibrary::VersionModel(
    FGs2VersionNamespace Namespace,
    FString VersionName
)
{
    FGs2VersionVersionModel Return;
    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2VersionNamespaceFunctionLibrary::VersionModel] Namespace parameter specification is missing."))
        return Return;
    }
    if (VersionName == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2VersionNamespaceFunctionLibrary::VersionModel] VersionName parameter specification is missing."))
        return Return;
    }
    Return.Value = Namespace.Value->VersionModel(
        VersionName
    );
    return Return;
}

FGs2VersionOwnUser UGs2VersionNamespaceFunctionLibrary::Me(
    FGs2VersionNamespace Namespace,
    FGs2AccessToken AccessToken
)
{
    FGs2VersionOwnUser Return;
    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2VersionNamespaceFunctionLibrary::Me] Namespace parameter specification is missing."))
        return Return;
    }
    if (AccessToken.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2VersionNamespaceFunctionLibrary::Me] AccessToken parameter specification is missing."))
        return Return;
    }
    Return.Value = Namespace.Value->Me(AccessToken.Value);
    return Return;
}