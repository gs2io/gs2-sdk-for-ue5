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

#include "SkillTree/Model/Gs2SkillTree.h"
#include "SkillTree/Domain/EzGs2SkillTree.h"
#include "SkillTree/Model/Gs2SkillTreeNamespace.h"
#include "Core/BpGs2Constant.h"

FGs2SkillTree UGs2SkillTreeFunctionLibrary::Service(
    FGs2Client Client
)
{
    FGs2SkillTree Return;
    if (Client.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2SkillTreeFunctionLibrary::Service] Client parameter specification is missing."))
        return Return;
    }
    Return.Value = Client.Value->SkillTree;
    return Return;
}
FGs2SkillTreeNamespace UGs2SkillTreeFunctionLibrary::Namespace(
    FGs2SkillTree Service,
    FString NamespaceName
)
{
    FGs2SkillTreeNamespace Return;
    if (Service.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2SkillTreeFunctionLibrary::Namespace] Service parameter specification is missing."))
        return Return;
    }
    if (NamespaceName == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2SkillTreeFunctionLibrary::Namespace] NamespaceName parameter specification is missing."))
        return Return;
    }
    Return.Value = Service.Value->Namespace(
        NamespaceName
    );
    return Return;
}