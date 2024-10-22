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
    class FCountAccessLogRequest;

    class GS2LOG_API FCountAccessLogRequest final : public TSharedFromThis<FCountAccessLogRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<bool> ServiceValue;
        TOptional<bool> MethodValue;
        TOptional<bool> UserIdValue;
        TOptional<int64> BeginValue;
        TOptional<int64> EndValue;
        TOptional<bool> LongTermValue;
        TOptional<FString> PageTokenValue;
        TOptional<int32> LimitValue;
        TOptional<FString> TimeOffsetTokenValue;
        
    public:
        
        FCountAccessLogRequest();
        FCountAccessLogRequest(
            const FCountAccessLogRequest& From
        );
        ~FCountAccessLogRequest() = default;

        TSharedPtr<FCountAccessLogRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FCountAccessLogRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FCountAccessLogRequest> WithService(const TOptional<bool> Service);
        TSharedPtr<FCountAccessLogRequest> WithMethod(const TOptional<bool> Method);
        TSharedPtr<FCountAccessLogRequest> WithUserId(const TOptional<bool> UserId);
        TSharedPtr<FCountAccessLogRequest> WithBegin(const TOptional<int64> Begin);
        TSharedPtr<FCountAccessLogRequest> WithEnd(const TOptional<int64> End);
        TSharedPtr<FCountAccessLogRequest> WithLongTerm(const TOptional<bool> LongTerm);
        TSharedPtr<FCountAccessLogRequest> WithPageToken(const TOptional<FString> PageToken);
        TSharedPtr<FCountAccessLogRequest> WithLimit(const TOptional<int32> Limit);
        TSharedPtr<FCountAccessLogRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<bool> GetService() const;
        FString GetServiceString() const;
        TOptional<bool> GetMethod() const;
        FString GetMethodString() const;
        TOptional<bool> GetUserId() const;
        FString GetUserIdString() const;
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

        static TSharedPtr<FCountAccessLogRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FCountAccessLogRequest> FCountAccessLogRequestPtr;
}