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

#include "BpGs2/Public/Formation/Model/Gs2FormationNamespace.h"
#include "BpGs2/Public/Formation/Model/Gs2FormationMoldModel.h"
#include "BpGs2/Public/Formation/Model/Gs2FormationFormModel.h"
#include "Core/Model/Gs2AccessToken.h"
#include "Formation/Model/Gs2FormationMoldModel.h"
#include "Formation/Model/Gs2FormationFormModel.h"
#include "Formation/Model/Gs2FormationUser.h"
#include "Core/BpGs2Constant.h"

FGs2FormationMoldModel UGs2FormationNamespaceFunctionLibrary::MoldModel(
    FGs2FormationNamespace Namespace,
    FString MoldName
)
{
    FGs2FormationMoldModel Return;
    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2FormationNamespaceFunctionLibrary::MoldModel] Namespace parameter specification is missing."))
        return Return;
    }
    if (MoldName == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2FormationNamespaceFunctionLibrary::MoldModel] MoldName parameter specification is missing."))
        return Return;
    }
    Return.Value = Namespace.Value->MoldModel(
        MoldName
    );
    return Return;
}

FGs2FormationFormModel UGs2FormationNamespaceFunctionLibrary::FormModel(
    FGs2FormationNamespace Namespace,
    FString FormModelName
)
{
    FGs2FormationFormModel Return;
    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2FormationNamespaceFunctionLibrary::FormModel] Namespace parameter specification is missing."))
        return Return;
    }
    if (FormModelName == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2FormationNamespaceFunctionLibrary::FormModel] FormModelName parameter specification is missing."))
        return Return;
    }
    Return.Value = Namespace.Value->FormModel(
        FormModelName
    );
    return Return;
}

FGs2FormationOwnUser UGs2FormationNamespaceFunctionLibrary::Me(
    FGs2FormationNamespace Namespace,
    FGs2AccessToken AccessToken
)
{
    FGs2FormationOwnUser Return;
    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2FormationNamespaceFunctionLibrary::Me] Namespace parameter specification is missing."))
        return Return;
    }
    if (AccessToken.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2FormationNamespaceFunctionLibrary::Me] AccessToken parameter specification is missing."))
        return Return;
    }
    Return.Value = Namespace.Value->Me(AccessToken.Value);
    return Return;
}