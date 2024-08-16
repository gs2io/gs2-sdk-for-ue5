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
    class FDeleteQuestModelMasterRequest;

    class GS2QUEST_API FDeleteQuestModelMasterRequest final : public TSharedFromThis<FDeleteQuestModelMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> QuestGroupNameValue;
        TOptional<FString> QuestNameValue;
        
    public:
        
        FDeleteQuestModelMasterRequest();
        FDeleteQuestModelMasterRequest(
            const FDeleteQuestModelMasterRequest& From
        );
        ~FDeleteQuestModelMasterRequest() = default;

        TSharedPtr<FDeleteQuestModelMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDeleteQuestModelMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDeleteQuestModelMasterRequest> WithQuestGroupName(const TOptional<FString> QuestGroupName);
        TSharedPtr<FDeleteQuestModelMasterRequest> WithQuestName(const TOptional<FString> QuestName);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetQuestGroupName() const;
        TOptional<FString> GetQuestName() const;

        static TSharedPtr<FDeleteQuestModelMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDeleteQuestModelMasterRequest> FDeleteQuestModelMasterRequestPtr;
}