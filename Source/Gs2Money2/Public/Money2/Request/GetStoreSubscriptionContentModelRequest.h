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
    class FGetStoreSubscriptionContentModelRequest;

    class GS2MONEY2_API FGetStoreSubscriptionContentModelRequest final : public TSharedFromThis<FGetStoreSubscriptionContentModelRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> ContentNameValue;
        
    public:
        
        FGetStoreSubscriptionContentModelRequest();
        FGetStoreSubscriptionContentModelRequest(
            const FGetStoreSubscriptionContentModelRequest& From
        );
        ~FGetStoreSubscriptionContentModelRequest() = default;

        TSharedPtr<FGetStoreSubscriptionContentModelRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetStoreSubscriptionContentModelRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetStoreSubscriptionContentModelRequest> WithContentName(const TOptional<FString> ContentName);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetContentName() const;

        static TSharedPtr<FGetStoreSubscriptionContentModelRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetStoreSubscriptionContentModelRequest> FGetStoreSubscriptionContentModelRequestPtr;
}