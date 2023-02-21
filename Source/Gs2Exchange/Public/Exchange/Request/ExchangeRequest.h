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
    class FExchangeRequest;

    class GS2EXCHANGE_API FExchangeRequest final : public TSharedFromThis<FExchangeRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> RateNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<int32> CountValue;
        TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> ConfigValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FExchangeRequest();
        FExchangeRequest(
            const FExchangeRequest& From
        );
        ~FExchangeRequest() = default;

        TSharedPtr<FExchangeRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FExchangeRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FExchangeRequest> WithRateName(const TOptional<FString> RateName);
        TSharedPtr<FExchangeRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FExchangeRequest> WithCount(const TOptional<int32> Count);
        TSharedPtr<FExchangeRequest> WithConfig(const TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> Config);
        TSharedPtr<FExchangeRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetRateName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<int32> GetCount() const;
        FString GetCountString() const;TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> GetConfig() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FExchangeRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FExchangeRequest, ESPMode::ThreadSafe> FExchangeRequestPtr;
}