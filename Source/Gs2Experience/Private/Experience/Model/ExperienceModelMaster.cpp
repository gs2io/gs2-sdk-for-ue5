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

#include "Experience/Model/ExperienceModelMaster.h"

namespace Gs2::Experience::Model
{
    FExperienceModelMaster::FExperienceModelMaster():
        ExperienceModelIdValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        DefaultExperienceValue(TOptional<int64>()),
        DefaultRankCapValue(TOptional<int64>()),
        MaxRankCapValue(TOptional<int64>()),
        RankThresholdNameValue(TOptional<FString>()),
        AcquireActionRatesValue(nullptr),
        CreatedAtValue(TOptional<int64>()),
        UpdatedAtValue(TOptional<int64>()),
        RevisionValue(TOptional<int64>())
    {
    }

    FExperienceModelMaster::FExperienceModelMaster(
        const FExperienceModelMaster& From
    ):
        ExperienceModelIdValue(From.ExperienceModelIdValue),
        NameValue(From.NameValue),
        DescriptionValue(From.DescriptionValue),
        MetadataValue(From.MetadataValue),
        DefaultExperienceValue(From.DefaultExperienceValue),
        DefaultRankCapValue(From.DefaultRankCapValue),
        MaxRankCapValue(From.MaxRankCapValue),
        RankThresholdNameValue(From.RankThresholdNameValue),
        AcquireActionRatesValue(From.AcquireActionRatesValue),
        CreatedAtValue(From.CreatedAtValue),
        UpdatedAtValue(From.UpdatedAtValue),
        RevisionValue(From.RevisionValue)
    {
    }

    TSharedPtr<FExperienceModelMaster> FExperienceModelMaster::WithExperienceModelId(
        const TOptional<FString> ExperienceModelId
    )
    {
        this->ExperienceModelIdValue = ExperienceModelId;
        return SharedThis(this);
    }

