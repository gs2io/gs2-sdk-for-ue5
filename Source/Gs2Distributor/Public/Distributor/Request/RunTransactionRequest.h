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

namespace Gs2::Distributor::Request
{
    class FRunTransactionRequest;

    class GS2DISTRIBUTOR_API FRunTransactionRequest final : public TSharedFromThis<FRunTransactionRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> OwnerIdValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> TransactionValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FRunTransactionRequest();
        FRunTransactionRequest(
            const FRunTransactionRequest& From
        );
        ~FRunTransactionRequest() = default;

        TSharedPtr<FRunTransactionRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FRunTransactionRequest> WithOwnerId(const TOptional<FString> OwnerId);
        TSharedPtr<FRunTransactionRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FRunTransactionRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FRunTransactionRequest> WithTransaction(const TOptional<FString> Transaction);
        TSharedPtr<FRunTransactionRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FRunTransactionRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetOwnerId() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetTransaction() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FRunTransactionRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FRunTransactionRequest> FRunTransactionRequestPtr;
}