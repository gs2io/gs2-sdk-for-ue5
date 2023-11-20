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

#include "Formation/Model/Gs2FormationNamespace.h"
#include "Formation/Model/Gs2FormationMoldModel.h"
#include "Formation/Model/Gs2FormationPropertyFormModel.h"
#include "Core/Model/Gs2AccessToken.h"
#include "Formation/Model/Gs2FormationMoldModel.h"
#include "Formation/Model/Gs2FormationPropertyFormModel.h"
#include "Formation/Model/Gs2FormationUser.h"
#include "Core/BpGs2Constant.h"

FGs2FormationMoldModel UGs2FormationNamespaceFunctionLibrary::MoldModel(
    FGs2FormationNamespace Namespace,
    FString MoldModelName
)
{
    FGs2FormationMoldModel Return;
    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2FormationNamespaceFunctionLibrary::MoldModel] Namespace parameter specification is missing."))
        return Return;
    }
    if (MoldModelName == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2FormationNamespaceFunctionLibrary::MoldModel] MoldModelName parameter specification is missing."))
        return Return;
    }
    Return.Value = Namespace.Value->MoldModel(
        MoldModelName
    );
    return Return;
}

FGs2FormationPropertyFormModel UGs2FormationNamespaceFunctionLibrary::PropertyFormModel(
    FGs2FormationNamespace Namespace,
    FString PropertyFormModelName
)
{
    FGs2FormationPropertyFormModel Return;
    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2FormationNamespaceFunctionLibrary::PropertyFormModel] Namespace parameter specification is missing."))
        return Return;
    }
    if (PropertyFormModelName == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2FormationNamespaceFunctionLibrary::PropertyFormModel] PropertyFormModelName parameter specification is missing."))
        return Return;
    }
    Return.Value = Namespace.Value->PropertyFormModel(
        PropertyFormModelName
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