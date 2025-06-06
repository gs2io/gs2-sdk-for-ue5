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

namespace Gs2::Showcase::Request
{
    class FGetRandomDisplayItemRequest;

    class GS2SHOWCASE_API FGetRandomDisplayItemRequest final : public TSharedFromThis<FGetRandomDisplayItemRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> ShowcaseNameValue;
        TOptional<FString> DisplayItemNameValue;
        TOptional<FString> AccessTokenValue;
        
    public:
        
        FGetRandomDisplayItemRequest();
        FGetRandomDisplayItemRequest(
            const FGetRandomDisplayItemRequest& From
        );
        ~FGetRandomDisplayItemRequest() = default;

        TSharedPtr<FGetRandomDisplayItemRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetRandomDisplayItemRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetRandomDisplayItemRequest> WithShowcaseName(const TOptional<FString> ShowcaseName);
        TSharedPtr<FGetRandomDisplayItemRequest> WithDisplayItemName(const TOptional<FString> DisplayItemName);
        TSharedPtr<FGetRandomDisplayItemRequest> WithAccessToken(const TOptional<FString> AccessToken);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetShowcaseName() const;
        TOptional<FString> GetDisplayItemName() const;
        TOptional<FString> GetAccessToken() const;

        static TSharedPtr<FGetRandomDisplayItemRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetRandomDisplayItemRequest> FGetRandomDisplayItemRequestPtr;
}