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
#include "../Model/ScopedValue.h"

namespace Gs2::Mission::Request
{
    class FResetCounterRequest;

    class GS2MISSION_API FResetCounterRequest final : public TSharedFromThis<FResetCounterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> CounterNameValue;
        TSharedPtr<TArray<TSharedPtr<Model::FScopedValue>>> ScopesValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FResetCounterRequest();
        FResetCounterRequest(
            const FResetCounterRequest& From
        );
        ~FResetCounterRequest() = default;

        TSharedPtr<FResetCounterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FResetCounterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FResetCounterRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FResetCounterRequest> WithCounterName(const TOptional<FString> CounterName);
        TSharedPtr<FResetCounterRequest> WithScopes(const TSharedPtr<TArray<TSharedPtr<Model::FScopedValue>>> Scopes);
        TSharedPtr<FResetCounterRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetCounterName() const;TSharedPtr<TArray<TSharedPtr<Model::FScopedValue>>> GetScopes() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FResetCounterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FResetCounterRequest> FResetCounterRequestPtr;
}