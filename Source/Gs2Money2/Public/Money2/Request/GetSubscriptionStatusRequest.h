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

namespace Gs2::Money2::Request
{
    class FGetSubscriptionStatusRequest;

    class GS2MONEY2_API FGetSubscriptionStatusRequest final : public TSharedFromThis<FGetSubscriptionStatusRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> ContentNameValue;
        
    public:
        
        FGetSubscriptionStatusRequest();
        FGetSubscriptionStatusRequest(
            const FGetSubscriptionStatusRequest& From
        );
        ~FGetSubscriptionStatusRequest() = default;

        TSharedPtr<FGetSubscriptionStatusRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetSubscriptionStatusRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetSubscriptionStatusRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FGetSubscriptionStatusRequest> WithContentName(const TOptional<FString> ContentName);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetContentName() const;

        static TSharedPtr<FGetSubscriptionStatusRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetSubscriptionStatusRequest> FGetSubscriptionStatusRequestPtr;
}