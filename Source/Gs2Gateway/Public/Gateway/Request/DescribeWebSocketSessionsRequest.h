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

namespace Gs2::Gateway::Request
{
    class FDescribeWebSocketSessionsRequest;

    class GS2GATEWAY_API FDescribeWebSocketSessionsRequest final : public TSharedFromThis<FDescribeWebSocketSessionsRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> PageTokenValue;
        TOptional<int32> LimitValue;
        
    public:
        
        FDescribeWebSocketSessionsRequest();
        FDescribeWebSocketSessionsRequest(
            const FDescribeWebSocketSessionsRequest& From
        );
        ~FDescribeWebSocketSessionsRequest() = default;

        TSharedPtr<FDescribeWebSocketSessionsRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDescribeWebSocketSessionsRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDescribeWebSocketSessionsRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FDescribeWebSocketSessionsRequest> WithPageToken(const TOptional<FString> PageToken);
        TSharedPtr<FDescribeWebSocketSessionsRequest> WithLimit(const TOptional<int32> Limit);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetPageToken() const;
        TOptional<int32> GetLimit() const;
        FString GetLimitString() const;

        static TSharedPtr<FDescribeWebSocketSessionsRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDescribeWebSocketSessionsRequest, ESPMode::ThreadSafe> FDescribeWebSocketSessionsRequestPtr;
}