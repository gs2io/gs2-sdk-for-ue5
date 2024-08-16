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
    class FGetCompletedQuestListByUserIdRequest;

    class GS2QUEST_API FGetCompletedQuestListByUserIdRequest final : public TSharedFromThis<FGetCompletedQuestListByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> QuestGroupNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> TimeOffsetTokenValue;
        
    public:
        
        FGetCompletedQuestListByUserIdRequest();
        FGetCompletedQuestListByUserIdRequest(
            const FGetCompletedQuestListByUserIdRequest& From
        );
        ~FGetCompletedQuestListByUserIdRequest() = default;

        TSharedPtr<FGetCompletedQuestListByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetCompletedQuestListByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetCompletedQuestListByUserIdRequest> WithQuestGroupName(const TOptional<FString> QuestGroupName);
        TSharedPtr<FGetCompletedQuestListByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FGetCompletedQuestListByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetQuestGroupName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetTimeOffsetToken() const;

        static TSharedPtr<FGetCompletedQuestListByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetCompletedQuestListByUserIdRequest> FGetCompletedQuestListByUserIdRequestPtr;
}