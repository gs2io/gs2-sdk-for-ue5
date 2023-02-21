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

namespace Gs2::Identifier::Request
{
    class FDescribePasswordsRequest;

    class GS2IDENTIFIER_API FDescribePasswordsRequest final : public TSharedFromThis<FDescribePasswordsRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> UserNameValue;
        TOptional<FString> PageTokenValue;
        TOptional<int32> LimitValue;
        
    public:
        
        FDescribePasswordsRequest();
        FDescribePasswordsRequest(
            const FDescribePasswordsRequest& From
        );
        ~FDescribePasswordsRequest() = default;

        TSharedPtr<FDescribePasswordsRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDescribePasswordsRequest> WithUserName(const TOptional<FString> UserName);
        TSharedPtr<FDescribePasswordsRequest> WithPageToken(const TOptional<FString> PageToken);
        TSharedPtr<FDescribePasswordsRequest> WithLimit(const TOptional<int32> Limit);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetUserName() const;
        TOptional<FString> GetPageToken() const;
        TOptional<int32> GetLimit() const;
        FString GetLimitString() const;

        static TSharedPtr<FDescribePasswordsRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDescribePasswordsRequest, ESPMode::ThreadSafe> FDescribePasswordsRequestPtr;
}