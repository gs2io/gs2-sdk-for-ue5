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

#include "Money2/Model/SubscribeTransaction.h"

namespace Gs2::Money2::Model
{
    FSubscribeTransaction::FSubscribeTransaction():
        SubscribeTransactionIdValue(TOptional<FString>()),
        ContentNameValue(TOptional<FString>()),
        TransactionIdValue(TOptional<FString>()),
        StoreValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        StatusDetailValue(TOptional<FString>()),
        ExpiresAtValue(TOptional<int64>()),
        LastAllocatedAtValue(TOptional<int64>()),
        LastTakeOverAtValue(TOptional<int64>()),
        CreatedAtValue(TOptional<int64>()),
        UpdatedAtValue(TOptional<int64>()),
        RevisionValue(TOptional<int64>())
    {
    }

    FSubscribeTransaction::FSubscribeTransaction(
        const FSubscribeTransaction& From
    ):
        SubscribeTransactionIdValue(From.SubscribeTransactionIdValue),
        ContentNameValue(From.ContentNameValue),
        TransactionIdValue(From.TransactionIdValue),
        StoreValue(From.StoreValue),
        UserIdValue(From.UserIdValue),
        StatusDetailValue(From.StatusDetailValue),
        ExpiresAtValue(From.ExpiresAtValue),
        LastAllocatedAtValue(From.LastAllocatedAtValue),
        LastTakeOverAtValue(From.LastTakeOverAtValue),
        CreatedAtValue(From.CreatedAtValue),
        UpdatedAtValue(From.UpdatedAtValue),
        RevisionValue(From.RevisionValue)
    {
    }

    TSharedPtr<FSubscribeTransaction> FSubscribeTransaction::WithSubscribeTransactionId(
        const TOptional<FString> SubscribeTransactionId
    )
    {
        this->SubscribeTransactionIdValue = SubscribeTransactionId;
        return SharedThis(this);
    }

    TSharedPtr<FSubscribeTransaction> FSubscribeTransaction::WithContentName(
        const TOptional<FString> ContentName
    )
    {
        this->ContentNameValue = ContentName;
        return SharedThis(this);
    }

    TSharedPtr<FSubscribeTransaction> FSubscribeTransaction::WithTransactionId(
        const TOptional<FString> TransactionId
    )
    {
        this->TransactionIdValue = TransactionId;
        return SharedThis(this);
    }

    TSharedPtr<FSubscribeTransaction> FSubscribeTransaction::WithStore(
        const TOptional<FString> Store
    )
    {
        this->StoreValue = Store;
        return SharedThis(this);
    }

    TSharedPtr<FSubscribeTransaction> FSubscribeTransaction::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FSubscribeTransaction> FSubscribeTransaction::WithStatusDetail(
        const TOptional<FString> StatusDetail
    )
    {
        this->StatusDetailValue = StatusDetail;
        return SharedThis(this);
    }

    TSharedPtr<FSubscribeTransaction> FSubscribeTransaction::WithExpiresAt(
        const TOptional<int64> ExpiresAt
    )
    {
        this->ExpiresAtValue = ExpiresAt;
        return SharedThis(this);
    }

