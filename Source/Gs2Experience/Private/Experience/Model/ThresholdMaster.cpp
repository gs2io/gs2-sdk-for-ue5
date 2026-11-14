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

#include "Experience/Model/ThresholdMaster.h"

namespace Gs2::Experience::Model
{
    FThresholdMaster::FThresholdMaster():
        ThresholdIdValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        ValuesValue(nullptr),
        CreatedAtValue(TOptional<int64>()),
        UpdatedAtValue(TOptional<int64>()),
        RevisionValue(TOptional<int64>())
    {
    }

    FThresholdMaster::FThresholdMaster(
        const FThresholdMaster& From
    ):
        ThresholdIdValue(From.ThresholdIdValue),
        NameValue(From.NameValue),
        DescriptionValue(From.DescriptionValue),
        MetadataValue(From.MetadataValue),
        ValuesValue(From.ValuesValue),
        CreatedAtValue(From.CreatedAtValue),
        UpdatedAtValue(From.UpdatedAtValue),
        RevisionValue(From.RevisionValue)
    {
    }

    TSharedPtr<FThresholdMaster> FThresholdMaster::WithThresholdId(
        const TOptional<FString> ThresholdId
    )
    {
        this->ThresholdIdValue = ThresholdId;
        return SharedThis(this);
    }

    TSharedPtr<FThresholdMaster> FThresholdMaster::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FThresholdMaster> FThresholdMaster::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
        return SharedThis(this);
    }

    TSharedPtr<FThresholdMaster> FThresholdMaster::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FThresholdMaster> FThresholdMaster::WithValues(
        const TSharedPtr<TArray<int64>> Values
    )
    {
        this->ValuesValue = Values;
        return SharedThis(this);
    }

    TSharedPtr<FThresholdMaster> FThresholdMaster::WithCreatedAt(
        const TOptional<int64> CreatedAt
    )
    {
        this->CreatedAtValue = CreatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FThresholdMaster> FThresholdMaster::WithUpdatedAt(
        const TOptional<int64> UpdatedAt
    )
    {
        this->UpdatedAtValue = UpdatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FThresholdMaster> FThresholdMaster::WithRevision(
        const TOptional<int64> Revision
    )
    {
        this->RevisionValue = Revision;
        return SharedThis(this);
    }
    TOptional<FString> FThresholdMaster::GetThresholdId() const
    {
        return ThresholdIdValue;
    }
    TOptional<FString> FThresholdMaster::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FThresholdMaster::GetDescription() const
    {
        return DescriptionValue;
    }
    TOptional<FString> FThresholdMaster::GetMetadata() const
    {
        return MetadataValue;
    }
    TSharedPtr<TArray<int64>> FThresholdMaster::GetValues() const
    {
        return ValuesValue;
    }
    TOptional<int64> FThresholdMaster::GetCreatedAt() const
    {
        return CreatedAtValue;
    }

    FString FThresholdMaster::GetCreatedAtString() const
    {
        if (!CreatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue());
    }
    TOptional<int64> FThresholdMaster::GetUpdatedAt() const
    {
        return UpdatedAtValue;
    }

    FString FThresholdMaster::GetUpdatedAtString() const
    {
        if (!UpdatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), UpdatedAtValue.GetValue());
    }
    TOptional<int64> FThresholdMaster::GetRevision() const
    {
        return RevisionValue;
    }

    FString FThresholdMaster::GetRevisionString() const
    {
        if (!RevisionValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), RevisionValue.GetValue());
    }

    TOptional<FString> FThresholdMaster::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):experience:(?<namespaceName>.+):threshold:(?<thresholdName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FThresholdMaster::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):experience:(?<namespaceName>.+):threshold:(?<thresholdName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FThresholdMaster::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):experience:(?<namespaceName>.+):threshold:(?<thresholdName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FThresholdMaster::GetThresholdNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):experience:(?<namespaceName>.+):threshold:(?<thresholdName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FThresholdMaster> FThresholdMaster::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FThresholdMaster>()
            ->WithThresholdId(Data->HasField(ANSI_TO_TCHAR("thresholdId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("thresholdId"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithName(Data->HasField(ANSI_TO_TCHAR("name")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("name"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithDescription(Data->HasField(ANSI_TO_TCHAR("description")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("description"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithMetadata(Data->HasField(ANSI_TO_TCHAR("metadata")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("metadata"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithValues(Data->HasField(ANSI_TO_TCHAR("values")) ? [Data]() -> TSharedPtr<TArray<int64>>
                {
                    if (!Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("values")))
                    {
                        return nullptr;
                    }
                    auto v = MakeShared<TArray<int64>>();
                    for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("values")))
                    {
                        v->Add(JsonObjectValue->AsNumber());
                    }
                    return v;
                 }() : nullptr)
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

    TSharedPtr<FJsonObject> FThresholdMaster::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ThresholdIdValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("thresholdId"), ThresholdIdValue.GetValue());
        }
        if (NameValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("name"), NameValue.GetValue());
        }
        if (DescriptionValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("description"), DescriptionValue.GetValue());
        }
        if (MetadataValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("metadata"), MetadataValue.GetValue());
        }
        if (ValuesValue != nullptr && ValuesValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *ValuesValue)
            {
                v.Add(MakeShared<FJsonValueString>(FString::Printf(TEXT("%lld"), JsonObjectValue)));
            }
            JsonRootObject->SetArrayField(TEXT("values"), v);
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

    FString FThresholdMaster::TypeName = "ThresholdMaster";
}
#include "Experience/Model/Cache/ThresholdMaster.h"

