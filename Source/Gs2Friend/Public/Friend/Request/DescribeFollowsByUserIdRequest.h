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

namespace Gs2::Friend::Request
{
    class FDescribeFollowsByUserIdRequest;

    class GS2FRIEND_API FDescribeFollowsByUserIdRequest final : public TSharedFromThis<FDescribeFollowsByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<bool> WithProfileValue;
        TOptional<FString> PageTokenValue;
        TOptional<int32> LimitValue;
        TOptional<FString> TimeOffsetTokenValue;
        
    public:
        
        FDescribeFollowsByUserIdRequest();
        FDescribeFollowsByUserIdRequest(
            const FDescribeFollowsByUserIdRequest& From
        );
        ~FDescribeFollowsByUserIdRequest() = default;

        TSharedPtr<FDescribeFollowsByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDescribeFollowsByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDescribeFollowsByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FDescribeFollowsByUserIdRequest> WithWithProfile(const TOptional<bool> WithProfile);
        TSharedPtr<FDescribeFollowsByUserIdRequest> WithPageToken(const TOptional<FString> PageToken);
        TSharedPtr<FDescribeFollowsByUserIdRequest> WithLimit(const TOptional<int32> Limit);
        TSharedPtr<FDescribeFollowsByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<bool> GetWithProfile() const;
        FString GetWithProfileString() const;
        TOptional<FString> GetPageToken() const;
        TOptional<int32> GetLimit() const;
        FString GetLimitString() const;
        TOptional<FString> GetTimeOffsetToken() const;

        static TSharedPtr<FDescribeFollowsByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDescribeFollowsByUserIdRequest, ESPMode::ThreadSafe> FDescribeFollowsByUserIdRequestPtr;
}