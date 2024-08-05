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
    class FQueryAccessLogWithTelemetryRequest;

    class GS2LOG_API FQueryAccessLogWithTelemetryRequest final : public TSharedFromThis<FQueryAccessLogWithTelemetryRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<int64> BeginValue;
        TOptional<int64> EndValue;
        TOptional<bool> LongTermValue;
        TOptional<FString> PageTokenValue;
        TOptional<int32> LimitValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FQueryAccessLogWithTelemetryRequest();
        FQueryAccessLogWithTelemetryRequest(
            const FQueryAccessLogWithTelemetryRequest& From
        );
        ~FQueryAccessLogWithTelemetryRequest() = default;

        TSharedPtr<FQueryAccessLogWithTelemetryRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FQueryAccessLogWithTelemetryRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FQueryAccessLogWithTelemetryRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FQueryAccessLogWithTelemetryRequest> WithBegin(const TOptional<int64> Begin);
        TSharedPtr<FQueryAccessLogWithTelemetryRequest> WithEnd(const TOptional<int64> End);
        TSharedPtr<FQueryAccessLogWithTelemetryRequest> WithLongTerm(const TOptional<bool> LongTerm);
        TSharedPtr<FQueryAccessLogWithTelemetryRequest> WithPageToken(const TOptional<FString> PageToken);
        TSharedPtr<FQueryAccessLogWithTelemetryRequest> WithLimit(const TOptional<int32> Limit);
        TSharedPtr<FQueryAccessLogWithTelemetryRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FQueryAccessLogWithTelemetryRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
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

        static TSharedPtr<FQueryAccessLogWithTelemetryRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FQueryAccessLogWithTelemetryRequest, ESPMode::ThreadSafe> FQueryAccessLogWithTelemetryRequestPtr;
}