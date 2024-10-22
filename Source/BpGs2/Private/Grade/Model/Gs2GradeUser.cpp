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

#include "Grade/Model/Gs2GradeUser.h"
#include "Grade/Domain/EzGs2Grade.h"
#include "Grade/Model/Gs2GradeStatus.h"
#include "Core/Model/Gs2AccessToken.h"
#include "Grade/Model/Gs2GradeStatus.h"
#include "Core/BpGs2Constant.h"

FGs2GradeOwnStatus UGs2GradeUserFunctionLibrary::OwnStatus(
    FGs2GradeOwnUser User,
    FString GradeName,
    FString PropertyId
)
{
    FGs2GradeOwnStatus Return;
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2GradeUserFunctionLibrary::OwnStatus] User parameter specification is missing."))
        return Return;
    }
    if (GradeName == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2GradeUserFunctionLibrary::OwnStatus] GradeName parameter specification is missing."))
        return Return;
    }
    if (PropertyId == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2GradeUserFunctionLibrary::OwnStatus] PropertyId parameter specification is missing."))
        return Return;
    }
    Return.Value = User.Value->Status(
        GradeName,
        PropertyId
    );
    return Return;
}