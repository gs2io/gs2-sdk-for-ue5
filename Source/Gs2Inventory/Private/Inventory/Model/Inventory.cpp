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

#include "Inventory/Model/Inventory.h"

namespace Gs2::Inventory::Model
{
    FInventory::FInventory():
        InventoryIdValue(TOptional<FString>()),
        InventoryNameValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        CurrentInventoryCapacityUsageValue(TOptional<int32>()),
        CurrentInventoryMaxCapacityValue(TOptional<int32>()),
        CreatedAtValue(TOptional<int64>()),
        UpdatedAtValue(TOptional<int64>()),
        RevisionValue(TOptional<int64>())
    {
    }

    FInventory::FInventory(
        const FInventory& From
    ):
        InventoryIdValue(From.InventoryIdValue),
        InventoryNameValue(From.InventoryNameValue),
        UserIdValue(From.UserIdValue),
        CurrentInventoryCapacityUsageValue(From.CurrentInventoryCapacityUsageValue),
        CurrentInventoryMaxCapacityValue(From.CurrentInventoryMaxCapacityValue),
        CreatedAtValue(From.CreatedAtValue),
        UpdatedAtValue(From.UpdatedAtValue),
        RevisionValue(From.RevisionValue)
    {
    }

    TSharedPtr<FInventory> FInventory::WithInventoryId(
        const TOptional<FString> InventoryId
    )
    {
        this->InventoryIdValue = InventoryId;
        return SharedThis(this);
    }

    TSharedPtr<FInventory> FInventory::WithInventoryName(
        const TOptional<FString> InventoryName
    )
    {
        this->InventoryNameValue = InventoryName;
        return SharedThis(this);
    }

    TSharedPtr<FInventory> FInventory::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FInventory> FInventory::WithCurrentInventoryCapacityUsage(
        const TOptional<int32> CurrentInventoryCapacityUsage
    )
    {
        this->CurrentInventoryCapacityUsageValue = CurrentInventoryCapacityUsage;
        return SharedThis(this);
    }

    TSharedPtr<FInventory> FInventory::WithCurrentInventoryMaxCapacity(
        const TOptional<int32> CurrentInventoryMaxCapacity
    )
    {
        this->CurrentInventoryMaxCapacityValue = CurrentInventoryMaxCapacity;
        return SharedThis(this);
    }

    TSharedPtr<FInventory> FInventory::WithCreatedAt(
        const TOptional<int64> CreatedAt
    )
    {
        this->CreatedAtValue = CreatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FInventory> FInventory::WithUpdatedAt(
        const TOptional<int64> UpdatedAt
    )
    {
        this->UpdatedAtValue = UpdatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FInventory> FInventory::WithRevision(
        const TOptional<int64> Revision
    )
    {
        this->RevisionValue = Revision;
        return SharedThis(this);
    }
    TOptional<FString> FInventory::GetInventoryId() const
    {
        return InventoryIdValue;
    }
    TOptional<FString> FInventory::GetInventoryName() const
    {
        return InventoryNameValue;
    }
    TOptional<FString> FInventory::GetUserId() const
    {
        return UserIdValue;
    }
    TOptional<int32> FInventory::GetCurrentInventoryCapacityUsage() const
    {
        return CurrentInventoryCapacityUsageValue;
    }

    FString FInventory::GetCurrentInventoryCapacityUsageString() const
    {
        if (!CurrentInventoryCapacityUsageValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), CurrentInventoryCapacityUsageValue.GetValue());
    }
    TOptional<int32> FInventory::GetCurrentInventoryMaxCapacity() const
    {
        return CurrentInventoryMaxCapacityValue;
    }

    FString FInventory::GetCurrentInventoryMaxCapacityString() const
    {
        if (!CurrentInventoryMaxCapacityValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), CurrentInventoryMaxCapacityValue.GetValue());
    }
    TOptional<int64> FInventory::GetCreatedAt() const
    {
        return CreatedAtValue;
    }

    FString FInventory::GetCreatedAtString() const
    {
        if (!CreatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue());
    }
    TOptional<int64> FInventory::GetUpdatedAt() const
    {
        return UpdatedAtValue;
    }

