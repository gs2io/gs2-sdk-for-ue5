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

namespace Gs2::Lock::Request
{
    class FLockRequest;

    class GS2LOCK_API FLockRequest final : public TSharedFromThis<FLockRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> PropertyIdValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> TransactionIdValue;
        TOptional<int64> TtlValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FLockRequest();
        FLockRequest(
            const FLockRequest& From
        );
        ~FLockRequest() = default;

        TSharedPtr<FLockRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FLockRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FLockRequest> WithPropertyId(const TOptional<FString> PropertyId);
        TSharedPtr<FLockRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FLockRequest> WithTransactionId(const TOptional<FString> TransactionId);
        TSharedPtr<FLockRequest> WithTtl(const TOptional<int64> Ttl);
        TSharedPtr<FLockRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetPropertyId() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetTransactionId() const;
        TOptional<int64> GetTtl() const;
        FString GetTtlString() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FLockRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FLockRequest, ESPMode::ThreadSafe> FLockRequestPtr;
}