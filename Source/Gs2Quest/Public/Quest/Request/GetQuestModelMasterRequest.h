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
    class FGetQuestModelMasterRequest;

    class GS2QUEST_API FGetQuestModelMasterRequest final : public TSharedFromThis<FGetQuestModelMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> QuestGroupNameValue;
        TOptional<FString> QuestNameValue;
        
    public:
        
        FGetQuestModelMasterRequest();
        FGetQuestModelMasterRequest(
            const FGetQuestModelMasterRequest& From
        );
        ~FGetQuestModelMasterRequest() = default;

        TSharedPtr<FGetQuestModelMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetQuestModelMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetQuestModelMasterRequest> WithQuestGroupName(const TOptional<FString> QuestGroupName);
        TSharedPtr<FGetQuestModelMasterRequest> WithQuestName(const TOptional<FString> QuestName);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetQuestGroupName() const;
        TOptional<FString> GetQuestName() const;

        static TSharedPtr<FGetQuestModelMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetQuestModelMasterRequest> FGetQuestModelMasterRequestPtr;
}