namespace Gs2::Experience::Model::Cache
{
    FString FThresholdMasterCache::CreateCacheParentKey(
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<int32> CacheOwnerArgumentTimeOffset
    )
    {
        return FString("experience:")
            + CacheOwnerArgumentNamespaceName.Get(FString()) + FString(":")
            + FString::FromInt(CacheOwnerArgumentTimeOffset.Get(0)) + FString(":ThresholdMaster");
    }

    FString FThresholdMasterCache::CreateCacheKey(
        TOptional<FString> CacheOwnerArgumentThresholdName
    )
    {
        return
            FString()
            + CacheOwnerArgumentThresholdName.Get(FString())
            ;
    }

    bool FThresholdMasterCache::TryGet(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<FString> CacheOwnerArgumentThresholdName,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        Gs2::Experience::Model::FThresholdMasterPtr* CacheOwnerArgumentOutItem
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid())
        {
            if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
            return false;
        }
        if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
        Gs2::Experience::Model::FThresholdMasterPtr CacheOwnerValue;
        const bool CacheOwnerFound = CacheSnapshot->TryGet<Gs2::Experience::Model::FThresholdMaster>(
            CreateCacheParentKey(
                CacheOwnerArgumentNamespaceName,
                CacheOwnerArgumentTimeOffset
            ),
            CreateCacheKey(
                CacheOwnerArgumentThresholdName
            ),
            &CacheOwnerValue
        );
        if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = CacheOwnerFound ? CacheOwnerValue : nullptr;
        return CacheOwnerFound;
    }

    void FThresholdMasterCache::Put(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<FString> CacheOwnerArgumentThresholdName,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        const Gs2::Experience::Model::FThresholdMasterPtr& CacheOwnerArgumentItem
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid()) return;
        const auto CacheOwnerParentKey = CreateCacheParentKey(
            CacheOwnerArgumentNamespaceName,
            CacheOwnerArgumentTimeOffset
        );
        const auto CacheOwnerKey = CreateCacheKey(
            CacheOwnerArgumentThresholdName
        );
        auto CacheOwnerValue = CacheOwnerArgumentItem;
        Gs2::Experience::Model::FThresholdMasterPtr CacheOwnerExisting;
        if (CacheSnapshot->TryGet<Gs2::Experience::Model::FThresholdMaster>(CacheOwnerParentKey, CacheOwnerKey, &CacheOwnerExisting))
        {
            const int64 CacheOwnerOldRevision = CacheOwnerExisting.IsValid() ? CacheOwnerExisting->GetRevision().Get(-1) : -1;
            const int64 CacheOwnerNewRevision = CacheOwnerValue.IsValid() ? CacheOwnerValue->GetRevision().Get(-1) : -1;
            if (CacheOwnerOldRevision > CacheOwnerNewRevision && CacheOwnerNewRevision > 1) return;
            if (CacheOwnerOldRevision == CacheOwnerNewRevision) return;
        }
        CacheSnapshot->Put(Gs2::Experience::Model::FThresholdMaster::TypeName, CacheOwnerParentKey, CacheOwnerKey, CacheOwnerValue,
            FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
        );
    }

    FString FThresholdMasterCache::PutUserData(
        const Gs2::Core::Domain::FCacheDatabasePtr& Cache,
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<int32> TimeOffset,
        const Gs2::Experience::Model::FThresholdMasterPtr& Item
    )
    {
        if (!Item.IsValid()) return FString();
        Put(
            Cache,
            NamespaceName,
            Item->GetName(),
            TimeOffset,
            Item
        );
        return CreateCacheParentKey(
            NamespaceName,
            TimeOffset
        );
    }

    void FThresholdMasterCache::Delete(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<FString> CacheOwnerArgumentThresholdName,
        TOptional<int32> CacheOwnerArgumentTimeOffset
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid()) return;
        CacheSnapshot->Delete(Gs2::Experience::Model::FThresholdMaster::TypeName, CreateCacheParentKey(
            CacheOwnerArgumentNamespaceName,
            CacheOwnerArgumentTimeOffset
        ), CreateCacheKey(
            CacheOwnerArgumentThresholdName
        ));
    }

    Gs2::Core::Model::FGs2ErrorPtr FThresholdMasterCache::Fetch(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<FString> CacheOwnerArgumentThresholdName,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        const TFunction<Gs2::Core::Model::FGs2ErrorPtr(Gs2::Experience::Model::FThresholdMasterPtr*)>& CacheOwnerArgumentFetchImpl,
        Gs2::Experience::Model::FThresholdMasterPtr* CacheOwnerArgumentOutItem
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
        Gs2::Experience::Model::FThresholdMasterPtr CacheOwnerFetchedItem;
        const auto CacheOwnerError = FetchImplSnapshot(&CacheOwnerFetchedItem);
        if (!CacheOwnerError)
        {
            Put(
                CacheSnapshot,
                CacheOwnerArgumentNamespaceName,
                CacheOwnerArgumentThresholdName,
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
            CacheOwnerArgumentThresholdName,
            CacheOwnerArgumentTimeOffset,
            nullptr
        );
        if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
        const auto CacheOwnerDetails = CacheOwnerError->GetErrors();
        if (CacheOwnerDetails.IsValid() && CacheOwnerDetails->Num() > 0 && (*CacheOwnerDetails)[0].IsValid() && (*CacheOwnerDetails)[0]->GetComponent() == TEXT("thresholdMaster"))
        {
            return nullptr;
        }
        if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
        return CacheOwnerError;
    }

    Gs2::Core::Domain::CallbackID FThresholdMasterCache::ListSubscribe(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        TFunction<void(TArray<Gs2::Experience::Model::FThresholdMasterPtr>)> CacheOwnerArgumentCallback
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid()) return 0;
        return CacheSnapshot->ListSubscribeTyped(Gs2::Experience::Model::FThresholdMaster::TypeName, CreateCacheParentKey(
            CacheOwnerArgumentNamespaceName,
            CacheOwnerArgumentTimeOffset
        ), [CacheOwnerArgumentCallback](const TArray<FGs2ObjectPtr>& CacheOwnerValues)
        {
            TArray<Gs2::Experience::Model::FThresholdMasterPtr> CacheOwnerTypedValues;
            for (const auto& CacheOwnerValue : CacheOwnerValues) if (CacheOwnerValue) CacheOwnerTypedValues.Add(StaticCastSharedPtr<Gs2::Experience::Model::FThresholdMaster>(CacheOwnerValue));
            if (CacheOwnerArgumentCallback) CacheOwnerArgumentCallback(CacheOwnerTypedValues);
        });
    }

    void FThresholdMasterCache::ListUnsubscribe(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        Gs2::Core::Domain::CallbackID CacheOwnerArgumentCallbackID
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid()) return;
        CacheSnapshot->ListUnsubscribe(Gs2::Experience::Model::FThresholdMaster::TypeName, CreateCacheParentKey(
            CacheOwnerArgumentNamespaceName,
            CacheOwnerArgumentTimeOffset
        ), CacheOwnerArgumentCallbackID);
    }
}