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
    class FReDrawBalanceParameterStatusByUserIdRequest;

    class GS2ENCHANT_API FReDrawBalanceParameterStatusByUserIdRequest final : public TSharedFromThis<FReDrawBalanceParameterStatusByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> ParameterNameValue;
        TOptional<FString> PropertyIdValue;
        TSharedPtr<TArray<FString>> FixedParameterNamesValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FReDrawBalanceParameterStatusByUserIdRequest();
        FReDrawBalanceParameterStatusByUserIdRequest(
            const FReDrawBalanceParameterStatusByUserIdRequest& From
        );
        ~FReDrawBalanceParameterStatusByUserIdRequest() = default;

        TSharedPtr<FReDrawBalanceParameterStatusByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FReDrawBalanceParameterStatusByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FReDrawBalanceParameterStatusByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FReDrawBalanceParameterStatusByUserIdRequest> WithParameterName(const TOptional<FString> ParameterName);
        TSharedPtr<FReDrawBalanceParameterStatusByUserIdRequest> WithPropertyId(const TOptional<FString> PropertyId);
        TSharedPtr<FReDrawBalanceParameterStatusByUserIdRequest> WithFixedParameterNames(
            const TSharedPtr<TArray<FString>> FixedParameterNames);
        TSharedPtr<FReDrawBalanceParameterStatusByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetParameterName() const;
        TOptional<FString> GetPropertyId() const;
        TSharedPtr<TArray<FString>> GetFixedParameterNames() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FReDrawBalanceParameterStatusByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FReDrawBalanceParameterStatusByUserIdRequest, ESPMode::ThreadSafe> FReDrawBalanceParameterStatusByUserIdRequestPtr;
}