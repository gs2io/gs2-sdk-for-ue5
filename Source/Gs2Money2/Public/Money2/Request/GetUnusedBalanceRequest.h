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

namespace Gs2::Money2::Request
{
    class FGetUnusedBalanceRequest;

    class GS2MONEY2_API FGetUnusedBalanceRequest final : public TSharedFromThis<FGetUnusedBalanceRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> CurrencyValue;
        
    public:
        
        FGetUnusedBalanceRequest();
        FGetUnusedBalanceRequest(
            const FGetUnusedBalanceRequest& From
        );
        ~FGetUnusedBalanceRequest() = default;

        TSharedPtr<FGetUnusedBalanceRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetUnusedBalanceRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetUnusedBalanceRequest> WithCurrency(const TOptional<FString> Currency);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetCurrency() const;

        static TSharedPtr<FGetUnusedBalanceRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetUnusedBalanceRequest, ESPMode::ThreadSafe> FGetUnusedBalanceRequestPtr;
}