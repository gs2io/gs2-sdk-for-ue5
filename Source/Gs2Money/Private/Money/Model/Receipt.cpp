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

#include "Money/Model/Receipt.h"

namespace Gs2::Money::Model
{
    FReceipt::FReceipt():
        ReceiptIdValue(TOptional<FString>()),
        TransactionIdValue(TOptional<FString>()),
        PurchaseTokenValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        TypeValue(TOptional<FString>()),
        SlotValue(TOptional<int32>()),
        PriceValue(TOptional<float>()),
        PaidValue(TOptional<int32>()),
        FreeValue(TOptional<int32>()),
        TotalValue(TOptional<int32>()),
        ContentsIdValue(TOptional<FString>()),
        CreatedAtValue(TOptional<int64>())
    {
    }

    FReceipt::FReceipt(
        const FReceipt& From
    ):
        ReceiptIdValue(From.ReceiptIdValue),
        TransactionIdValue(From.TransactionIdValue),
        PurchaseTokenValue(From.PurchaseTokenValue),
        UserIdValue(From.UserIdValue),
        TypeValue(From.TypeValue),
        SlotValue(From.SlotValue),
        PriceValue(From.PriceValue),
        PaidValue(From.PaidValue),
        FreeValue(From.FreeValue),
        TotalValue(From.TotalValue),
        ContentsIdValue(From.ContentsIdValue),
        CreatedAtValue(From.CreatedAtValue)
    {
    }

    TSharedPtr<FReceipt> FReceipt::WithReceiptId(
        const TOptional<FString> ReceiptId
    )
    {
        this->ReceiptIdValue = ReceiptId;
        return SharedThis(this);
    }

    TSharedPtr<FReceipt> FReceipt::WithTransactionId(
        const TOptional<FString> TransactionId
    )
    {
        this->TransactionIdValue = TransactionId;
        return SharedThis(this);
    }

    TSharedPtr<FReceipt> FReceipt::WithPurchaseToken(
        const TOptional<FString> PurchaseToken
    )
    {
        this->PurchaseTokenValue = PurchaseToken;
        return SharedThis(this);
    }

    TSharedPtr<FReceipt> FReceipt::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FReceipt> FReceipt::WithType(
        const TOptional<FString> Type
    )
    {
        this->TypeValue = Type;
        return SharedThis(this);
    }

    TSharedPtr<FReceipt> FReceipt::WithSlot(
        const TOptional<int32> Slot
    )
    {
        this->SlotValue = Slot;
        return SharedThis(this);
    }

    TSharedPtr<FReceipt> FReceipt::WithPrice(
        const TOptional<float> Price
    )
    {
        this->PriceValue = Price;
        return SharedThis(this);
    }

    TSharedPtr<FReceipt> FReceipt::WithPaid(
        const TOptional<int32> Paid
    )
    {
        this->PaidValue = Paid;
        return SharedThis(this);
    }

    TSharedPtr<FReceipt> FReceipt::WithFree(
        const TOptional<int32> Free
    )
    {
        this->FreeValue = Free;
        return SharedThis(this);
    }

    TSharedPtr<FReceipt> FReceipt::WithTotal(
        const TOptional<int32> Total
    )
    {
        this->TotalValue = Total;
        return SharedThis(this);
    }

    TSharedPtr<FReceipt> FReceipt::WithContentsId(
        const TOptional<FString> ContentsId
    )
    {
        this->ContentsIdValue = ContentsId;
        return SharedThis(this);
    }

    TSharedPtr<FReceipt> FReceipt::WithCreatedAt(
        const TOptional<int64> CreatedAt
    )
    {
        this->CreatedAtValue = CreatedAt;
        return SharedThis(this);
    }
    TOptional<FString> FReceipt::GetReceiptId() const
    {
        return ReceiptIdValue;
    }
    TOptional<FString> FReceipt::GetTransactionId() const
    {
        return TransactionIdValue;
    }
    TOptional<FString> FReceipt::GetPurchaseToken() const
    {
        return PurchaseTokenValue;
    }
    TOptional<FString> FReceipt::GetUserId() const
    {
        return UserIdValue;
    }
    TOptional<FString> FReceipt::GetType() const
    {
        return TypeValue;
    }
    TOptional<int32> FReceipt::GetSlot() const
    {
        return SlotValue;
    }

