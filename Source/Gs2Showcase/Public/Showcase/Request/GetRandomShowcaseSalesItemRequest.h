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
    class FGetRandomShowcaseSalesItemRequest;

    class GS2SHOWCASE_API FGetRandomShowcaseSalesItemRequest final : public TSharedFromThis<FGetRandomShowcaseSalesItemRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> ShowcaseNameValue;
        TOptional<FString> DisplayItemNameValue;
        TOptional<FString> AccessTokenValue;
        
    public:
        
        FGetRandomShowcaseSalesItemRequest();
        FGetRandomShowcaseSalesItemRequest(
            const FGetRandomShowcaseSalesItemRequest& From
        );
        ~FGetRandomShowcaseSalesItemRequest() = default;

        TSharedPtr<FGetRandomShowcaseSalesItemRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetRandomShowcaseSalesItemRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetRandomShowcaseSalesItemRequest> WithShowcaseName(const TOptional<FString> ShowcaseName);
        TSharedPtr<FGetRandomShowcaseSalesItemRequest> WithDisplayItemName(const TOptional<FString> DisplayItemName);
        TSharedPtr<FGetRandomShowcaseSalesItemRequest> WithAccessToken(const TOptional<FString> AccessToken);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetShowcaseName() const;
        TOptional<FString> GetDisplayItemName() const;
        TOptional<FString> GetAccessToken() const;

        static TSharedPtr<FGetRandomShowcaseSalesItemRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetRandomShowcaseSalesItemRequest, ESPMode::ThreadSafe> FGetRandomShowcaseSalesItemRequestPtr;
}