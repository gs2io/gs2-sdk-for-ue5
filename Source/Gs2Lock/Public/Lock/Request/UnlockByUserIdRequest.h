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
    class FUnlockByUserIdRequest;

    class GS2LOCK_API FUnlockByUserIdRequest final : public TSharedFromThis<FUnlockByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> PropertyIdValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> TransactionIdValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FUnlockByUserIdRequest();
        FUnlockByUserIdRequest(
            const FUnlockByUserIdRequest& From
        );
        ~FUnlockByUserIdRequest() = default;

        TSharedPtr<FUnlockByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FUnlockByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FUnlockByUserIdRequest> WithPropertyId(const TOptional<FString> PropertyId);
        TSharedPtr<FUnlockByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FUnlockByUserIdRequest> WithTransactionId(const TOptional<FString> TransactionId);
        TSharedPtr<FUnlockByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FUnlockByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetPropertyId() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetTransactionId() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FUnlockByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUnlockByUserIdRequest> FUnlockByUserIdRequestPtr;
}