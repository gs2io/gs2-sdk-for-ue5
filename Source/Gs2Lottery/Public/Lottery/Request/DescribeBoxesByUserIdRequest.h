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

namespace Gs2::Lottery::Request
{
    class FDescribeBoxesByUserIdRequest;

    class GS2LOTTERY_API FDescribeBoxesByUserIdRequest final : public TSharedFromThis<FDescribeBoxesByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> PageTokenValue;
        TOptional<int32> LimitValue;
        
    public:
        
        FDescribeBoxesByUserIdRequest();
        FDescribeBoxesByUserIdRequest(
            const FDescribeBoxesByUserIdRequest& From
        );
        ~FDescribeBoxesByUserIdRequest() = default;

        TSharedPtr<FDescribeBoxesByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDescribeBoxesByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDescribeBoxesByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FDescribeBoxesByUserIdRequest> WithPageToken(const TOptional<FString> PageToken);
        TSharedPtr<FDescribeBoxesByUserIdRequest> WithLimit(const TOptional<int32> Limit);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetPageToken() const;
        TOptional<int32> GetLimit() const;
        FString GetLimitString() const;

        static TSharedPtr<FDescribeBoxesByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDescribeBoxesByUserIdRequest, ESPMode::ThreadSafe> FDescribeBoxesByUserIdRequestPtr;
}