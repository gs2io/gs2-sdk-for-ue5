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

namespace Gs2::Quest::Request
{
    class FGetCompletedQuestListRequest;

    class GS2QUEST_API FGetCompletedQuestListRequest final : public TSharedFromThis<FGetCompletedQuestListRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> QuestGroupNameValue;
        TOptional<FString> AccessTokenValue;
        
    public:
        
        FGetCompletedQuestListRequest();
        FGetCompletedQuestListRequest(
            const FGetCompletedQuestListRequest& From
        );
        ~FGetCompletedQuestListRequest() = default;

        TSharedPtr<FGetCompletedQuestListRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetCompletedQuestListRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetCompletedQuestListRequest> WithQuestGroupName(const TOptional<FString> QuestGroupName);
        TSharedPtr<FGetCompletedQuestListRequest> WithAccessToken(const TOptional<FString> AccessToken);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetQuestGroupName() const;
        TOptional<FString> GetAccessToken() const;

        static TSharedPtr<FGetCompletedQuestListRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetCompletedQuestListRequest, ESPMode::ThreadSafe> FGetCompletedQuestListRequestPtr;
}