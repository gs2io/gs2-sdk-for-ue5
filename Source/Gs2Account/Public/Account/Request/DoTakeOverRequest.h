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
    class FDoTakeOverRequest;

    class GS2ACCOUNT_API FDoTakeOverRequest final : public TSharedFromThis<FDoTakeOverRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<int32> TypeValue;
        TOptional<FString> UserIdentifierValue;
        TOptional<FString> PasswordValue;
        
    public:
        
        FDoTakeOverRequest();
        FDoTakeOverRequest(
            const FDoTakeOverRequest& From
        );
        ~FDoTakeOverRequest() = default;

        TSharedPtr<FDoTakeOverRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDoTakeOverRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDoTakeOverRequest> WithType(const TOptional<int32> Type);
        TSharedPtr<FDoTakeOverRequest> WithUserIdentifier(const TOptional<FString> UserIdentifier);
        TSharedPtr<FDoTakeOverRequest> WithPassword(const TOptional<FString> Password);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<int32> GetType() const;
        FString GetTypeString() const;
        TOptional<FString> GetUserIdentifier() const;
        TOptional<FString> GetPassword() const;

        static TSharedPtr<FDoTakeOverRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDoTakeOverRequest, ESPMode::ThreadSafe> FDoTakeOverRequestPtr;
}