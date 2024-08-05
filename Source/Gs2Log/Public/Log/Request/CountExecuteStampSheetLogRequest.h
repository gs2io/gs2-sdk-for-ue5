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
    class FCountExecuteStampSheetLogRequest;

    class GS2LOG_API FCountExecuteStampSheetLogRequest final : public TSharedFromThis<FCountExecuteStampSheetLogRequest>
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
        
        FCountExecuteStampSheetLogRequest();
        FCountExecuteStampSheetLogRequest(
            const FCountExecuteStampSheetLogRequest& From
        );
        ~FCountExecuteStampSheetLogRequest() = default;

        TSharedPtr<FCountExecuteStampSheetLogRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FCountExecuteStampSheetLogRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FCountExecuteStampSheetLogRequest> WithService(const TOptional<bool> Service);
        TSharedPtr<FCountExecuteStampSheetLogRequest> WithMethod(const TOptional<bool> Method);
        TSharedPtr<FCountExecuteStampSheetLogRequest> WithUserId(const TOptional<bool> UserId);
        TSharedPtr<FCountExecuteStampSheetLogRequest> WithAction(const TOptional<bool> Action);
        TSharedPtr<FCountExecuteStampSheetLogRequest> WithBegin(const TOptional<int64> Begin);
        TSharedPtr<FCountExecuteStampSheetLogRequest> WithEnd(const TOptional<int64> End);
        TSharedPtr<FCountExecuteStampSheetLogRequest> WithLongTerm(const TOptional<bool> LongTerm);
        TSharedPtr<FCountExecuteStampSheetLogRequest> WithPageToken(const TOptional<FString> PageToken);
        TSharedPtr<FCountExecuteStampSheetLogRequest> WithLimit(const TOptional<int32> Limit);
        TSharedPtr<FCountExecuteStampSheetLogRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);

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

        static TSharedPtr<FCountExecuteStampSheetLogRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FCountExecuteStampSheetLogRequest, ESPMode::ThreadSafe> FCountExecuteStampSheetLogRequestPtr;
}