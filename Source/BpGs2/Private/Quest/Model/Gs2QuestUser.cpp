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
 *
 * deny overwrite
 */

#include "Quest/Model/Gs2QuestUser.h"
#include "Quest/Model/Gs2QuestProgress.h"
#include "Quest/Model/Gs2QuestCompletedQuestList.h"
#include "Core/Model/Gs2AccessToken.h"
#include "Quest/Model/Gs2QuestProgress.h"
#include "Quest/Model/Gs2QuestCompletedQuestList.h"
#include "Core/BpGs2Constant.h"

FGs2QuestOwnProgress UGs2QuestUserFunctionLibrary::OwnProgress(
    FGs2QuestOwnUser User
)
{
    FGs2QuestOwnProgress Return;
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2QuestUserFunctionLibrary::OwnProgress] User parameter specification is missing."))
        return Return;
    }
    Return.Value = User.Value->Progress(
    );
    return Return;
}

FGs2QuestOwnCompletedQuestList UGs2QuestUserFunctionLibrary::OwnCompletedQuestList(
    FGs2QuestOwnUser User,
    FString QuestGroupName
)
{
    FGs2QuestOwnCompletedQuestList Return;
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2QuestUserFunctionLibrary::OwnCompletedQuestList] User parameter specification is missing."))
        return Return;
    }
    if (QuestGroupName == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2QuestUserFunctionLibrary::OwnCompletedQuestList] QuestGroupName parameter specification is missing."))
        return Return;
    }
    Return.Value = User.Value->CompletedQuestList(
        QuestGroupName
    );
    return Return;
}