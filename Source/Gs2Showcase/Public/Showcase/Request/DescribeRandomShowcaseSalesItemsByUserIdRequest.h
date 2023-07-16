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
    class FDescribeRandomShowcaseSalesItemsByUserIdRequest;

    class GS2SHOWCASE_API FDescribeRandomShowcaseSalesItemsByUserIdRequest final : public TSharedFromThis<FDescribeRandomShowcaseSalesItemsByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> ShowcaseNameValue;
        TOptional<FString> UserIdValue;
        
    public:
        
        FDescribeRandomShowcaseSalesItemsByUserIdRequest();
        FDescribeRandomShowcaseSalesItemsByUserIdRequest(
            const FDescribeRandomShowcaseSalesItemsByUserIdRequest& From
        );
        ~FDescribeRandomShowcaseSalesItemsByUserIdRequest() = default;

        TSharedPtr<FDescribeRandomShowcaseSalesItemsByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDescribeRandomShowcaseSalesItemsByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDescribeRandomShowcaseSalesItemsByUserIdRequest> WithShowcaseName(const TOptional<FString> ShowcaseName);
        TSharedPtr<FDescribeRandomShowcaseSalesItemsByUserIdRequest> WithUserId(const TOptional<FString> UserId);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetShowcaseName() const;
        TOptional<FString> GetUserId() const;

        static TSharedPtr<FDescribeRandomShowcaseSalesItemsByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDescribeRandomShowcaseSalesItemsByUserIdRequest, ESPMode::ThreadSafe> FDescribeRandomShowcaseSalesItemsByUserIdRequestPtr;
}