    TSharedPtr<FExperienceModelMaster> FExperienceModelMaster::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FExperienceModelMaster> FExperienceModelMaster::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
        return SharedThis(this);
    }

    TSharedPtr<FExperienceModelMaster> FExperienceModelMaster::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FExperienceModelMaster> FExperienceModelMaster::WithDefaultExperience(
        const TOptional<int64> DefaultExperience
    )
    {
        this->DefaultExperienceValue = DefaultExperience;
        return SharedThis(this);
    }

    TSharedPtr<FExperienceModelMaster> FExperienceModelMaster::WithDefaultRankCap(
        const TOptional<int64> DefaultRankCap
    )
    {
        this->DefaultRankCapValue = DefaultRankCap;
        return SharedThis(this);
    }

    TSharedPtr<FExperienceModelMaster> FExperienceModelMaster::WithMaxRankCap(
        const TOptional<int64> MaxRankCap
    )
    {
        this->MaxRankCapValue = MaxRankCap;
        return SharedThis(this);
    }

    TSharedPtr<FExperienceModelMaster> FExperienceModelMaster::WithRankThresholdName(
        const TOptional<FString> RankThresholdName
    )
    {
        this->RankThresholdNameValue = RankThresholdName;
        return SharedThis(this);
    }

    TSharedPtr<FExperienceModelMaster> FExperienceModelMaster::WithAcquireActionRates(
        const TSharedPtr<TArray<TSharedPtr<Model::FAcquireActionRate>>> AcquireActionRates
    )
    {
        this->AcquireActionRatesValue = AcquireActionRates;
        return SharedThis(this);
    }

    TSharedPtr<FExperienceModelMaster> FExperienceModelMaster::WithCreatedAt(
        const TOptional<int64> CreatedAt
    )
    {
        this->CreatedAtValue = CreatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FExperienceModelMaster> FExperienceModelMaster::WithUpdatedAt(
        const TOptional<int64> UpdatedAt
    )
    {
        this->UpdatedAtValue = UpdatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FExperienceModelMaster> FExperienceModelMaster::WithRevision(
        const TOptional<int64> Revision
    )
    {
        this->RevisionValue = Revision;
        return SharedThis(this);
    }
    TOptional<FString> FExperienceModelMaster::GetExperienceModelId() const
    {
        return ExperienceModelIdValue;
    }
    TOptional<FString> FExperienceModelMaster::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FExperienceModelMaster::GetDescription() const
    {
        return DescriptionValue;
    }
    TOptional<FString> FExperienceModelMaster::GetMetadata() const
    {
        return MetadataValue;
    }
    TOptional<int64> FExperienceModelMaster::GetDefaultExperience() const
    {
        return DefaultExperienceValue;
    }

    FString FExperienceModelMaster::GetDefaultExperienceString() const
    {
        if (!DefaultExperienceValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), DefaultExperienceValue.GetValue());
    }
    TOptional<int64> FExperienceModelMaster::GetDefaultRankCap() const
    {
        return DefaultRankCapValue;
    }

    FString FExperienceModelMaster::GetDefaultRankCapString() const
    {
        if (!DefaultRankCapValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), DefaultRankCapValue.GetValue());
    }
    TOptional<int64> FExperienceModelMaster::GetMaxRankCap() const
    {
        return MaxRankCapValue;
    }

    FString FExperienceModelMaster::GetMaxRankCapString() const
    {
        if (!MaxRankCapValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), MaxRankCapValue.GetValue());
    }
    TOptional<FString> FExperienceModelMaster::GetRankThresholdName() const
    {
        return RankThresholdNameValue;
    }
    TSharedPtr<TArray<TSharedPtr<Model::FAcquireActionRate>>> FExperienceModelMaster::GetAcquireActionRates() const
    {
        return AcquireActionRatesValue;
    }
    TOptional<int64> FExperienceModelMaster::GetCreatedAt() const
    {
        return CreatedAtValue;
    }

    FString FExperienceModelMaster::GetCreatedAtString() const
    {
        if (!CreatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue());
    }
    TOptional<int64> FExperienceModelMaster::GetUpdatedAt() const
    {
        return UpdatedAtValue;
    }

    FString FExperienceModelMaster::GetUpdatedAtString() const
    {
        if (!UpdatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), UpdatedAtValue.GetValue());
    }
    TOptional<int64> FExperienceModelMaster::GetRevision() const
    {
        return RevisionValue;
    }

    FString FExperienceModelMaster::GetRevisionString() const
    {
        if (!RevisionValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), RevisionValue.GetValue());
    }

    TOptional<FString> FExperienceModelMaster::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):experience:(?<namespaceName>.+):model:(?<experienceName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FExperienceModelMaster::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):experience:(?<namespaceName>.+):model:(?<experienceName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FExperienceModelMaster::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):experience:(?<namespaceName>.+):model:(?<experienceName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FExperienceModelMaster::GetExperienceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):experience:(?<namespaceName>.+):model:(?<experienceName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FExperienceModelMaster> FExperienceModelMaster::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FExperienceModelMaster>()
            ->WithExperienceModelId(Data->HasField(ANSI_TO_TCHAR("experienceModelId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("experienceModelId"), v))
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
            ->WithDefaultExperience(Data->HasField(ANSI_TO_TCHAR("defaultExperience")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("defaultExperience"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithDefaultRankCap(Data->HasField(ANSI_TO_TCHAR("defaultRankCap")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("defaultRankCap"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithMaxRankCap(Data->HasField(ANSI_TO_TCHAR("maxRankCap")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("maxRankCap"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithRankThresholdName(Data->HasField(ANSI_TO_TCHAR("rankThresholdName")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("rankThresholdName"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithAcquireActionRates(Data->HasField(ANSI_TO_TCHAR("acquireActionRates")) ? [Data]() -> TSharedPtr<TArray<Model::FAcquireActionRatePtr>>
                {
                    if (!Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("acquireActionRates")))
                    {
                        return nullptr;
                    }
                    auto v = MakeShared<TArray<Model::FAcquireActionRatePtr>>();
                    for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("acquireActionRates")))
                    {
                        v->Add(Model::FAcquireActionRate::FromJson(JsonObjectValue->AsObject()));
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

    TSharedPtr<FJsonObject> FExperienceModelMaster::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ExperienceModelIdValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("experienceModelId"), ExperienceModelIdValue.GetValue());
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
        if (DefaultExperienceValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("defaultExperience"), FString::Printf(TEXT("%lld"), DefaultExperienceValue.GetValue()));
        }
        if (DefaultRankCapValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("defaultRankCap"), FString::Printf(TEXT("%lld"), DefaultRankCapValue.GetValue()));
        }
        if (MaxRankCapValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("maxRankCap"), FString::Printf(TEXT("%lld"), MaxRankCapValue.GetValue()));
        }
        if (RankThresholdNameValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("rankThresholdName"), RankThresholdNameValue.GetValue());
        }
        if (AcquireActionRatesValue != nullptr && AcquireActionRatesValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *AcquireActionRatesValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField(TEXT("acquireActionRates"), v);
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

    FString FExperienceModelMaster::TypeName = "ExperienceModelMaster";
}
#include "Experience/Model/Cache/ExperienceModelMaster.h"

namespace Gs2::Experience::Model::Cache
{
    FString FExperienceModelMasterCache::CreateCacheParentKey(
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<int32> CacheOwnerArgumentTimeOffset
    )
    {
        return FString("experience:")
            + CacheOwnerArgumentNamespaceName.Get(FString()) + FString(":")
            + FString::FromInt(CacheOwnerArgumentTimeOffset.Get(0)) + FString(":ExperienceModelMaster");
    }

    FString FExperienceModelMasterCache::CreateCacheKey(
        TOptional<FString> CacheOwnerArgumentExperienceName
    )
    {
        return
            FString()
            + CacheOwnerArgumentExperienceName.Get(FString())
            ;
    }

    bool FExperienceModelMasterCache::TryGet(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<FString> CacheOwnerArgumentExperienceName,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        Gs2::Experience::Model::FExperienceModelMasterPtr* CacheOwnerArgumentOutItem
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid())
        {
            if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
            return false;
        }
        if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
        Gs2::Experience::Model::FExperienceModelMasterPtr CacheOwnerValue;
        const bool CacheOwnerFound = CacheSnapshot->TryGet<Gs2::Experience::Model::FExperienceModelMaster>(
            CreateCacheParentKey(
                CacheOwnerArgumentNamespaceName,
                CacheOwnerArgumentTimeOffset
            ),
            CreateCacheKey(
                CacheOwnerArgumentExperienceName
            ),
            &CacheOwnerValue
        );
        if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = CacheOwnerFound ? CacheOwnerValue : nullptr;
        return CacheOwnerFound;
    }

    void FExperienceModelMasterCache::Put(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<FString> CacheOwnerArgumentExperienceName,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        const Gs2::Experience::Model::FExperienceModelMasterPtr& CacheOwnerArgumentItem
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid()) return;
        const auto CacheOwnerParentKey = CreateCacheParentKey(
            CacheOwnerArgumentNamespaceName,
            CacheOwnerArgumentTimeOffset
        );
        const auto CacheOwnerKey = CreateCacheKey(
            CacheOwnerArgumentExperienceName
        );
        auto CacheOwnerValue = CacheOwnerArgumentItem;
        Gs2::Experience::Model::FExperienceModelMasterPtr CacheOwnerExisting;
        if (CacheSnapshot->TryGet<Gs2::Experience::Model::FExperienceModelMaster>(CacheOwnerParentKey, CacheOwnerKey, &CacheOwnerExisting))
        {
            const int64 CacheOwnerOldRevision = CacheOwnerExisting.IsValid() ? CacheOwnerExisting->GetRevision().Get(-1) : -1;
            const int64 CacheOwnerNewRevision = CacheOwnerValue.IsValid() ? CacheOwnerValue->GetRevision().Get(-1) : -1;
            if (CacheOwnerOldRevision > CacheOwnerNewRevision && CacheOwnerNewRevision > 1) return;
            if (CacheOwnerOldRevision == CacheOwnerNewRevision) return;
        }
        CacheSnapshot->Put(Gs2::Experience::Model::FExperienceModelMaster::TypeName, CacheOwnerParentKey, CacheOwnerKey, CacheOwnerValue,
            FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
        );
    }

    FString FExperienceModelMasterCache::PutUserData(
        const Gs2::Core::Domain::FCacheDatabasePtr& Cache,
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<int32> TimeOffset,
        const Gs2::Experience::Model::FExperienceModelMasterPtr& Item
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

    void FExperienceModelMasterCache::Delete(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<FString> CacheOwnerArgumentExperienceName,
        TOptional<int32> CacheOwnerArgumentTimeOffset
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid()) return;
        CacheSnapshot->Delete(Gs2::Experience::Model::FExperienceModelMaster::TypeName, CreateCacheParentKey(
            CacheOwnerArgumentNamespaceName,
            CacheOwnerArgumentTimeOffset
        ), CreateCacheKey(
            CacheOwnerArgumentExperienceName
        ));
    }

    Gs2::Core::Model::FGs2ErrorPtr FExperienceModelMasterCache::Fetch(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<FString> CacheOwnerArgumentExperienceName,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        const TFunction<Gs2::Core::Model::FGs2ErrorPtr(Gs2::Experience::Model::FExperienceModelMasterPtr*)>& CacheOwnerArgumentFetchImpl,
        Gs2::Experience::Model::FExperienceModelMasterPtr* CacheOwnerArgumentOutItem
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
        Gs2::Experience::Model::FExperienceModelMasterPtr CacheOwnerFetchedItem;
        const auto CacheOwnerError = FetchImplSnapshot(&CacheOwnerFetchedItem);
        if (!CacheOwnerError)
        {
            Put(
                CacheSnapshot,
                CacheOwnerArgumentNamespaceName,
                CacheOwnerArgumentExperienceName,
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
            CacheOwnerArgumentExperienceName,
            CacheOwnerArgumentTimeOffset,
            nullptr
        );
        if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
        const auto CacheOwnerDetails = CacheOwnerError->GetErrors();
        if (CacheOwnerDetails.IsValid() && CacheOwnerDetails->Num() > 0 && (*CacheOwnerDetails)[0].IsValid() && (*CacheOwnerDetails)[0]->GetComponent() == TEXT("experienceModelMaster"))
        {
            return nullptr;
        }
        if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
        return CacheOwnerError;
    }

    Gs2::Core::Domain::CallbackID FExperienceModelMasterCache::ListSubscribe(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        TFunction<void(TArray<Gs2::Experience::Model::FExperienceModelMasterPtr>)> CacheOwnerArgumentCallback
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid()) return 0;
        return CacheSnapshot->ListSubscribeTyped(Gs2::Experience::Model::FExperienceModelMaster::TypeName, CreateCacheParentKey(
            CacheOwnerArgumentNamespaceName,
            CacheOwnerArgumentTimeOffset
        ), [CacheOwnerArgumentCallback](const TArray<FGs2ObjectPtr>& CacheOwnerValues)
        {
            TArray<Gs2::Experience::Model::FExperienceModelMasterPtr> CacheOwnerTypedValues;
            for (const auto& CacheOwnerValue : CacheOwnerValues) if (CacheOwnerValue) CacheOwnerTypedValues.Add(StaticCastSharedPtr<Gs2::Experience::Model::FExperienceModelMaster>(CacheOwnerValue));
            if (CacheOwnerArgumentCallback) CacheOwnerArgumentCallback(CacheOwnerTypedValues);
        });
    }

    void FExperienceModelMasterCache::ListUnsubscribe(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        Gs2::Core::Domain::CallbackID CacheOwnerArgumentCallbackID
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid()) return;
        CacheSnapshot->ListUnsubscribe(Gs2::Experience::Model::FExperienceModelMaster::TypeName, CreateCacheParentKey(
            CacheOwnerArgumentNamespaceName,
            CacheOwnerArgumentTimeOffset
        ), CacheOwnerArgumentCallbackID);
    }
}