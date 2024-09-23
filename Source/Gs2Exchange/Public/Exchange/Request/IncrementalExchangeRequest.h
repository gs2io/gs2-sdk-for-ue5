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
    class FIncrementalExchangeRequest;

    class GS2EXCHANGE_API FIncrementalExchangeRequest final : public TSharedFromThis<FIncrementalExchangeRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> RateNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<int32> CountValue;
        TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> ConfigValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FIncrementalExchangeRequest();
        FIncrementalExchangeRequest(
            const FIncrementalExchangeRequest& From
        );
        ~FIncrementalExchangeRequest() = default;

        TSharedPtr<FIncrementalExchangeRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FIncrementalExchangeRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FIncrementalExchangeRequest> WithRateName(const TOptional<FString> RateName);
        TSharedPtr<FIncrementalExchangeRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FIncrementalExchangeRequest> WithCount(const TOptional<int32> Count);
        TSharedPtr<FIncrementalExchangeRequest> WithConfig(const TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> Config);
        TSharedPtr<FIncrementalExchangeRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetRateName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<int32> GetCount() const;
        FString GetCountString() const;TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> GetConfig() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FIncrementalExchangeRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FIncrementalExchangeRequest, ESPMode::ThreadSafe> FIncrementalExchangeRequestPtr;
}