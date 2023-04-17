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
    class FAuthenticationRequest;

    class GS2ACCOUNT_API FAuthenticationRequest final : public TSharedFromThis<FAuthenticationRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> KeyIdValue;
        TOptional<FString> PasswordValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FAuthenticationRequest();
        FAuthenticationRequest(
            const FAuthenticationRequest& From
        );
        ~FAuthenticationRequest() = default;

        TSharedPtr<FAuthenticationRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FAuthenticationRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FAuthenticationRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FAuthenticationRequest> WithKeyId(const TOptional<FString> KeyId);
        TSharedPtr<FAuthenticationRequest> WithPassword(const TOptional<FString> Password);
        TSharedPtr<FAuthenticationRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetKeyId() const;
        TOptional<FString> GetPassword() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FAuthenticationRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FAuthenticationRequest, ESPMode::ThreadSafe> FAuthenticationRequestPtr;
}