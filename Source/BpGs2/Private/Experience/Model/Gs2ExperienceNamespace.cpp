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

#include "BpGs2/Public/Experience/Model/Gs2ExperienceNamespace.h"
#include "BpGs2/Public/Experience/Model/Gs2ExperienceExperienceModel.h"
#include "Core/Model/Gs2AccessToken.h"
#include "Experience/Model/Gs2ExperienceExperienceModel.h"
#include "Experience/Model/Gs2ExperienceUser.h"
#include "Core/BpGs2Constant.h"

FGs2ExperienceExperienceModel UGs2ExperienceNamespaceFunctionLibrary::ExperienceModel(
    FGs2ExperienceNamespace Namespace,
    FString ExperienceName
)
{
    FGs2ExperienceExperienceModel Return;
    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2ExperienceNamespaceFunctionLibrary::ExperienceModel] Namespace parameter specification is missing."))
        return Return;
    }
    if (ExperienceName == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2ExperienceNamespaceFunctionLibrary::ExperienceModel] ExperienceName parameter specification is missing."))
        return Return;
    }
    Return.Value = Namespace.Value->ExperienceModel(
        ExperienceName
    );
    return Return;
}

FGs2ExperienceOwnUser UGs2ExperienceNamespaceFunctionLibrary::Me(
    FGs2ExperienceNamespace Namespace,
    FGs2AccessToken AccessToken
)
{
    FGs2ExperienceOwnUser Return;
    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2ExperienceNamespaceFunctionLibrary::Me] Namespace parameter specification is missing."))
        return Return;
    }
    if (AccessToken.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2ExperienceNamespaceFunctionLibrary::Me] AccessToken parameter specification is missing."))
        return Return;
    }
    Return.Value = Namespace.Value->Me(AccessToken.Value);
    return Return;
}