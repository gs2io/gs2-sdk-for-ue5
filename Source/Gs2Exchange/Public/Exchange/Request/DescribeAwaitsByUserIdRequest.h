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

namespace Gs2::Exchange::Request
{
    class FDescribeAwaitsByUserIdRequest;

    class GS2EXCHANGE_API FDescribeAwaitsByUserIdRequest final : public TSharedFromThis<FDescribeAwaitsByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> RateNameValue;
        TOptional<FString> PageTokenValue;
        TOptional<int32> LimitValue;
        TOptional<FString> TimeOffsetTokenValue;
        
    public:
        
        FDescribeAwaitsByUserIdRequest();
        FDescribeAwaitsByUserIdRequest(
            const FDescribeAwaitsByUserIdRequest& From
        );
        ~FDescribeAwaitsByUserIdRequest() = default;

        TSharedPtr<FDescribeAwaitsByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDescribeAwaitsByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDescribeAwaitsByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FDescribeAwaitsByUserIdRequest> WithRateName(const TOptional<FString> RateName);
        TSharedPtr<FDescribeAwaitsByUserIdRequest> WithPageToken(const TOptional<FString> PageToken);
        TSharedPtr<FDescribeAwaitsByUserIdRequest> WithLimit(const TOptional<int32> Limit);
        TSharedPtr<FDescribeAwaitsByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetRateName() const;
        TOptional<FString> GetPageToken() const;
        TOptional<int32> GetLimit() const;
        FString GetLimitString() const;
        TOptional<FString> GetTimeOffsetToken() const;

        static TSharedPtr<FDescribeAwaitsByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDescribeAwaitsByUserIdRequest> FDescribeAwaitsByUserIdRequestPtr;
}