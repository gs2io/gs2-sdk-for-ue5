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

#include "Quest/Model/Gs2QuestNamespace.h"
#include "Quest/Domain/EzGs2Quest.h"
#include "Quest/Model/Gs2QuestQuestGroupModel.h"
#include "Core/Model/Gs2AccessToken.h"
#include "Quest/Model/Gs2QuestQuestGroupModel.h"
#include "Quest/Model/Gs2QuestUser.h"
#include "Core/BpGs2Constant.h"

FGs2QuestQuestGroupModel UGs2QuestNamespaceFunctionLibrary::QuestGroupModel(
    FGs2QuestNamespace Namespace,
    FString QuestGroupName
)
{
    FGs2QuestQuestGroupModel Return;
    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2QuestNamespaceFunctionLibrary::QuestGroupModel] Namespace parameter specification is missing."))
        return Return;
    }
    if (QuestGroupName == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2QuestNamespaceFunctionLibrary::QuestGroupModel] QuestGroupName parameter specification is missing."))
        return Return;
    }
    Return.Value = Namespace.Value->QuestGroupModel(
        QuestGroupName
    );
    return Return;
}

FGs2QuestOwnUser UGs2QuestNamespaceFunctionLibrary::Me(
    FGs2QuestNamespace Namespace,
    FGs2AccessToken AccessToken
)
{
    FGs2QuestOwnUser Return;
    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2QuestNamespaceFunctionLibrary::Me] Namespace parameter specification is missing."))
        return Return;
    }
    if (AccessToken.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2QuestNamespaceFunctionLibrary::Me] AccessToken parameter specification is missing."))
        return Return;
    }
    Return.Value = Namespace.Value->Me(AccessToken.Value);
    return Return;
}