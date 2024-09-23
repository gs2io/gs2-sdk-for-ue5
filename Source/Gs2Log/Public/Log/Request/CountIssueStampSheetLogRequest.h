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

namespace Gs2::Log::Request
{
    class FCountIssueStampSheetLogRequest;

    class GS2LOG_API FCountIssueStampSheetLogRequest final : public TSharedFromThis<FCountIssueStampSheetLogRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<bool> ServiceValue;
        TOptional<bool> MethodValue;
        TOptional<bool> UserIdValue;
        TOptional<bool> ActionValue;
        TOptional<int64> BeginValue;
        TOptional<int64> EndValue;
        TOptional<bool> LongTermValue;
        TOptional<FString> PageTokenValue;
        TOptional<int32> LimitValue;
        TOptional<FString> TimeOffsetTokenValue;
        
    public:
        
        FCountIssueStampSheetLogRequest();
        FCountIssueStampSheetLogRequest(
            const FCountIssueStampSheetLogRequest& From
        );
        ~FCountIssueStampSheetLogRequest() = default;

        TSharedPtr<FCountIssueStampSheetLogRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FCountIssueStampSheetLogRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FCountIssueStampSheetLogRequest> WithService(const TOptional<bool> Service);
        TSharedPtr<FCountIssueStampSheetLogRequest> WithMethod(const TOptional<bool> Method);
        TSharedPtr<FCountIssueStampSheetLogRequest> WithUserId(const TOptional<bool> UserId);
        TSharedPtr<FCountIssueStampSheetLogRequest> WithAction(const TOptional<bool> Action);
        TSharedPtr<FCountIssueStampSheetLogRequest> WithBegin(const TOptional<int64> Begin);
        TSharedPtr<FCountIssueStampSheetLogRequest> WithEnd(const TOptional<int64> End);
        TSharedPtr<FCountIssueStampSheetLogRequest> WithLongTerm(const TOptional<bool> LongTerm);
        TSharedPtr<FCountIssueStampSheetLogRequest> WithPageToken(const TOptional<FString> PageToken);
        TSharedPtr<FCountIssueStampSheetLogRequest> WithLimit(const TOptional<int32> Limit);
        TSharedPtr<FCountIssueStampSheetLogRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<bool> GetService() const;
        FString GetServiceString() const;
        TOptional<bool> GetMethod() const;
        FString GetMethodString() const;
        TOptional<bool> GetUserId() const;
        FString GetUserIdString() const;
        TOptional<bool> GetAction() const;
        FString GetActionString() const;
        TOptional<int64> GetBegin() const;
        FString GetBeginString() const;
        TOptional<int64> GetEnd() const;
        FString GetEndString() const;
        TOptional<bool> GetLongTerm() const;
        FString GetLongTermString() const;
        TOptional<FString> GetPageToken() const;
        TOptional<int32> GetLimit() const;
        FString GetLimitString() const;
        TOptional<FString> GetTimeOffsetToken() const;

        static TSharedPtr<FCountIssueStampSheetLogRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FCountIssueStampSheetLogRequest, ESPMode::ThreadSafe> FCountIssueStampSheetLogRequestPtr;
}