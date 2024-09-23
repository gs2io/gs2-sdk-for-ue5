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

#include "SkillTree/Model/Gs2SkillTreeNamespace.h"
#include "SkillTree/Model/Gs2SkillTreeNodeModel.h"
#include "Core/Model/Gs2AccessToken.h"
#include "SkillTree/Model/Gs2SkillTreeNodeModel.h"
#include "SkillTree/Model/Gs2SkillTreeUser.h"
#include "Core/BpGs2Constant.h"

FGs2SkillTreeNodeModel UGs2SkillTreeNamespaceFunctionLibrary::NodeModel(
    FGs2SkillTreeNamespace Namespace,
    FString NodeModelName
)
{
    FGs2SkillTreeNodeModel Return;
    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2SkillTreeNamespaceFunctionLibrary::NodeModel] Namespace parameter specification is missing."))
        return Return;
    }
    if (NodeModelName == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2SkillTreeNamespaceFunctionLibrary::NodeModel] NodeModelName parameter specification is missing."))
        return Return;
    }
    Return.Value = Namespace.Value->NodeModel(
        NodeModelName
    );
    return Return;
}

FGs2SkillTreeOwnUser UGs2SkillTreeNamespaceFunctionLibrary::Me(
    FGs2SkillTreeNamespace Namespace,
    FGs2AccessToken AccessToken
)
{
    FGs2SkillTreeOwnUser Return;
    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2SkillTreeNamespaceFunctionLibrary::Me] Namespace parameter specification is missing."))
        return Return;
    }
    if (AccessToken.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2SkillTreeNamespaceFunctionLibrary::Me] AccessToken parameter specification is missing."))
        return Return;
    }
    Return.Value = Namespace.Value->Me(AccessToken.Value);
    return Return;
}