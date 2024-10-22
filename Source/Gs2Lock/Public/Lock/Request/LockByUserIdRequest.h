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
    class FLockByUserIdRequest;

    class GS2LOCK_API FLockByUserIdRequest final : public TSharedFromThis<FLockByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> PropertyIdValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> TransactionIdValue;
        TOptional<int64> TtlValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FLockByUserIdRequest();
        FLockByUserIdRequest(
            const FLockByUserIdRequest& From
        );
        ~FLockByUserIdRequest() = default;

        TSharedPtr<FLockByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FLockByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FLockByUserIdRequest> WithPropertyId(const TOptional<FString> PropertyId);
        TSharedPtr<FLockByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FLockByUserIdRequest> WithTransactionId(const TOptional<FString> TransactionId);
        TSharedPtr<FLockByUserIdRequest> WithTtl(const TOptional<int64> Ttl);
        TSharedPtr<FLockByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FLockByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetPropertyId() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetTransactionId() const;
        TOptional<int64> GetTtl() const;
        FString GetTtlString() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FLockByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FLockByUserIdRequest> FLockByUserIdRequestPtr;
}