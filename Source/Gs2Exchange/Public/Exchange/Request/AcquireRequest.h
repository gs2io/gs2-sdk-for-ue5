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
#include "../Model/Config.h"

namespace Gs2::Exchange::Request
{
    class FAcquireRequest;

    class GS2EXCHANGE_API FAcquireRequest final : public TSharedFromThis<FAcquireRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> AwaitNameValue;
        TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> ConfigValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FAcquireRequest();
        FAcquireRequest(
            const FAcquireRequest& From
        );
        ~FAcquireRequest() = default;

        TSharedPtr<FAcquireRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FAcquireRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FAcquireRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FAcquireRequest> WithAwaitName(const TOptional<FString> AwaitName);
        TSharedPtr<FAcquireRequest> WithConfig(const TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> Config);
        TSharedPtr<FAcquireRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetAwaitName() const;TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> GetConfig() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FAcquireRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FAcquireRequest, ESPMode::ThreadSafe> FAcquireRequestPtr;
}