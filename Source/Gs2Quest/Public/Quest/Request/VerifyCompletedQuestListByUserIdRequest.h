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
    class FVerifyCompletedQuestListByUserIdRequest;

    class GS2QUEST_API FVerifyCompletedQuestListByUserIdRequest final : public TSharedFromThis<FVerifyCompletedQuestListByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> QuestGroupNameValue;
        TOptional<FString> QuestNameValue;
        TOptional<FString> VerifyTypeValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FVerifyCompletedQuestListByUserIdRequest();
        FVerifyCompletedQuestListByUserIdRequest(
            const FVerifyCompletedQuestListByUserIdRequest& From
        );
        ~FVerifyCompletedQuestListByUserIdRequest() = default;

        TSharedPtr<FVerifyCompletedQuestListByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FVerifyCompletedQuestListByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FVerifyCompletedQuestListByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FVerifyCompletedQuestListByUserIdRequest> WithQuestGroupName(const TOptional<FString> QuestGroupName);
        TSharedPtr<FVerifyCompletedQuestListByUserIdRequest> WithQuestName(const TOptional<FString> QuestName);
        TSharedPtr<FVerifyCompletedQuestListByUserIdRequest> WithVerifyType(const TOptional<FString> VerifyType);
        TSharedPtr<FVerifyCompletedQuestListByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FVerifyCompletedQuestListByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetQuestGroupName() const;
        TOptional<FString> GetQuestName() const;
        TOptional<FString> GetVerifyType() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FVerifyCompletedQuestListByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FVerifyCompletedQuestListByUserIdRequest> FVerifyCompletedQuestListByUserIdRequestPtr;
}