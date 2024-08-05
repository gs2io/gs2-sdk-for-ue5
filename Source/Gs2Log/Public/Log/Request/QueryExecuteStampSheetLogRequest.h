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
    class FQueryExecuteStampSheetLogRequest;

    class GS2LOG_API FQueryExecuteStampSheetLogRequest final : public TSharedFromThis<FQueryExecuteStampSheetLogRequest>
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
        
        FQueryExecuteStampSheetLogRequest();
        FQueryExecuteStampSheetLogRequest(
            const FQueryExecuteStampSheetLogRequest& From
        );
        ~FQueryExecuteStampSheetLogRequest() = default;

        TSharedPtr<FQueryExecuteStampSheetLogRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FQueryExecuteStampSheetLogRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FQueryExecuteStampSheetLogRequest> WithService(const TOptional<FString> Service);
        TSharedPtr<FQueryExecuteStampSheetLogRequest> WithMethod(const TOptional<FString> Method);
        TSharedPtr<FQueryExecuteStampSheetLogRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FQueryExecuteStampSheetLogRequest> WithAction(const TOptional<FString> Action);
        TSharedPtr<FQueryExecuteStampSheetLogRequest> WithBegin(const TOptional<int64> Begin);
        TSharedPtr<FQueryExecuteStampSheetLogRequest> WithEnd(const TOptional<int64> End);
        TSharedPtr<FQueryExecuteStampSheetLogRequest> WithLongTerm(const TOptional<bool> LongTerm);
        TSharedPtr<FQueryExecuteStampSheetLogRequest> WithPageToken(const TOptional<FString> PageToken);
        TSharedPtr<FQueryExecuteStampSheetLogRequest> WithLimit(const TOptional<int32> Limit);
        TSharedPtr<FQueryExecuteStampSheetLogRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FQueryExecuteStampSheetLogRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

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

        static TSharedPtr<FQueryExecuteStampSheetLogRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FQueryExecuteStampSheetLogRequest, ESPMode::ThreadSafe> FQueryExecuteStampSheetLogRequestPtr;
}