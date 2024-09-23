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

namespace Gs2::Enchant::Request
{
    class FGetBalanceParameterStatusRequest;

    class GS2ENCHANT_API FGetBalanceParameterStatusRequest final : public TSharedFromThis<FGetBalanceParameterStatusRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> ParameterNameValue;
        TOptional<FString> PropertyIdValue;
        
    public:
        
        FGetBalanceParameterStatusRequest();
        FGetBalanceParameterStatusRequest(
            const FGetBalanceParameterStatusRequest& From
        );
        ~FGetBalanceParameterStatusRequest() = default;

        TSharedPtr<FGetBalanceParameterStatusRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetBalanceParameterStatusRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetBalanceParameterStatusRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FGetBalanceParameterStatusRequest> WithParameterName(const TOptional<FString> ParameterName);
        TSharedPtr<FGetBalanceParameterStatusRequest> WithPropertyId(const TOptional<FString> PropertyId);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetParameterName() const;
        TOptional<FString> GetPropertyId() const;

        static TSharedPtr<FGetBalanceParameterStatusRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetBalanceParameterStatusRequest, ESPMode::ThreadSafe> FGetBalanceParameterStatusRequestPtr;
}