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
    class FQueryExecuteStampTaskLogRequest;

    class GS2LOG_API FQueryExecuteStampTaskLogRequest final : public TSharedFromThis<FQueryExecuteStampTaskLogRequest>
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
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FQueryExecuteStampTaskLogRequest();
        FQueryExecuteStampTaskLogRequest(
            const FQueryExecuteStampTaskLogRequest& From
        );
        ~FQueryExecuteStampTaskLogRequest() = default;

        TSharedPtr<FQueryExecuteStampTaskLogRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FQueryExecuteStampTaskLogRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FQueryExecuteStampTaskLogRequest> WithService(const TOptional<FString> Service);
        TSharedPtr<FQueryExecuteStampTaskLogRequest> WithMethod(const TOptional<FString> Method);
        TSharedPtr<FQueryExecuteStampTaskLogRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FQueryExecuteStampTaskLogRequest> WithAction(const TOptional<FString> Action);
        TSharedPtr<FQueryExecuteStampTaskLogRequest> WithBegin(const TOptional<int64> Begin);
        TSharedPtr<FQueryExecuteStampTaskLogRequest> WithEnd(const TOptional<int64> End);
        TSharedPtr<FQueryExecuteStampTaskLogRequest> WithLongTerm(const TOptional<bool> LongTerm);
        TSharedPtr<FQueryExecuteStampTaskLogRequest> WithPageToken(const TOptional<FString> PageToken);
        TSharedPtr<FQueryExecuteStampTaskLogRequest> WithLimit(const TOptional<int32> Limit);
        TSharedPtr<FQueryExecuteStampTaskLogRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FQueryExecuteStampTaskLogRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

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
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FQueryExecuteStampTaskLogRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FQueryExecuteStampTaskLogRequest> FQueryExecuteStampTaskLogRequestPtr;
}