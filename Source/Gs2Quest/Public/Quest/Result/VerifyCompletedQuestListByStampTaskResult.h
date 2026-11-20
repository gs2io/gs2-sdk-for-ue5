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
#include "../Model/CompletedQuestList.h"

namespace Gs2::Quest::Result
{
    class GS2QUEST_API FVerifyCompletedQuestListByStampTaskResult final : public TSharedFromThis<FVerifyCompletedQuestListByStampTaskResult>
    {
        TSharedPtr<Model::FCompletedQuestList> ItemValue;
        TOptional<FString> NewContextStackValue;
        
    public:
        
        FVerifyCompletedQuestListByStampTaskResult();
        FVerifyCompletedQuestListByStampTaskResult(
            const FVerifyCompletedQuestListByStampTaskResult& From
        );
        ~FVerifyCompletedQuestListByStampTaskResult() = default;

        TSharedPtr<FVerifyCompletedQuestListByStampTaskResult> WithItem(const TSharedPtr<Model::FCompletedQuestList> Item);
        TSharedPtr<FVerifyCompletedQuestListByStampTaskResult> WithNewContextStack(const TOptional<FString> NewContextStack);

        TSharedPtr<Model::FCompletedQuestList> GetItem() const;
        TOptional<FString> GetNewContextStack() const;

        static TSharedPtr<FVerifyCompletedQuestListByStampTaskResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FVerifyCompletedQuestListByStampTaskResult, ESPMode::ThreadSafe> FVerifyCompletedQuestListByStampTaskResultPtr;
}