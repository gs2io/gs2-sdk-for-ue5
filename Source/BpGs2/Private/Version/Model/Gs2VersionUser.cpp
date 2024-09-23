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

#include "Version/Model/Gs2VersionUser.h"
#include "Version/Model/Gs2VersionAcceptVersion.h"
#include "Core/Model/Gs2AccessToken.h"
#include "Version/Model/Gs2VersionAcceptVersion.h"
#include "Version/Model/Gs2VersionChecker.h"
#include "Core/BpGs2Constant.h"

FGs2VersionOwnAcceptVersion UGs2VersionUserFunctionLibrary::OwnAcceptVersion(
    FGs2VersionOwnUser User,
    FString VersionName
)
{
    FGs2VersionOwnAcceptVersion Return;
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2VersionUserFunctionLibrary::OwnAcceptVersion] User parameter specification is missing."))
        return Return;
    }
    if (VersionName == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2VersionUserFunctionLibrary::OwnAcceptVersion] VersionName parameter specification is missing."))
        return Return;
    }
    Return.Value = User.Value->AcceptVersion(
        VersionName
    );
    return Return;
}

FGs2VersionOwnChecker UGs2VersionUserFunctionLibrary::OwnChecker(
    FGs2VersionOwnUser User
)
{
    FGs2VersionOwnChecker Return;
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2VersionUserFunctionLibrary::OwnChecker] User parameter specification is missing."))
        return Return;
    }
    Return.Value = User.Value->Checker(
    );
    return Return;
}