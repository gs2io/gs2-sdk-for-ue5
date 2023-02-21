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
#include "../Model/QuestModel.h"

namespace Gs2::Quest::Result
{
    class GS2QUEST_API FGetQuestModelResult final : public TSharedFromThis<FGetQuestModelResult>
    {
        TSharedPtr<Model::FQuestModel> ItemValue;
        
    public:
        
        FGetQuestModelResult();
        FGetQuestModelResult(
            const FGetQuestModelResult& From
        );
        ~FGetQuestModelResult() = default;

        TSharedPtr<FGetQuestModelResult> WithItem(const TSharedPtr<Model::FQuestModel> Item);

        TSharedPtr<Model::FQuestModel> GetItem() const;

        static TSharedPtr<FGetQuestModelResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetQuestModelResult, ESPMode::ThreadSafe> FGetQuestModelResultPtr;
}