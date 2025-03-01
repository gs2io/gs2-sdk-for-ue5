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

#include "MegaField/Model/Gs2MegaFieldUser.h"
#include "MegaField/Domain/EzGs2MegaField.h"
#include "MegaField/Model/Gs2MegaFieldSpatial.h"
#include "Core/Model/Gs2AccessToken.h"
#include "MegaField/Model/Gs2MegaFieldSpatial.h"
#include "Core/BpGs2Constant.h"

FGs2MegaFieldOwnSpatial UGs2MegaFieldUserFunctionLibrary::OwnSpatial(
    FGs2MegaFieldOwnUser User,
    FString AreaModelName,
    FString LayerModelName
)
{
    FGs2MegaFieldOwnSpatial Return;
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2MegaFieldUserFunctionLibrary::OwnSpatial] User parameter specification is missing."))
        return Return;
    }
    if (AreaModelName == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2MegaFieldUserFunctionLibrary::OwnSpatial] AreaModelName parameter specification is missing."))
        return Return;
    }
    if (LayerModelName == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2MegaFieldUserFunctionLibrary::OwnSpatial] LayerModelName parameter specification is missing."))
        return Return;
    }
    Return.Value = User.Value->Spatial(
        AreaModelName,
        LayerModelName
    );
    return Return;
}