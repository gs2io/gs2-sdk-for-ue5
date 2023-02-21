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
#include "../Model/QuestGroupModelMaster.h"

namespace Gs2::Quest::Result
{
    class GS2QUEST_API FDescribeQuestGroupModelMastersResult final : public TSharedFromThis<FDescribeQuestGroupModelMastersResult>
    {
        TSharedPtr<TArray<TSharedPtr<Model::FQuestGroupModelMaster>>> ItemsValue;
        TOptional<FString> NextPageTokenValue;
        
    public:
        
        FDescribeQuestGroupModelMastersResult();
        FDescribeQuestGroupModelMastersResult(
            const FDescribeQuestGroupModelMastersResult& From
        );
        ~FDescribeQuestGroupModelMastersResult() = default;

        TSharedPtr<FDescribeQuestGroupModelMastersResult> WithItems(const TSharedPtr<TArray<TSharedPtr<Model::FQuestGroupModelMaster>>> Items);
        TSharedPtr<FDescribeQuestGroupModelMastersResult> WithNextPageToken(const TOptional<FString> NextPageToken);

        TSharedPtr<TArray<TSharedPtr<Model::FQuestGroupModelMaster>>> GetItems() const;
        TOptional<FString> GetNextPageToken() const;

        static TSharedPtr<FDescribeQuestGroupModelMastersResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDescribeQuestGroupModelMastersResult, ESPMode::ThreadSafe> FDescribeQuestGroupModelMastersResultPtr;
}