    TSharedPtr<FSubscribeTransaction> FSubscribeTransaction::WithLastAllocatedAt(
        const TOptional<int64> LastAllocatedAt
    )
    {
        this->LastAllocatedAtValue = LastAllocatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FSubscribeTransaction> FSubscribeTransaction::WithLastTakeOverAt(
        const TOptional<int64> LastTakeOverAt
    )
    {
        this->LastTakeOverAtValue = LastTakeOverAt;
        return SharedThis(this);
    }

    TSharedPtr<FSubscribeTransaction> FSubscribeTransaction::WithCreatedAt(
        const TOptional<int64> CreatedAt
    )
    {
        this->CreatedAtValue = CreatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FSubscribeTransaction> FSubscribeTransaction::WithUpdatedAt(
        const TOptional<int64> UpdatedAt
    )
    {
        this->UpdatedAtValue = UpdatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FSubscribeTransaction> FSubscribeTransaction::WithRevision(
        const TOptional<int64> Revision
    )
    {
        this->RevisionValue = Revision;
        return SharedThis(this);
    }
    TOptional<FString> FSubscribeTransaction::GetSubscribeTransactionId() const
    {
        return SubscribeTransactionIdValue;
    }
    TOptional<FString> FSubscribeTransaction::GetContentName() const
    {
        return ContentNameValue;
    }
    TOptional<FString> FSubscribeTransaction::GetTransactionId() const
    {
        return TransactionIdValue;
    }
    TOptional<FString> FSubscribeTransaction::GetStore() const
    {
        return StoreValue;
    }
    TOptional<FString> FSubscribeTransaction::GetUserId() const
    {
        return UserIdValue;
    }
    TOptional<FString> FSubscribeTransaction::GetStatusDetail() const
    {
        return StatusDetailValue;
    }
    TOptional<int64> FSubscribeTransaction::GetExpiresAt() const
    {
        return ExpiresAtValue;
    }

    FString FSubscribeTransaction::GetExpiresAtString() const
    {
        if (!ExpiresAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), ExpiresAtValue.GetValue());
    }
    TOptional<int64> FSubscribeTransaction::GetLastAllocatedAt() const
    {
        return LastAllocatedAtValue;
    }

    FString FSubscribeTransaction::GetLastAllocatedAtString() const
    {
        if (!LastAllocatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), LastAllocatedAtValue.GetValue());
    }
    TOptional<int64> FSubscribeTransaction::GetLastTakeOverAt() const
    {
        return LastTakeOverAtValue;
    }

    FString FSubscribeTransaction::GetLastTakeOverAtString() const
    {
        if (!LastTakeOverAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), LastTakeOverAtValue.GetValue());
    }
    TOptional<int64> FSubscribeTransaction::GetCreatedAt() const
    {
        return CreatedAtValue;
    }

    FString FSubscribeTransaction::GetCreatedAtString() const
    {
        if (!CreatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue());
    }
    TOptional<int64> FSubscribeTransaction::GetUpdatedAt() const
    {
        return UpdatedAtValue;
    }