    FString FInventory::GetUpdatedAtString() const
    {
        if (!UpdatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), UpdatedAtValue.GetValue());
    }
    TOptional<int64> FInventory::GetRevision() const
    {
        return RevisionValue;
    }

    FString FInventory::GetRevisionString() const
    {
        if (!RevisionValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), RevisionValue.GetValue());
    }

    TOptional<FString> FInventory::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):inventory:(?<namespaceName>.+):user:(?<userId>.+):inventory:(?<inventoryName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FInventory::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):inventory:(?<namespaceName>.+):user:(?<userId>.+):inventory:(?<inventoryName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FInventory::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):inventory:(?<namespaceName>.+):user:(?<userId>.+):inventory:(?<inventoryName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FInventory::GetUserIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):inventory:(?<namespaceName>.+):user:(?<userId>.+):inventory:(?<inventoryName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FInventory::GetInventoryNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):inventory:(?<namespaceName>.+):user:(?<userId>.+):inventory:(?<inventoryName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(5);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FInventory> FInventory::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FInventory>()
            ->WithInventoryId(Data->HasField(ANSI_TO_TCHAR("inventoryId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("inventoryId"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithInventoryName(Data->HasField(ANSI_TO_TCHAR("inventoryName")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("inventoryName"), v))
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
            ->WithCurrentInventoryCapacityUsage(Data->HasField(ANSI_TO_TCHAR("currentInventoryCapacityUsage")) ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("currentInventoryCapacityUsage"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithCurrentInventoryMaxCapacity(Data->HasField(ANSI_TO_TCHAR("currentInventoryMaxCapacity")) ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("currentInventoryMaxCapacity"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
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

    TSharedPtr<FJsonObject> FInventory::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (InventoryIdValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("inventoryId"), InventoryIdValue.GetValue());
        }
        if (InventoryNameValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("inventoryName"), InventoryNameValue.GetValue());
        }
        if (UserIdValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("userId"), UserIdValue.GetValue());
        }
        if (CurrentInventoryCapacityUsageValue.IsSet())
        {
            JsonRootObject->SetNumberField(TEXT("currentInventoryCapacityUsage"), CurrentInventoryCapacityUsageValue.GetValue());
        }
        if (CurrentInventoryMaxCapacityValue.IsSet())
        {
            JsonRootObject->SetNumberField(TEXT("currentInventoryMaxCapacity"), CurrentInventoryMaxCapacityValue.GetValue());
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

    FString FInventory::TypeName = "Inventory";
}
#include "Inventory/Model/Cache/Inventory.h"

namespace Gs2::Inventory::Model::Cache
{
    FString FInventoryCache::CreateCacheParentKey(
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<FString> CacheOwnerArgumentUserId,
        TOptional<int32> CacheOwnerArgumentTimeOffset
    )
    {
        return FString("inventory:")
            + CacheOwnerArgumentNamespaceName.Get(FString()) + FString(":")
            + CacheOwnerArgumentUserId.Get(FString()) + FString(":")
            + FString::FromInt(CacheOwnerArgumentTimeOffset.Get(0)) + FString(":Inventory");
    }

    FString FInventoryCache::CreateCacheKey(
        TOptional<FString> CacheOwnerArgumentInventoryName
    )
    {
        return
            FString()
            + CacheOwnerArgumentInventoryName.Get(FString())
            ;
    }

    bool FInventoryCache::TryGet(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<FString> CacheOwnerArgumentUserId,
        TOptional<FString> CacheOwnerArgumentInventoryName,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        Gs2::Inventory::Model::FInventoryPtr* CacheOwnerArgumentOutItem
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
        Gs2::Inventory::Model::FInventoryPtr CacheOwnerValue;
        const bool CacheOwnerFound = CacheSnapshot->TryGet<Gs2::Inventory::Model::FInventory>(
            CreateCacheParentKey(
                CacheOwnerArgumentNamespaceName,
                CacheOwnerArgumentUserId,
                CacheOwnerArgumentTimeOffset
            ),
            CreateCacheKey(
                CacheOwnerArgumentInventoryName
            ),
            &CacheOwnerValue
        );
        if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = CacheOwnerFound ? CacheOwnerValue : nullptr;
        return CacheOwnerFound;
    }

    void FInventoryCache::Put(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<FString> CacheOwnerArgumentUserId,
        TOptional<FString> CacheOwnerArgumentInventoryName,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        const Gs2::Inventory::Model::FInventoryPtr& CacheOwnerArgumentItem
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
            CacheOwnerArgumentInventoryName
        );
        auto CacheOwnerValue = CacheOwnerArgumentItem;
        Gs2::Inventory::Model::FInventoryPtr CacheOwnerExisting;
        if (CacheSnapshot->TryGet<Gs2::Inventory::Model::FInventory>(CacheOwnerParentKey, CacheOwnerKey, &CacheOwnerExisting))
        {
            const int64 CacheOwnerOldRevision = CacheOwnerExisting.IsValid() ? CacheOwnerExisting->GetRevision().Get(-1) : -1;
            const int64 CacheOwnerNewRevision = CacheOwnerValue.IsValid() ? CacheOwnerValue->GetRevision().Get(-1) : -1;
            if (CacheOwnerOldRevision > CacheOwnerNewRevision && CacheOwnerNewRevision > 1) return;
            if (CacheOwnerOldRevision == CacheOwnerNewRevision) return;
        }
        CacheSnapshot->Put(Gs2::Inventory::Model::FInventory::TypeName, CacheOwnerParentKey, CacheOwnerKey, CacheOwnerValue,
            FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
        );
    }

    FString FInventoryCache::PutUserData(
        const Gs2::Core::Domain::FCacheDatabasePtr& Cache,
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<int32> TimeOffset,
        const Gs2::Inventory::Model::FInventoryPtr& Item
    )
    {
        if (!Item.IsValid()) return FString();
        Put(
            Cache,
            NamespaceName,
            UserId,
            Item->GetInventoryName(),
            TimeOffset,
            Item
        );
        return CreateCacheParentKey(
            NamespaceName,
            UserId,
            TimeOffset
        );
    }

    void FInventoryCache::Delete(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<FString> CacheOwnerArgumentUserId,
        TOptional<FString> CacheOwnerArgumentInventoryName,
        TOptional<int32> CacheOwnerArgumentTimeOffset
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid()) return;
        if (!CacheOwnerArgumentUserId.IsSet()) return;
        CacheSnapshot->Delete(Gs2::Inventory::Model::FInventory::TypeName, CreateCacheParentKey(
            CacheOwnerArgumentNamespaceName,
            CacheOwnerArgumentUserId,
            CacheOwnerArgumentTimeOffset
        ), CreateCacheKey(
            CacheOwnerArgumentInventoryName
        ));
    }

    Gs2::Core::Model::FGs2ErrorPtr FInventoryCache::Fetch(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<FString> CacheOwnerArgumentUserId,
        TOptional<FString> CacheOwnerArgumentInventoryName,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        const TFunction<Gs2::Core::Model::FGs2ErrorPtr(Gs2::Inventory::Model::FInventoryPtr*)>& CacheOwnerArgumentFetchImpl,
        Gs2::Inventory::Model::FInventoryPtr* CacheOwnerArgumentOutItem
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
        Gs2::Inventory::Model::FInventoryPtr CacheOwnerFetchedItem;
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
                CacheOwnerArgumentInventoryName,
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
            CacheOwnerArgumentInventoryName,
            CacheOwnerArgumentTimeOffset,
            nullptr
        );
        if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
        const auto CacheOwnerDetails = CacheOwnerError->GetErrors();
        if (CacheOwnerDetails.IsValid() && CacheOwnerDetails->Num() > 0 && (*CacheOwnerDetails)[0].IsValid() && (*CacheOwnerDetails)[0]->GetComponent() == TEXT("inventory"))
        {
            return nullptr;
        }
        if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
        return CacheOwnerError;
    }

    Gs2::Core::Domain::CallbackID FInventoryCache::ListSubscribe(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<FString> CacheOwnerArgumentUserId,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        TFunction<void(TArray<Gs2::Inventory::Model::FInventoryPtr>)> CacheOwnerArgumentCallback
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid()) return 0;
        return CacheSnapshot->ListSubscribeTyped(Gs2::Inventory::Model::FInventory::TypeName, CreateCacheParentKey(
            CacheOwnerArgumentNamespaceName,
            CacheOwnerArgumentUserId,
            CacheOwnerArgumentTimeOffset
        ), [CacheOwnerArgumentCallback](const TArray<FGs2ObjectPtr>& CacheOwnerValues)
        {
            TArray<Gs2::Inventory::Model::FInventoryPtr> CacheOwnerTypedValues;
            for (const auto& CacheOwnerValue : CacheOwnerValues) if (CacheOwnerValue) CacheOwnerTypedValues.Add(StaticCastSharedPtr<Gs2::Inventory::Model::FInventory>(CacheOwnerValue));
            if (CacheOwnerArgumentCallback) CacheOwnerArgumentCallback(CacheOwnerTypedValues);
        });
    }

    void FInventoryCache::ListUnsubscribe(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<FString> CacheOwnerArgumentUserId,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        Gs2::Core::Domain::CallbackID CacheOwnerArgumentCallbackID
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid()) return;
        CacheSnapshot->ListUnsubscribe(Gs2::Inventory::Model::FInventory::TypeName, CreateCacheParentKey(
            CacheOwnerArgumentNamespaceName,
            CacheOwnerArgumentUserId,
            CacheOwnerArgumentTimeOffset
        ), CacheOwnerArgumentCallbackID);
    }
}