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

namespace Gs2::SkillTree::Request
{
    class FDescribeStatusesRequest;

    class GS2SKILLTREE_API FDescribeStatusesRequest final : public TSharedFromThis<FDescribeStatusesRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> PageTokenValue;
        TOptional<int32> LimitValue;
        
    public:
        
        FDescribeStatusesRequest();
        FDescribeStatusesRequest(
            const FDescribeStatusesRequest& From
        );
        ~FDescribeStatusesRequest() = default;

        TSharedPtr<FDescribeStatusesRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDescribeStatusesRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDescribeStatusesRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FDescribeStatusesRequest> WithPageToken(const TOptional<FString> PageToken);
        TSharedPtr<FDescribeStatusesRequest> WithLimit(const TOptional<int32> Limit);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetPageToken() const;
        TOptional<int32> GetLimit() const;
        FString GetLimitString() const;

        static TSharedPtr<FDescribeStatusesRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDescribeStatusesRequest, ESPMode::ThreadSafe> FDescribeStatusesRequestPtr;
}