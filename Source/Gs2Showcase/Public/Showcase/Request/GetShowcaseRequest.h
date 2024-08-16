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
    class FGetShowcaseRequest;

    class GS2SHOWCASE_API FGetShowcaseRequest final : public TSharedFromThis<FGetShowcaseRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> ShowcaseNameValue;
        TOptional<FString> AccessTokenValue;
        
    public:
        
        FGetShowcaseRequest();
        FGetShowcaseRequest(
            const FGetShowcaseRequest& From
        );
        ~FGetShowcaseRequest() = default;

        TSharedPtr<FGetShowcaseRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetShowcaseRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetShowcaseRequest> WithShowcaseName(const TOptional<FString> ShowcaseName);
        TSharedPtr<FGetShowcaseRequest> WithAccessToken(const TOptional<FString> AccessToken);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetShowcaseName() const;
        TOptional<FString> GetAccessToken() const;

        static TSharedPtr<FGetShowcaseRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetShowcaseRequest> FGetShowcaseRequestPtr;
}