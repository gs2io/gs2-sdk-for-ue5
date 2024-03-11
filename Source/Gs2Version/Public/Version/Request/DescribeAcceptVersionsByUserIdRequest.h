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

namespace Gs2::Version::Request
{
    class FDescribeAcceptVersionsByUserIdRequest;

    class GS2VERSION_API FDescribeAcceptVersionsByUserIdRequest final : public TSharedFromThis<FDescribeAcceptVersionsByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> PageTokenValue;
        TOptional<int32> LimitValue;
        TOptional<FString> TimeOffsetTokenValue;
        
    public:
        
        FDescribeAcceptVersionsByUserIdRequest();
        FDescribeAcceptVersionsByUserIdRequest(
            const FDescribeAcceptVersionsByUserIdRequest& From
        );
        ~FDescribeAcceptVersionsByUserIdRequest() = default;

        TSharedPtr<FDescribeAcceptVersionsByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDescribeAcceptVersionsByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDescribeAcceptVersionsByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FDescribeAcceptVersionsByUserIdRequest> WithPageToken(const TOptional<FString> PageToken);
        TSharedPtr<FDescribeAcceptVersionsByUserIdRequest> WithLimit(const TOptional<int32> Limit);
        TSharedPtr<FDescribeAcceptVersionsByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetPageToken() const;
        TOptional<int32> GetLimit() const;
        FString GetLimitString() const;
        TOptional<FString> GetTimeOffsetToken() const;

        static TSharedPtr<FDescribeAcceptVersionsByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDescribeAcceptVersionsByUserIdRequest, ESPMode::ThreadSafe> FDescribeAcceptVersionsByUserIdRequestPtr;
}