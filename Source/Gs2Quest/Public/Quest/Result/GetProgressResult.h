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

#pragma once

#include "CoreMinimal.h"
#include "../Model/Progress.h"
#include "../Model/QuestGroupModel.h"
#include "../Model/QuestModel.h"

namespace Gs2::Quest::Result
{
    class GS2QUEST_API FGetProgressResult final : public TSharedFromThis<FGetProgressResult>
    {
        TSharedPtr<Model::FProgress> ItemValue;
        TSharedPtr<Model::FQuestGroupModel> QuestGroupValue;
        TSharedPtr<Model::FQuestModel> QuestValue;
        
    public:
        
        FGetProgressResult();
        FGetProgressResult(
            const FGetProgressResult& From
        );
        ~FGetProgressResult() = default;

        TSharedPtr<FGetProgressResult> WithItem(const TSharedPtr<Model::FProgress> Item);
        TSharedPtr<FGetProgressResult> WithQuestGroup(const TSharedPtr<Model::FQuestGroupModel> QuestGroup);
        TSharedPtr<FGetProgressResult> WithQuest(const TSharedPtr<Model::FQuestModel> Quest);

        TSharedPtr<Model::FProgress> GetItem() const;
        TSharedPtr<Model::FQuestGroupModel> GetQuestGroup() const;
        TSharedPtr<Model::FQuestModel> GetQuest() const;

        static TSharedPtr<FGetProgressResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetProgressResult, ESPMode::ThreadSafe> FGetProgressResultPtr;
}