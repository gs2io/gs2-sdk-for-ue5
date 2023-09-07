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

#include "BpGs2/Public/Formation/Model/Gs2FormationUser.h"
#include "BpGs2/Public/Formation/Model/Gs2FormationMold.h"
#include "BpGs2/Public/Formation/Model/Gs2FormationPropertyForm.h"
#include "Core/Model/Gs2AccessToken.h"
#include "Formation/Model/Gs2FormationMold.h"
#include "Formation/Model/Gs2FormationPropertyForm.h"
#include "Core/BpGs2Constant.h"

FGs2FormationOwnMold UGs2FormationUserFunctionLibrary::OwnMold(
    FGs2FormationOwnUser User,
    FString MoldModelName
)
{
    FGs2FormationOwnMold Return;
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2FormationUserFunctionLibrary::OwnMold] User parameter specification is missing."))
        return Return;
    }
    if (MoldModelName == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2FormationUserFunctionLibrary::OwnMold] MoldModelName parameter specification is missing."))
        return Return;
    }
    Return.Value = User.Value->Mold(
        MoldModelName
    );
    return Return;
}

FGs2FormationOwnPropertyForm UGs2FormationUserFunctionLibrary::OwnPropertyForm(
    FGs2FormationOwnUser User,
    FString PropertyFormModelName,
    FString PropertyId
)
{
    FGs2FormationOwnPropertyForm Return;
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2FormationUserFunctionLibrary::OwnPropertyForm] User parameter specification is missing."))
        return Return;
    }
    if (PropertyFormModelName == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2FormationUserFunctionLibrary::OwnPropertyForm] PropertyFormModelName parameter specification is missing."))
        return Return;
    }
    if (PropertyId == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2FormationUserFunctionLibrary::OwnPropertyForm] PropertyId parameter specification is missing."))
        return Return;
    }
    Return.Value = User.Value->PropertyForm(
        PropertyFormModelName,
        PropertyId
    );
    return Return;
}