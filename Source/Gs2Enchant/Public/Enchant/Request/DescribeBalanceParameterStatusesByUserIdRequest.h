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

namespace Gs2::Enchant::Request
{
    class FDescribeBalanceParameterStatusesByUserIdRequest;

    class GS2ENCHANT_API FDescribeBalanceParameterStatusesByUserIdRequest final : public TSharedFromThis<FDescribeBalanceParameterStatusesByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> ParameterNameValue;
        TOptional<FString> PageTokenValue;
        TOptional<int32> LimitValue;
        
    public:
        
        FDescribeBalanceParameterStatusesByUserIdRequest();
        FDescribeBalanceParameterStatusesByUserIdRequest(
            const FDescribeBalanceParameterStatusesByUserIdRequest& From
        );
        ~FDescribeBalanceParameterStatusesByUserIdRequest() = default;

        TSharedPtr<FDescribeBalanceParameterStatusesByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDescribeBalanceParameterStatusesByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDescribeBalanceParameterStatusesByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FDescribeBalanceParameterStatusesByUserIdRequest> WithParameterName(const TOptional<FString> ParameterName);
        TSharedPtr<FDescribeBalanceParameterStatusesByUserIdRequest> WithPageToken(const TOptional<FString> PageToken);
        TSharedPtr<FDescribeBalanceParameterStatusesByUserIdRequest> WithLimit(const TOptional<int32> Limit);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetParameterName() const;
        TOptional<FString> GetPageToken() const;
        TOptional<int32> GetLimit() const;
        FString GetLimitString() const;

        static TSharedPtr<FDescribeBalanceParameterStatusesByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDescribeBalanceParameterStatusesByUserIdRequest, ESPMode::ThreadSafe> FDescribeBalanceParameterStatusesByUserIdRequestPtr;
}