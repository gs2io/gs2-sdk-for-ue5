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

namespace Gs2::Showcase::Request
{
    class FDescribeRandomDisplayItemsRequest;

    class GS2SHOWCASE_API FDescribeRandomDisplayItemsRequest final : public TSharedFromThis<FDescribeRandomDisplayItemsRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> ShowcaseNameValue;
        TOptional<FString> AccessTokenValue;
        
    public:
        
        FDescribeRandomDisplayItemsRequest();
        FDescribeRandomDisplayItemsRequest(
            const FDescribeRandomDisplayItemsRequest& From
        );
        ~FDescribeRandomDisplayItemsRequest() = default;

        TSharedPtr<FDescribeRandomDisplayItemsRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDescribeRandomDisplayItemsRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDescribeRandomDisplayItemsRequest> WithShowcaseName(const TOptional<FString> ShowcaseName);
        TSharedPtr<FDescribeRandomDisplayItemsRequest> WithAccessToken(const TOptional<FString> AccessToken);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetShowcaseName() const;
        TOptional<FString> GetAccessToken() const;

        static TSharedPtr<FDescribeRandomDisplayItemsRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDescribeRandomDisplayItemsRequest, ESPMode::ThreadSafe> FDescribeRandomDisplayItemsRequestPtr;
}