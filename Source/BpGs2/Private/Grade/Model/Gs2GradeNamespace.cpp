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

#include "Grade/Model/Gs2GradeNamespace.h"
#include "Grade/Model/Gs2GradeGradeModel.h"
#include "Core/Model/Gs2AccessToken.h"
#include "Grade/Model/Gs2GradeGradeModel.h"
#include "Grade/Model/Gs2GradeUser.h"
#include "Core/BpGs2Constant.h"

FGs2GradeGradeModel UGs2GradeNamespaceFunctionLibrary::GradeModel(
    FGs2GradeNamespace Namespace,
    FString GradeName
)
{
    FGs2GradeGradeModel Return;
    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2GradeNamespaceFunctionLibrary::GradeModel] Namespace parameter specification is missing."))
        return Return;
    }
    if (GradeName == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2GradeNamespaceFunctionLibrary::GradeModel] GradeName parameter specification is missing."))
        return Return;
    }
    Return.Value = Namespace.Value->GradeModel(
        GradeName
    );
    return Return;
}

FGs2GradeOwnUser UGs2GradeNamespaceFunctionLibrary::Me(
    FGs2GradeNamespace Namespace,
    FGs2AccessToken AccessToken
)
{
    FGs2GradeOwnUser Return;
    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2GradeNamespaceFunctionLibrary::Me] Namespace parameter specification is missing."))
        return Return;
    }
    if (AccessToken.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2GradeNamespaceFunctionLibrary::Me] AccessToken parameter specification is missing."))
        return Return;
    }
    Return.Value = Namespace.Value->Me(AccessToken.Value);
    return Return;
}