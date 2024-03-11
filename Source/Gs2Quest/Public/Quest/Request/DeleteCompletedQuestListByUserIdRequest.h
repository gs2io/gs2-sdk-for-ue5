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
    class FDeleteCompletedQuestListByUserIdRequest;

    class GS2QUEST_API FDeleteCompletedQuestListByUserIdRequest final : public TSharedFromThis<FDeleteCompletedQuestListByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> QuestGroupNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FDeleteCompletedQuestListByUserIdRequest();
        FDeleteCompletedQuestListByUserIdRequest(
            const FDeleteCompletedQuestListByUserIdRequest& From
        );
        ~FDeleteCompletedQuestListByUserIdRequest() = default;

        TSharedPtr<FDeleteCompletedQuestListByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDeleteCompletedQuestListByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDeleteCompletedQuestListByUserIdRequest> WithQuestGroupName(const TOptional<FString> QuestGroupName);
        TSharedPtr<FDeleteCompletedQuestListByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FDeleteCompletedQuestListByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FDeleteCompletedQuestListByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetQuestGroupName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FDeleteCompletedQuestListByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDeleteCompletedQuestListByUserIdRequest, ESPMode::ThreadSafe> FDeleteCompletedQuestListByUserIdRequestPtr;
}