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

#include "Enhance/Model/Gs2EnhanceUser.h"
#include "Enhance/Model/Gs2EnhanceProgress.h"
#include "Core/Model/Gs2AccessToken.h"
#include "Enhance/Model/Gs2EnhanceProgress.h"
#include "Enhance/Model/Gs2EnhanceEnhance.h"
#include "Core/BpGs2Constant.h"

FGs2EnhanceOwnProgress UGs2EnhanceUserFunctionLibrary::OwnProgress(
    FGs2EnhanceOwnUser User
)
{
    FGs2EnhanceOwnProgress Return;
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2EnhanceUserFunctionLibrary::OwnProgress] User parameter specification is missing."))
        return Return;
    }
    Return.Value = User.Value->Progress(
    );
    return Return;
}

FGs2EnhanceOwnEnhance UGs2EnhanceUserFunctionLibrary::OwnEnhance(
    FGs2EnhanceOwnUser User
)
{
    FGs2EnhanceOwnEnhance Return;
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2EnhanceUserFunctionLibrary::OwnEnhance] User parameter specification is missing."))
        return Return;
    }
    Return.Value = User.Value->Enhance(
    );
    return Return;
}