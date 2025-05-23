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
#include "../Model/DepositTransaction.h"

namespace Gs2::Money2::Request
{
    class FDepositByUserIdRequest;

    class GS2MONEY2_API FDepositByUserIdRequest final : public TSharedFromThis<FDepositByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<int32> SlotValue;
        TSharedPtr<TArray<TSharedPtr<Model::FDepositTransaction>>> DepositTransactionsValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FDepositByUserIdRequest();
        FDepositByUserIdRequest(
            const FDepositByUserIdRequest& From
        );
        ~FDepositByUserIdRequest() = default;

        TSharedPtr<FDepositByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDepositByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDepositByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FDepositByUserIdRequest> WithSlot(const TOptional<int32> Slot);
        TSharedPtr<FDepositByUserIdRequest> WithDepositTransactions(const TSharedPtr<TArray<TSharedPtr<Model::FDepositTransaction>>> DepositTransactions);
        TSharedPtr<FDepositByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FDepositByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<int32> GetSlot() const;
        FString GetSlotString() const;TSharedPtr<TArray<TSharedPtr<Model::FDepositTransaction>>> GetDepositTransactions() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FDepositByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDepositByUserIdRequest> FDepositByUserIdRequestPtr;
}