    FString FReceipt::GetSlotString() const
    {
        if (!SlotValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%ld"), SlotValue.GetValue());
    }
    TOptional<float> FReceipt::GetPrice() const
    {
        return PriceValue;
    }

    FString FReceipt::GetPriceString() const
    {
        if (!PriceValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%f"), PriceValue.GetValue());
    }
    TOptional<int32> FReceipt::GetPaid() const
    {
        return PaidValue;
    }

    FString FReceipt::GetPaidString() const
    {
        if (!PaidValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%ld"), PaidValue.GetValue());
    }
    TOptional<int32> FReceipt::GetFree() const
    {
        return FreeValue;
    }

    FString FReceipt::GetFreeString() const
    {
        if (!FreeValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%ld"), FreeValue.GetValue());
    }
    TOptional<int32> FReceipt::GetTotal() const
    {
        return TotalValue;
    }

    FString FReceipt::GetTotalString() const
    {
        if (!TotalValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%ld"), TotalValue.GetValue());
    }
    TOptional<FString> FReceipt::GetContentsId() const
    {
        return ContentsIdValue;
    }
    TOptional<int64> FReceipt::GetCreatedAt() const
    {
        return CreatedAtValue;
    }

    FString FReceipt::GetCreatedAtString() const
    {
        if (!CreatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue());
    }

    TOptional<FString> FReceipt::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):money:(?<namespaceName>.+):user:(?<userId>.+):receipt:(?<transactionId>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FReceipt::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):money:(?<namespaceName>.+):user:(?<userId>.+):receipt:(?<transactionId>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FReceipt::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):money:(?<namespaceName>.+):user:(?<userId>.+):receipt:(?<transactionId>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FReceipt::GetUserIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):money:(?<namespaceName>.+):user:(?<userId>.+):receipt:(?<transactionId>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FReceipt::GetTransactionIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):money:(?<namespaceName>.+):user:(?<userId>.+):receipt:(?<transactionId>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(5);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FReceipt> FReceipt::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FReceipt>()
            ->WithReceiptId(Data->HasField("receiptId") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("receiptId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithTransactionId(Data->HasField("transactionId") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("transactionId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithPurchaseToken(Data->HasField("purchaseToken") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("purchaseToken", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithUserId(Data->HasField("userId") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("userId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithType(Data->HasField("type") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("type", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithSlot(Data->HasField("slot") ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField("slot", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithPrice(Data->HasField("price") ? [Data]() -> TOptional<float>
                {
                    float v;
                    if (Data->TryGetNumberField("price", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<float>();
                }() : TOptional<float>())
            ->WithPaid(Data->HasField("paid") ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField("paid", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithFree(Data->HasField("free") ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField("free", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithTotal(Data->HasField("total") ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField("total", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithContentsId(Data->HasField("contentsId") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("contentsId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithCreatedAt(Data->HasField("createdAt") ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField("createdAt", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>());
    }

    TSharedPtr<FJsonObject> FReceipt::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ReceiptIdValue.IsSet())
        {
            JsonRootObject->SetStringField("receiptId", ReceiptIdValue.GetValue());
        }
        if (TransactionIdValue.IsSet())
        {
            JsonRootObject->SetStringField("transactionId", TransactionIdValue.GetValue());
        }
        if (PurchaseTokenValue.IsSet())
        {
            JsonRootObject->SetStringField("purchaseToken", PurchaseTokenValue.GetValue());
        }
        if (UserIdValue.IsSet())
        {
            JsonRootObject->SetStringField("userId", UserIdValue.GetValue());
        }
        if (TypeValue.IsSet())
        {
            JsonRootObject->SetStringField("type", TypeValue.GetValue());
        }
        if (SlotValue.IsSet())
        {
            JsonRootObject->SetNumberField("slot", SlotValue.GetValue());
        }
        if (PriceValue.IsSet())
        {
            JsonRootObject->SetNumberField("price", PriceValue.GetValue());
        }
        if (PaidValue.IsSet())
        {
            JsonRootObject->SetNumberField("paid", PaidValue.GetValue());
        }
        if (FreeValue.IsSet())
        {
            JsonRootObject->SetNumberField("free", FreeValue.GetValue());
        }
        if (TotalValue.IsSet())
        {
            JsonRootObject->SetNumberField("total", TotalValue.GetValue());
        }
        if (ContentsIdValue.IsSet())
        {
            JsonRootObject->SetStringField("contentsId", ContentsIdValue.GetValue());
        }
        if (CreatedAtValue.IsSet())
        {
            JsonRootObject->SetStringField("createdAt", FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue()));
        }
        return JsonRootObject;
    }

    FString FReceipt::TypeName = "Receipt";
}