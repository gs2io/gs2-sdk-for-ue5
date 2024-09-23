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

namespace Gs2::Account::Request
{
    class FDoTakeOverOpenIdConnectRequest;

    class GS2ACCOUNT_API FDoTakeOverOpenIdConnectRequest final : public TSharedFromThis<FDoTakeOverOpenIdConnectRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<int32> TypeValue;
        TOptional<FString> IdTokenValue;
        
    public:
        
        FDoTakeOverOpenIdConnectRequest();
        FDoTakeOverOpenIdConnectRequest(
            const FDoTakeOverOpenIdConnectRequest& From
        );
        ~FDoTakeOverOpenIdConnectRequest() = default;

        TSharedPtr<FDoTakeOverOpenIdConnectRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDoTakeOverOpenIdConnectRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDoTakeOverOpenIdConnectRequest> WithType(const TOptional<int32> Type);
        TSharedPtr<FDoTakeOverOpenIdConnectRequest> WithIdToken(const TOptional<FString> IdToken);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<int32> GetType() const;
        FString GetTypeString() const;
        TOptional<FString> GetIdToken() const;

        static TSharedPtr<FDoTakeOverOpenIdConnectRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDoTakeOverOpenIdConnectRequest, ESPMode::ThreadSafe> FDoTakeOverOpenIdConnectRequestPtr;
}