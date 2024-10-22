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

namespace Gs2::Log::Request
{
    class FQueryIssueStampSheetLogRequest;

    class GS2LOG_API FQueryIssueStampSheetLogRequest final : public TSharedFromThis<FQueryIssueStampSheetLogRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> ServiceValue;
        TOptional<FString> MethodValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> ActionValue;
        TOptional<int64> BeginValue;
        TOptional<int64> EndValue;
        TOptional<bool> LongTermValue;
        TOptional<FString> PageTokenValue;
        TOptional<int32> LimitValue;
        TOptional<FString> TimeOffsetTokenValue;
        
    public:
        
        FQueryIssueStampSheetLogRequest();
        FQueryIssueStampSheetLogRequest(
            const FQueryIssueStampSheetLogRequest& From
        );
        ~FQueryIssueStampSheetLogRequest() = default;

        TSharedPtr<FQueryIssueStampSheetLogRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FQueryIssueStampSheetLogRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FQueryIssueStampSheetLogRequest> WithService(const TOptional<FString> Service);
        TSharedPtr<FQueryIssueStampSheetLogRequest> WithMethod(const TOptional<FString> Method);
        TSharedPtr<FQueryIssueStampSheetLogRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FQueryIssueStampSheetLogRequest> WithAction(const TOptional<FString> Action);
        TSharedPtr<FQueryIssueStampSheetLogRequest> WithBegin(const TOptional<int64> Begin);
        TSharedPtr<FQueryIssueStampSheetLogRequest> WithEnd(const TOptional<int64> End);
        TSharedPtr<FQueryIssueStampSheetLogRequest> WithLongTerm(const TOptional<bool> LongTerm);
        TSharedPtr<FQueryIssueStampSheetLogRequest> WithPageToken(const TOptional<FString> PageToken);
        TSharedPtr<FQueryIssueStampSheetLogRequest> WithLimit(const TOptional<int32> Limit);
        TSharedPtr<FQueryIssueStampSheetLogRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetService() const;
        TOptional<FString> GetMethod() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetAction() const;
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

        static TSharedPtr<FQueryIssueStampSheetLogRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FQueryIssueStampSheetLogRequest> FQueryIssueStampSheetLogRequestPtr;
}