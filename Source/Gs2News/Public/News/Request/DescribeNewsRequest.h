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

namespace Gs2::News::Request
{
    class FDescribeNewsRequest;

    class GS2NEWS_API FDescribeNewsRequest final : public TSharedFromThis<FDescribeNewsRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AccessTokenValue;
        
    public:
        
        FDescribeNewsRequest();
        FDescribeNewsRequest(
            const FDescribeNewsRequest& From
        );
        ~FDescribeNewsRequest() = default;

        TSharedPtr<FDescribeNewsRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDescribeNewsRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDescribeNewsRequest> WithAccessToken(const TOptional<FString> AccessToken);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAccessToken() const;

        static TSharedPtr<FDescribeNewsRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDescribeNewsRequest> FDescribeNewsRequestPtr;
}