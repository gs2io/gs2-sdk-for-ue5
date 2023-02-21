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

namespace Gs2::Money::Model
{
    class GS2MONEY_API FReceipt final : public TSharedFromThis<FReceipt>
    {
        TOptional<FString> ReceiptIdValue;
        TOptional<FString> TransactionIdValue;
        TOptional<FString> PurchaseTokenValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> TypeValue;
        TOptional<int32> SlotValue;
        TOptional<float> PriceValue;
        TOptional<int32> PaidValue;
        TOptional<int32> FreeValue;
        TOptional<int32> TotalValue;
        TOptional<FString> ContentsIdValue;
        TOptional<int64> CreatedAtValue;

    public:
        FReceipt();
        FReceipt(
            const FReceipt& From
        );
        ~FReceipt() = default;

        TSharedPtr<FReceipt> WithReceiptId(const TOptional<FString> ReceiptId);
        TSharedPtr<FReceipt> WithTransactionId(const TOptional<FString> TransactionId);
        TSharedPtr<FReceipt> WithPurchaseToken(const TOptional<FString> PurchaseToken);
        TSharedPtr<FReceipt> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FReceipt> WithType(const TOptional<FString> Type);
        TSharedPtr<FReceipt> WithSlot(const TOptional<int32> Slot);
        TSharedPtr<FReceipt> WithPrice(const TOptional<float> Price);
        TSharedPtr<FReceipt> WithPaid(const TOptional<int32> Paid);
        TSharedPtr<FReceipt> WithFree(const TOptional<int32> Free);
        TSharedPtr<FReceipt> WithTotal(const TOptional<int32> Total);
        TSharedPtr<FReceipt> WithContentsId(const TOptional<FString> ContentsId);
        TSharedPtr<FReceipt> WithCreatedAt(const TOptional<int64> CreatedAt);

        TOptional<FString> GetReceiptId() const;
        TOptional<FString> GetTransactionId() const;
        TOptional<FString> GetPurchaseToken() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetType() const;
        TOptional<int32> GetSlot() const;
        FString GetSlotString() const;
        TOptional<float> GetPrice() const;
        FString GetPriceString() const;
        TOptional<int32> GetPaid() const;
        FString GetPaidString() const;
        TOptional<int32> GetFree() const;
        FString GetFreeString() const;
        TOptional<int32> GetTotal() const;
        FString GetTotalString() const;
        TOptional<FString> GetContentsId() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetUserIdFromGrn(const FString Grn);
        static TOptional<FString> GetTransactionIdFromGrn(const FString Grn);

        static TSharedPtr<FReceipt> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FReceipt, ESPMode::ThreadSafe> FReceiptPtr;
}