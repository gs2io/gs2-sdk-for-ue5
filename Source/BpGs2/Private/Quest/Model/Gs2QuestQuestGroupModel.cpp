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

#include "Quest/Model/Gs2QuestQuestGroupModel.h"
#include "Quest/Model/Gs2QuestQuestModel.h"
#include "Core/Model/Gs2AccessToken.h"
#include "Quest/Model/Gs2QuestQuestModel.h"
#include "Core/BpGs2Constant.h"

FGs2QuestQuestModel UGs2QuestQuestGroupModelFunctionLibrary::QuestModel(
    FGs2QuestQuestGroupModel QuestGroupModel,
    FString QuestName
)
{
    FGs2QuestQuestModel Return;
    if (QuestGroupModel.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2QuestQuestGroupModelFunctionLibrary::QuestModel] QuestGroupModel parameter specification is missing."))
        return Return;
    }
    if (QuestName == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2QuestQuestGroupModelFunctionLibrary::QuestModel] QuestName parameter specification is missing."))
        return Return;
    }
    Return.Value = QuestGroupModel.Value->QuestModel(
        QuestName
    );
    return Return;
}