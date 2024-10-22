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

namespace Gs2::Gateway::Request
{
    class FDescribeWebSocketSessionsByUserIdRequest;

    class GS2GATEWAY_API FDescribeWebSocketSessionsByUserIdRequest final : public TSharedFromThis<FDescribeWebSocketSessionsByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> PageTokenValue;
        TOptional<int32> LimitValue;
        TOptional<FString> TimeOffsetTokenValue;
        
    public:
        
        FDescribeWebSocketSessionsByUserIdRequest();
        FDescribeWebSocketSessionsByUserIdRequest(
            const FDescribeWebSocketSessionsByUserIdRequest& From
        );
        ~FDescribeWebSocketSessionsByUserIdRequest() = default;

        TSharedPtr<FDescribeWebSocketSessionsByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDescribeWebSocketSessionsByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDescribeWebSocketSessionsByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FDescribeWebSocketSessionsByUserIdRequest> WithPageToken(const TOptional<FString> PageToken);
        TSharedPtr<FDescribeWebSocketSessionsByUserIdRequest> WithLimit(const TOptional<int32> Limit);
        TSharedPtr<FDescribeWebSocketSessionsByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetPageToken() const;
        TOptional<int32> GetLimit() const;
        FString GetLimitString() const;
        TOptional<FString> GetTimeOffsetToken() const;

        static TSharedPtr<FDescribeWebSocketSessionsByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDescribeWebSocketSessionsByUserIdRequest> FDescribeWebSocketSessionsByUserIdRequestPtr;
}