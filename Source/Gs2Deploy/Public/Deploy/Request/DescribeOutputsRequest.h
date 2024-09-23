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

namespace Gs2::Deploy::Request
{
    class FDescribeOutputsRequest;

    class GS2DEPLOY_API FDescribeOutputsRequest final : public TSharedFromThis<FDescribeOutputsRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> StackNameValue;
        TOptional<FString> PageTokenValue;
        TOptional<int32> LimitValue;
        
    public:
        
        FDescribeOutputsRequest();
        FDescribeOutputsRequest(
            const FDescribeOutputsRequest& From
        );
        ~FDescribeOutputsRequest() = default;

        TSharedPtr<FDescribeOutputsRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDescribeOutputsRequest> WithStackName(const TOptional<FString> StackName);
        TSharedPtr<FDescribeOutputsRequest> WithPageToken(const TOptional<FString> PageToken);
        TSharedPtr<FDescribeOutputsRequest> WithLimit(const TOptional<int32> Limit);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetStackName() const;
        TOptional<FString> GetPageToken() const;
        TOptional<int32> GetLimit() const;
        FString GetLimitString() const;

        static TSharedPtr<FDescribeOutputsRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDescribeOutputsRequest, ESPMode::ThreadSafe> FDescribeOutputsRequestPtr;
}