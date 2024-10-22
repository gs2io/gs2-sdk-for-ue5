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

namespace Gs2::Lock::Request
{
    class FUnlockRequest;

    class GS2LOCK_API FUnlockRequest final : public TSharedFromThis<FUnlockRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> PropertyIdValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> TransactionIdValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FUnlockRequest();
        FUnlockRequest(
            const FUnlockRequest& From
        );
        ~FUnlockRequest() = default;

        TSharedPtr<FUnlockRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FUnlockRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FUnlockRequest> WithPropertyId(const TOptional<FString> PropertyId);
        TSharedPtr<FUnlockRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FUnlockRequest> WithTransactionId(const TOptional<FString> TransactionId);
        TSharedPtr<FUnlockRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetPropertyId() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetTransactionId() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FUnlockRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUnlockRequest> FUnlockRequestPtr;
}