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
#include "Dom/JsonObject.h"

namespace Gs2::Quest::Request
{
    class FDescribeQuestModelsRequest;

    class GS2QUEST_API FDescribeQuestModelsRequest final : public TSharedFromThis<FDescribeQuestModelsRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> QuestGroupNameValue;
        
    public:
        
        FDescribeQuestModelsRequest();
        FDescribeQuestModelsRequest(
            const FDescribeQuestModelsRequest& From
        );
        ~FDescribeQuestModelsRequest() = default;

        TSharedPtr<FDescribeQuestModelsRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDescribeQuestModelsRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDescribeQuestModelsRequest> WithQuestGroupName(const TOptional<FString> QuestGroupName);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetQuestGroupName() const;

        static TSharedPtr<FDescribeQuestModelsRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDescribeQuestModelsRequest> FDescribeQuestModelsRequestPtr;
}