    FString FSubscribeTransaction::GetUpdatedAtString() const
    {
        if (!UpdatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), UpdatedAtValue.GetValue());
    }
    TOptional<int64> FSubscribeTransaction::GetRevision() const
    {
        return RevisionValue;
    }

    FString FSubscribeTransaction::GetRevisionString() const
    {
        if (!RevisionValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), RevisionValue.GetValue());
    }

    TOptional<FString> FSubscribeTransaction::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):money2:(?<namespaceName>.+):subscriptionTransaction:(?<contentName>.+):(?<transactionId>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FSubscribeTransaction::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):money2:(?<namespaceName>.+):subscriptionTransaction:(?<contentName>.+):(?<transactionId>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FSubscribeTransaction::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):money2:(?<namespaceName>.+):subscriptionTransaction:(?<contentName>.+):(?<transactionId>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FSubscribeTransaction::GetContentNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):money2:(?<namespaceName>.+):subscriptionTransaction:(?<contentName>.+):(?<transactionId>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FSubscribeTransaction::GetTransactionIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):money2:(?<namespaceName>.+):subscriptionTransaction:(?<contentName>.+):(?<transactionId>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(5);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FSubscribeTransaction> FSubscribeTransaction::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FSubscribeTransaction>()
            ->WithSubscribeTransactionId(Data->HasField(ANSI_TO_TCHAR("subscribeTransactionId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("subscribeTransactionId"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithContentName(Data->HasField(ANSI_TO_TCHAR("contentName")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("contentName"), v))
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
            ->WithStore(Data->HasField(ANSI_TO_TCHAR("store")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("store"), v))
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
            ->WithStatusDetail(Data->HasField(ANSI_TO_TCHAR("statusDetail")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("statusDetail"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithExpiresAt(Data->HasField(ANSI_TO_TCHAR("expiresAt")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("expiresAt"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithLastAllocatedAt(Data->HasField(ANSI_TO_TCHAR("lastAllocatedAt")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("lastAllocatedAt"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithLastTakeOverAt(Data->HasField(ANSI_TO_TCHAR("lastTakeOverAt")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("lastTakeOverAt"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithCreatedAt(Data->HasField(ANSI_TO_TCHAR("createdAt")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("createdAt"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithUpdatedAt(Data->HasField(ANSI_TO_TCHAR("updatedAt")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("updatedAt"), v))
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

    TSharedPtr<FJsonObject> FSubscribeTransaction::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (SubscribeTransactionIdValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("subscribeTransactionId"), SubscribeTransactionIdValue.GetValue());
        }
        if (ContentNameValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("contentName"), ContentNameValue.GetValue());
        }
        if (TransactionIdValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("transactionId"), TransactionIdValue.GetValue());
        }
        if (StoreValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("store"), StoreValue.GetValue());
        }
        if (UserIdValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("userId"), UserIdValue.GetValue());
        }
        if (StatusDetailValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("statusDetail"), StatusDetailValue.GetValue());
        }
        if (ExpiresAtValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("expiresAt"), FString::Printf(TEXT("%lld"), ExpiresAtValue.GetValue()));
        }
        if (LastAllocatedAtValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("lastAllocatedAt"), FString::Printf(TEXT("%lld"), LastAllocatedAtValue.GetValue()));
        }
        if (LastTakeOverAtValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("lastTakeOverAt"), FString::Printf(TEXT("%lld"), LastTakeOverAtValue.GetValue()));
        }
        if (CreatedAtValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("createdAt"), FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue()));
        }
        if (UpdatedAtValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("updatedAt"), FString::Printf(TEXT("%lld"), UpdatedAtValue.GetValue()));
        }
        if (RevisionValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("revision"), FString::Printf(TEXT("%lld"), RevisionValue.GetValue()));
        }
        return JsonRootObject;
    }

    FString FSubscribeTransaction::TypeName = "SubscribeTransaction";
}
#include "Money2/Model/Cache/SubscribeTransaction.h"

namespace Gs2::Money2::Model::Cache
{
    FString FSubscribeTransactionCache::CreateCacheParentKey(
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<int32> CacheOwnerArgumentTimeOffset
    )
    {
        return FString("money2:")
            + CacheOwnerArgumentNamespaceName.Get(FString()) + FString(":")
            + FString::FromInt(CacheOwnerArgumentTimeOffset.Get(0)) + FString(":SubscribeTransaction");
    }

    FString FSubscribeTransactionCache::CreateCacheKey(
        TOptional<FString> CacheOwnerArgumentContentName,
        TOptional<FString> CacheOwnerArgumentTransactionId
    )
    {
        return
            FString()
            + CacheOwnerArgumentContentName.Get(FString()) + FString(":")
            + CacheOwnerArgumentTransactionId.Get(FString())
            ;
    }

    bool FSubscribeTransactionCache::TryGet(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<FString> CacheOwnerArgumentContentName,
        TOptional<FString> CacheOwnerArgumentTransactionId,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        Gs2::Money2::Model::FSubscribeTransactionPtr* CacheOwnerArgumentOutItem
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid())
        {
            if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
            return false;
        }
        if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
        Gs2::Money2::Model::FSubscribeTransactionPtr CacheOwnerValue;
        const bool CacheOwnerFound = CacheSnapshot->TryGet<Gs2::Money2::Model::FSubscribeTransaction>(
            CreateCacheParentKey(
                CacheOwnerArgumentNamespaceName,
                CacheOwnerArgumentTimeOffset
            ),
            CreateCacheKey(
                CacheOwnerArgumentContentName,
                CacheOwnerArgumentTransactionId
            ),
            &CacheOwnerValue
        );
        if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = CacheOwnerFound ? CacheOwnerValue : nullptr;
        return CacheOwnerFound;
    }

    void FSubscribeTransactionCache::Put(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<FString> CacheOwnerArgumentContentName,
        TOptional<FString> CacheOwnerArgumentTransactionId,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        const Gs2::Money2::Model::FSubscribeTransactionPtr& CacheOwnerArgumentItem
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid()) return;
        const auto CacheOwnerParentKey = CreateCacheParentKey(
            CacheOwnerArgumentNamespaceName,
            CacheOwnerArgumentTimeOffset
        );
        const auto CacheOwnerKey = CreateCacheKey(
            CacheOwnerArgumentContentName,
            CacheOwnerArgumentTransactionId
        );
        auto CacheOwnerValue = CacheOwnerArgumentItem;
        Gs2::Money2::Model::FSubscribeTransactionPtr CacheOwnerExisting;
        if (CacheSnapshot->TryGet<Gs2::Money2::Model::FSubscribeTransaction>(CacheOwnerParentKey, CacheOwnerKey, &CacheOwnerExisting))
        {
            const int64 CacheOwnerOldRevision = CacheOwnerExisting.IsValid() ? CacheOwnerExisting->GetRevision().Get(-1) : -1;
            const int64 CacheOwnerNewRevision = CacheOwnerValue.IsValid() ? CacheOwnerValue->GetRevision().Get(-1) : -1;
            if (CacheOwnerOldRevision > CacheOwnerNewRevision && CacheOwnerNewRevision > 1) return;
            if (CacheOwnerOldRevision == CacheOwnerNewRevision) return;
        }
        CacheSnapshot->Put(Gs2::Money2::Model::FSubscribeTransaction::TypeName, CacheOwnerParentKey, CacheOwnerKey, CacheOwnerValue,
            CacheOwnerValue.IsValid() && CacheOwnerValue->GetExpiresAt().IsSet() && CacheOwnerValue->GetExpiresAt().Get(0) != 0
                ? FDateTime::FromUnixTimestamp(0) + FTimespan::FromMilliseconds(CacheOwnerValue->GetExpiresAt().Get(0))
                : FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
        );
    }

    void FSubscribeTransactionCache::Delete(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<FString> CacheOwnerArgumentContentName,
        TOptional<FString> CacheOwnerArgumentTransactionId,
        TOptional<int32> CacheOwnerArgumentTimeOffset
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid()) return;
        CacheSnapshot->Delete(Gs2::Money2::Model::FSubscribeTransaction::TypeName, CreateCacheParentKey(
            CacheOwnerArgumentNamespaceName,
            CacheOwnerArgumentTimeOffset
        ), CreateCacheKey(
            CacheOwnerArgumentContentName,
            CacheOwnerArgumentTransactionId
        ));
    }

    Gs2::Core::Model::FGs2ErrorPtr FSubscribeTransactionCache::Fetch(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<FString> CacheOwnerArgumentContentName,
        TOptional<FString> CacheOwnerArgumentTransactionId,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        const TFunction<Gs2::Core::Model::FGs2ErrorPtr(Gs2::Money2::Model::FSubscribeTransactionPtr*)>& CacheOwnerArgumentFetchImpl,
        Gs2::Money2::Model::FSubscribeTransactionPtr* CacheOwnerArgumentOutItem
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
        Gs2::Money2::Model::FSubscribeTransactionPtr CacheOwnerFetchedItem;
        const auto CacheOwnerError = FetchImplSnapshot(&CacheOwnerFetchedItem);
        if (!CacheOwnerError)
        {
            Put(
                CacheSnapshot,
                CacheOwnerArgumentNamespaceName,
                CacheOwnerArgumentContentName,
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
            CacheOwnerArgumentContentName,
            CacheOwnerArgumentTransactionId,
            CacheOwnerArgumentTimeOffset,
            nullptr
        );
        if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
        const auto CacheOwnerDetails = CacheOwnerError->GetErrors();
        if (CacheOwnerDetails.IsValid() && CacheOwnerDetails->Num() > 0 && (*CacheOwnerDetails)[0].IsValid() && (*CacheOwnerDetails)[0]->GetComponent() == TEXT("subscribeTransaction"))
        {
            return nullptr;
        }
        if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
        return CacheOwnerError;
    }

    Gs2::Core::Domain::CallbackID FSubscribeTransactionCache::ListSubscribe(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        TFunction<void(TArray<Gs2::Money2::Model::FSubscribeTransactionPtr>)> CacheOwnerArgumentCallback
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid()) return 0;
        return CacheSnapshot->ListSubscribeTyped(Gs2::Money2::Model::FSubscribeTransaction::TypeName, CreateCacheParentKey(
            CacheOwnerArgumentNamespaceName,
            CacheOwnerArgumentTimeOffset
        ), [CacheOwnerArgumentCallback](const TArray<FGs2ObjectPtr>& CacheOwnerValues)
        {
            TArray<Gs2::Money2::Model::FSubscribeTransactionPtr> CacheOwnerTypedValues;
            for (const auto& CacheOwnerValue : CacheOwnerValues) if (CacheOwnerValue) CacheOwnerTypedValues.Add(StaticCastSharedPtr<Gs2::Money2::Model::FSubscribeTransaction>(CacheOwnerValue));
            if (CacheOwnerArgumentCallback) CacheOwnerArgumentCallback(CacheOwnerTypedValues);
        });
    }

    void FSubscribeTransactionCache::ListUnsubscribe(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        Gs2::Core::Domain::CallbackID CacheOwnerArgumentCallbackID
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid()) return;
        CacheSnapshot->ListUnsubscribe(Gs2::Money2::Model::FSubscribeTransaction::TypeName, CreateCacheParentKey(
            CacheOwnerArgumentNamespaceName,
            CacheOwnerArgumentTimeOffset
        ), CacheOwnerArgumentCallbackID);
    }
}