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

namespace Gs2::Friend::Request
{
    class FDescribeFollowsRequest;

    class GS2FRIEND_API FDescribeFollowsRequest final : public TSharedFromThis<FDescribeFollowsRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<bool> WithProfileValue;
        TOptional<FString> PageTokenValue;
        TOptional<int32> LimitValue;
        
    public:
        
        FDescribeFollowsRequest();
        FDescribeFollowsRequest(
            const FDescribeFollowsRequest& From
        );
        ~FDescribeFollowsRequest() = default;

        TSharedPtr<FDescribeFollowsRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDescribeFollowsRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDescribeFollowsRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FDescribeFollowsRequest> WithWithProfile(const TOptional<bool> WithProfile);
        TSharedPtr<FDescribeFollowsRequest> WithPageToken(const TOptional<FString> PageToken);
        TSharedPtr<FDescribeFollowsRequest> WithLimit(const TOptional<int32> Limit);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<bool> GetWithProfile() const;
        FString GetWithProfileString() const;
        TOptional<FString> GetPageToken() const;
        TOptional<int32> GetLimit() const;
        FString GetLimitString() const;

        static TSharedPtr<FDescribeFollowsRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDescribeFollowsRequest> FDescribeFollowsRequestPtr;
}