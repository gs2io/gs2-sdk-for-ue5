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
    class FDescribeEventsRequest;

    class GS2DEPLOY_API FDescribeEventsRequest final : public TSharedFromThis<FDescribeEventsRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> StackNameValue;
        TOptional<FString> PageTokenValue;
        TOptional<int32> LimitValue;
        
    public:
        
        FDescribeEventsRequest();
        FDescribeEventsRequest(
            const FDescribeEventsRequest& From
        );
        ~FDescribeEventsRequest() = default;

        TSharedPtr<FDescribeEventsRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDescribeEventsRequest> WithStackName(const TOptional<FString> StackName);
        TSharedPtr<FDescribeEventsRequest> WithPageToken(const TOptional<FString> PageToken);
        TSharedPtr<FDescribeEventsRequest> WithLimit(const TOptional<int32> Limit);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetStackName() const;
        TOptional<FString> GetPageToken() const;
        TOptional<int32> GetLimit() const;
        FString GetLimitString() const;

        static TSharedPtr<FDescribeEventsRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDescribeEventsRequest, ESPMode::ThreadSafe> FDescribeEventsRequestPtr;
}