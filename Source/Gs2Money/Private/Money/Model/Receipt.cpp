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
        CreatedAtValue(TOptional<int64>()),
        RevisionValue(TOptional<int64>())
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
        CreatedAtValue(From.CreatedAtValue),
        RevisionValue(From.RevisionValue)
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

    TSharedPtr<FReceipt> FReceipt::WithRevision(
        const TOptional<int64> Revision
    )
    {
        this->RevisionValue = Revision;
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
        return FString::Printf(TEXT("%d"), SlotValue.GetValue());
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
        return FString::Printf(TEXT("%d"), PaidValue.GetValue());
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
        return FString::Printf(TEXT("%d"), FreeValue.GetValue());
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
        return FString::Printf(TEXT("%d"), TotalValue.GetValue());
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
    TOptional<int64> FReceipt::GetRevision() const
    {
        return RevisionValue;
    }

    FString FReceipt::GetRevisionString() const
    {
        if (!RevisionValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), RevisionValue.GetValue());
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
            ->WithReceiptId(Data->HasField(ANSI_TO_TCHAR("receiptId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("receiptId"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithTransactionId(Data->HasField(ANSI_TO_TCHAR("transactionId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("transactionId"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithPurchaseToken(Data->HasField(ANSI_TO_TCHAR("purchaseToken")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("purchaseToken"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithUserId(Data->HasField(ANSI_TO_TCHAR("userId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("userId"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithType(Data->HasField(ANSI_TO_TCHAR("type")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("type"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithSlot(Data->HasField(ANSI_TO_TCHAR("slot")) ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("slot"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithPrice(Data->HasField(ANSI_TO_TCHAR("price")) ? [Data]() -> TOptional<float>
                {
                    float v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("price"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<float>();
                }() : TOptional<float>())
            ->WithPaid(Data->HasField(ANSI_TO_TCHAR("paid")) ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("paid"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithFree(Data->HasField(ANSI_TO_TCHAR("free")) ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("free"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithTotal(Data->HasField(ANSI_TO_TCHAR("total")) ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("total"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithContentsId(Data->HasField(ANSI_TO_TCHAR("contentsId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("contentsId"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithCreatedAt(Data->HasField(ANSI_TO_TCHAR("createdAt")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("createdAt"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithRevision(Data->HasField(ANSI_TO_TCHAR("revision")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("revision"), v))
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
            JsonRootObject->SetStringField(TEXT("receiptId"), ReceiptIdValue.GetValue());
        }
        if (TransactionIdValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("transactionId"), TransactionIdValue.GetValue());
        }
        if (PurchaseTokenValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("purchaseToken"), PurchaseTokenValue.GetValue());
        }
        if (UserIdValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("userId"), UserIdValue.GetValue());
        }
        if (TypeValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("type"), TypeValue.GetValue());
        }
        if (SlotValue.IsSet())
        {
            JsonRootObject->SetNumberField(TEXT("slot"), SlotValue.GetValue());
        }
        if (PriceValue.IsSet())
        {
            JsonRootObject->SetNumberField(TEXT("price"), PriceValue.GetValue());
        }
        if (PaidValue.IsSet())
        {
            JsonRootObject->SetNumberField(TEXT("paid"), PaidValue.GetValue());
        }
        if (FreeValue.IsSet())
        {
            JsonRootObject->SetNumberField(TEXT("free"), FreeValue.GetValue());
        }
        if (TotalValue.IsSet())
        {
            JsonRootObject->SetNumberField(TEXT("total"), TotalValue.GetValue());
        }
        if (ContentsIdValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("contentsId"), ContentsIdValue.GetValue());
        }
        if (CreatedAtValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("createdAt"), FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue()));
        }
        if (RevisionValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("revision"), FString::Printf(TEXT("%lld"), RevisionValue.GetValue()));
        }
        return JsonRootObject;
    }

    FString FReceipt::TypeName = "Receipt";
}
#include "Money/Model/Cache/Receipt.h"

namespace Gs2::Money::Model::Cache
{
    FString FReceiptCache::CreateCacheParentKey(
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<FString> CacheOwnerArgumentUserId,
        TOptional<int32> CacheOwnerArgumentTimeOffset
    )
    {
        return FString("money:")
            + CacheOwnerArgumentNamespaceName.Get(FString()) + FString(":")
            + CacheOwnerArgumentUserId.Get(FString()) + FString(":")
            + FString::FromInt(CacheOwnerArgumentTimeOffset.Get(0)) + FString(":Receipt");
    }

    FString FReceiptCache::CreateCacheKey(
        TOptional<FString> CacheOwnerArgumentTransactionId
    )
    {
        return
            FString()
            + CacheOwnerArgumentTransactionId.Get(FString())
            ;
    }

    bool FReceiptCache::TryGet(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<FString> CacheOwnerArgumentUserId,
        TOptional<FString> CacheOwnerArgumentTransactionId,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        Gs2::Money::Model::FReceiptPtr* CacheOwnerArgumentOutItem
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid())
        {
            if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
            return false;
        }
        if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
        if (!CacheOwnerArgumentUserId.IsSet()) return false;
        Gs2::Money::Model::FReceiptPtr CacheOwnerValue;
        const bool CacheOwnerFound = CacheSnapshot->TryGet<Gs2::Money::Model::FReceipt>(
            CreateCacheParentKey(
                CacheOwnerArgumentNamespaceName,
                CacheOwnerArgumentUserId,
                CacheOwnerArgumentTimeOffset
            ),
            CreateCacheKey(
                CacheOwnerArgumentTransactionId
            ),
            &CacheOwnerValue
        );
        if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = CacheOwnerFound ? CacheOwnerValue : nullptr;
        return CacheOwnerFound;
    }

    void FReceiptCache::Put(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<FString> CacheOwnerArgumentUserId,
        TOptional<FString> CacheOwnerArgumentTransactionId,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        const Gs2::Money::Model::FReceiptPtr& CacheOwnerArgumentItem
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid()) return;
        if (!CacheOwnerArgumentUserId.IsSet()) return;
        const auto CacheOwnerParentKey = CreateCacheParentKey(
            CacheOwnerArgumentNamespaceName,
            CacheOwnerArgumentUserId,
            CacheOwnerArgumentTimeOffset
        );
        const auto CacheOwnerKey = CreateCacheKey(
            CacheOwnerArgumentTransactionId
        );
        auto CacheOwnerValue = CacheOwnerArgumentItem;
        Gs2::Money::Model::FReceiptPtr CacheOwnerExisting;
        if (CacheSnapshot->TryGet<Gs2::Money::Model::FReceipt>(CacheOwnerParentKey, CacheOwnerKey, &CacheOwnerExisting))
        {
            const int64 CacheOwnerOldRevision = CacheOwnerExisting.IsValid() ? CacheOwnerExisting->GetRevision().Get(-1) : -1;
            const int64 CacheOwnerNewRevision = CacheOwnerValue.IsValid() ? CacheOwnerValue->GetRevision().Get(-1) : -1;
            if (CacheOwnerOldRevision > CacheOwnerNewRevision && CacheOwnerNewRevision > 1) return;
            if (CacheOwnerOldRevision == CacheOwnerNewRevision) return;
        }
        CacheSnapshot->Put(Gs2::Money::Model::FReceipt::TypeName, CacheOwnerParentKey, CacheOwnerKey, CacheOwnerValue,
            FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
        );
    }

    FString FReceiptCache::PutUserData(
        const Gs2::Core::Domain::FCacheDatabasePtr& Cache,
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<int32> TimeOffset,
        const Gs2::Money::Model::FReceiptPtr& Item
    )
    {
        if (!Item.IsValid()) return FString();
        Put(
            Cache,
            NamespaceName,
            UserId,
            Item->GetTransactionId(),
            TimeOffset,
            Item
        );
        return CreateCacheParentKey(
            NamespaceName,
            UserId,
            TimeOffset
        );
    }

    void FReceiptCache::Delete(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<FString> CacheOwnerArgumentUserId,
        TOptional<FString> CacheOwnerArgumentTransactionId,
        TOptional<int32> CacheOwnerArgumentTimeOffset
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid()) return;
        if (!CacheOwnerArgumentUserId.IsSet()) return;
        CacheSnapshot->Delete(Gs2::Money::Model::FReceipt::TypeName, CreateCacheParentKey(
            CacheOwnerArgumentNamespaceName,
            CacheOwnerArgumentUserId,
            CacheOwnerArgumentTimeOffset
        ), CreateCacheKey(
            CacheOwnerArgumentTransactionId
        ));
    }

    Gs2::Core::Model::FGs2ErrorPtr FReceiptCache::Fetch(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<FString> CacheOwnerArgumentUserId,
        TOptional<FString> CacheOwnerArgumentTransactionId,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        const TFunction<Gs2::Core::Model::FGs2ErrorPtr(Gs2::Money::Model::FReceiptPtr*)>& CacheOwnerArgumentFetchImpl,
        Gs2::Money::Model::FReceiptPtr* CacheOwnerArgumentOutItem
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        const auto FetchImplSnapshot = CacheOwnerArgumentFetchImpl;
        if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
        if (!FetchImplSnapshot)
        {
            if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
            const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
            Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("fetchImpl"), TEXT("fetchImpl is required."), TEXT("required")));
            return MakeShared<Gs2::Core::Model::FBadRequestError>(Details);
        }
        Gs2::Money::Model::FReceiptPtr CacheOwnerFetchedItem;
        const auto CacheOwnerError = FetchImplSnapshot(&CacheOwnerFetchedItem);
        if ((!CacheOwnerError || CacheOwnerError->IsChildOf(Gs2::Core::Model::FNotFoundError::Class)) && !CacheOwnerArgumentUserId.IsSet())
        {
            if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
            const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
            Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("userId"), TEXT("userId is required."), TEXT("required")));
            return MakeShared<Gs2::Core::Model::FBadRequestError>(Details);
        }
        if (!CacheOwnerError)
        {
            Put(
                CacheSnapshot,
                CacheOwnerArgumentNamespaceName,
                CacheOwnerArgumentUserId,
                CacheOwnerArgumentTransactionId,
                CacheOwnerArgumentTimeOffset,
                CacheOwnerFetchedItem
            );
            if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = CacheOwnerFetchedItem;
            return nullptr;
        }
        if (!CacheOwnerError->IsChildOf(Gs2::Core::Model::FNotFoundError::Class))
        {
            if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
            return CacheOwnerError;
        }
        Put(
            CacheSnapshot,
            CacheOwnerArgumentNamespaceName,
            CacheOwnerArgumentUserId,
            CacheOwnerArgumentTransactionId,
            CacheOwnerArgumentTimeOffset,
            nullptr
        );
        if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
        const auto CacheOwnerDetails = CacheOwnerError->GetErrors();
        if (CacheOwnerDetails.IsValid() && CacheOwnerDetails->Num() > 0 && (*CacheOwnerDetails)[0].IsValid() && (*CacheOwnerDetails)[0]->GetComponent() == TEXT("receipt"))
        {
            return nullptr;
        }
        if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
        return CacheOwnerError;
    }

    Gs2::Core::Domain::CallbackID FReceiptCache::ListSubscribe(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<FString> CacheOwnerArgumentUserId,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        TFunction<void(TArray<Gs2::Money::Model::FReceiptPtr>)> CacheOwnerArgumentCallback
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid()) return 0;
        return CacheSnapshot->ListSubscribeTyped(Gs2::Money::Model::FReceipt::TypeName, CreateCacheParentKey(
            CacheOwnerArgumentNamespaceName,
            CacheOwnerArgumentUserId,
            CacheOwnerArgumentTimeOffset
        ), [CacheOwnerArgumentCallback](const TArray<FGs2ObjectPtr>& CacheOwnerValues)
        {
            TArray<Gs2::Money::Model::FReceiptPtr> CacheOwnerTypedValues;
            for (const auto& CacheOwnerValue : CacheOwnerValues) if (CacheOwnerValue) CacheOwnerTypedValues.Add(StaticCastSharedPtr<Gs2::Money::Model::FReceipt>(CacheOwnerValue));
            if (CacheOwnerArgumentCallback) CacheOwnerArgumentCallback(CacheOwnerTypedValues);
        });
    }

    void FReceiptCache::ListUnsubscribe(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<FString> CacheOwnerArgumentUserId,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        Gs2::Core::Domain::CallbackID CacheOwnerArgumentCallbackID
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid()) return;
        CacheSnapshot->ListUnsubscribe(Gs2::Money::Model::FReceipt::TypeName, CreateCacheParentKey(
            CacheOwnerArgumentNamespaceName,
            CacheOwnerArgumentUserId,
            CacheOwnerArgumentTimeOffset
        ), CacheOwnerArgumentCallbackID);
    }
}