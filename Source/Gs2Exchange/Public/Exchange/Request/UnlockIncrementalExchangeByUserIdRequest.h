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

namespace Gs2::Exchange::Request
{
    class FUnlockIncrementalExchangeByUserIdRequest;

    class GS2EXCHANGE_API FUnlockIncrementalExchangeByUserIdRequest final : public TSharedFromThis<FUnlockIncrementalExchangeByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> RateNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> LockTransactionIdValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FUnlockIncrementalExchangeByUserIdRequest();
        FUnlockIncrementalExchangeByUserIdRequest(
            const FUnlockIncrementalExchangeByUserIdRequest& From
        );
        ~FUnlockIncrementalExchangeByUserIdRequest() = default;

        TSharedPtr<FUnlockIncrementalExchangeByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FUnlockIncrementalExchangeByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FUnlockIncrementalExchangeByUserIdRequest> WithRateName(const TOptional<FString> RateName);
        TSharedPtr<FUnlockIncrementalExchangeByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FUnlockIncrementalExchangeByUserIdRequest> WithLockTransactionId(const TOptional<FString> LockTransactionId);
        TSharedPtr<FUnlockIncrementalExchangeByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetRateName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetLockTransactionId() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FUnlockIncrementalExchangeByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUnlockIncrementalExchangeByUserIdRequest, ESPMode::ThreadSafe> FUnlockIncrementalExchangeByUserIdRequestPtr;
}