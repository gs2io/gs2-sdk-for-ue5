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
    class FVerifyCompletedQuestListRequest;

    class GS2QUEST_API FVerifyCompletedQuestListRequest final : public TSharedFromThis<FVerifyCompletedQuestListRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> QuestGroupNameValue;
        TOptional<FString> QuestNameValue;
        TOptional<FString> VerifyTypeValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FVerifyCompletedQuestListRequest();
        FVerifyCompletedQuestListRequest(
            const FVerifyCompletedQuestListRequest& From
        );
        ~FVerifyCompletedQuestListRequest() = default;

        TSharedPtr<FVerifyCompletedQuestListRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FVerifyCompletedQuestListRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FVerifyCompletedQuestListRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FVerifyCompletedQuestListRequest> WithQuestGroupName(const TOptional<FString> QuestGroupName);
        TSharedPtr<FVerifyCompletedQuestListRequest> WithQuestName(const TOptional<FString> QuestName);
        TSharedPtr<FVerifyCompletedQuestListRequest> WithVerifyType(const TOptional<FString> VerifyType);
        TSharedPtr<FVerifyCompletedQuestListRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetQuestGroupName() const;
        TOptional<FString> GetQuestName() const;
        TOptional<FString> GetVerifyType() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FVerifyCompletedQuestListRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FVerifyCompletedQuestListRequest> FVerifyCompletedQuestListRequestPtr;
}