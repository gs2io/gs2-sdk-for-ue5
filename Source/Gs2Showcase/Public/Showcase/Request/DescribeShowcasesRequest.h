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
    class FDescribeShowcasesRequest;

    class GS2SHOWCASE_API FDescribeShowcasesRequest final : public TSharedFromThis<FDescribeShowcasesRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AccessTokenValue;
        
    public:
        
        FDescribeShowcasesRequest();
        FDescribeShowcasesRequest(
            const FDescribeShowcasesRequest& From
        );
        ~FDescribeShowcasesRequest() = default;

        TSharedPtr<FDescribeShowcasesRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDescribeShowcasesRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDescribeShowcasesRequest> WithAccessToken(const TOptional<FString> AccessToken);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAccessToken() const;

        static TSharedPtr<FDescribeShowcasesRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDescribeShowcasesRequest, ESPMode::ThreadSafe> FDescribeShowcasesRequestPtr;
}