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

#include "SkillTree/Model/NodeModelMaster.h"

namespace Gs2::SkillTree::Model
{
    FNodeModelMaster::FNodeModelMaster():
        NodeModelIdValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        ReleaseVerifyActionsValue(nullptr),
        ReleaseConsumeActionsValue(nullptr),
        RestrainReturnRateValue(TOptional<float>()),
        PremiseNodeNamesValue(nullptr),
        CreatedAtValue(TOptional<int64>()),
        UpdatedAtValue(TOptional<int64>()),
        RevisionValue(TOptional<int64>())
    {
    }

    FNodeModelMaster::FNodeModelMaster(
        const FNodeModelMaster& From
    ):
        NodeModelIdValue(From.NodeModelIdValue),
        NameValue(From.NameValue),
        DescriptionValue(From.DescriptionValue),
        MetadataValue(From.MetadataValue),
        ReleaseVerifyActionsValue(From.ReleaseVerifyActionsValue),
        ReleaseConsumeActionsValue(From.ReleaseConsumeActionsValue),
        RestrainReturnRateValue(From.RestrainReturnRateValue),
        PremiseNodeNamesValue(From.PremiseNodeNamesValue),
        CreatedAtValue(From.CreatedAtValue),
        UpdatedAtValue(From.UpdatedAtValue),
        RevisionValue(From.RevisionValue)
    {
    }

    TSharedPtr<FNodeModelMaster> FNodeModelMaster::WithNodeModelId(
        const TOptional<FString> NodeModelId
    )
    {
        this->NodeModelIdValue = NodeModelId;
        return SharedThis(this);
    }

    TSharedPtr<FNodeModelMaster> FNodeModelMaster::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FNodeModelMaster> FNodeModelMaster::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
        return SharedThis(this);
    }

    TSharedPtr<FNodeModelMaster> FNodeModelMaster::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FNodeModelMaster> FNodeModelMaster::WithReleaseVerifyActions(
        const TSharedPtr<TArray<TSharedPtr<Model::FVerifyAction>>> ReleaseVerifyActions
    )
    {
        this->ReleaseVerifyActionsValue = ReleaseVerifyActions;
        return SharedThis(this);
    }

    TSharedPtr<FNodeModelMaster> FNodeModelMaster::WithReleaseConsumeActions(
        const TSharedPtr<TArray<TSharedPtr<Model::FConsumeAction>>> ReleaseConsumeActions
    )
    {
        this->ReleaseConsumeActionsValue = ReleaseConsumeActions;
        return SharedThis(this);
    }

    TSharedPtr<FNodeModelMaster> FNodeModelMaster::WithRestrainReturnRate(
        const TOptional<float> RestrainReturnRate
    )
    {
        this->RestrainReturnRateValue = RestrainReturnRate;
        return SharedThis(this);
    }

    TSharedPtr<FNodeModelMaster> FNodeModelMaster::WithPremiseNodeNames(
        const TSharedPtr<TArray<FString>> PremiseNodeNames
    )
    {
        this->PremiseNodeNamesValue = PremiseNodeNames;
        return SharedThis(this);
    }

    TSharedPtr<FNodeModelMaster> FNodeModelMaster::WithCreatedAt(
        const TOptional<int64> CreatedAt
    )
    {
        this->CreatedAtValue = CreatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FNodeModelMaster> FNodeModelMaster::WithUpdatedAt(
        const TOptional<int64> UpdatedAt
    )
    {
        this->UpdatedAtValue = UpdatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FNodeModelMaster> FNodeModelMaster::WithRevision(
        const TOptional<int64> Revision
    )
    {
        this->RevisionValue = Revision;
        return SharedThis(this);
    }
    TOptional<FString> FNodeModelMaster::GetNodeModelId() const
    {
        return NodeModelIdValue;
    }
    TOptional<FString> FNodeModelMaster::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FNodeModelMaster::GetDescription() const
    {
        return DescriptionValue;
    }
    TOptional<FString> FNodeModelMaster::GetMetadata() const
    {
        return MetadataValue;
    }
    TSharedPtr<TArray<TSharedPtr<Model::FVerifyAction>>> FNodeModelMaster::GetReleaseVerifyActions() const
    {
        return ReleaseVerifyActionsValue;
    }
    TSharedPtr<TArray<TSharedPtr<Model::FConsumeAction>>> FNodeModelMaster::GetReleaseConsumeActions() const
    {
        return ReleaseConsumeActionsValue;
    }
    TOptional<float> FNodeModelMaster::GetRestrainReturnRate() const
    {
        return RestrainReturnRateValue;
    }

    FString FNodeModelMaster::GetRestrainReturnRateString() const
    {
        if (!RestrainReturnRateValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%f"), RestrainReturnRateValue.GetValue());
    }
    TSharedPtr<TArray<FString>> FNodeModelMaster::GetPremiseNodeNames() const
    {
        return PremiseNodeNamesValue;
    }
    TOptional<int64> FNodeModelMaster::GetCreatedAt() const
    {
        return CreatedAtValue;
    }

    FString FNodeModelMaster::GetCreatedAtString() const
    {
        if (!CreatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue());
    }
    TOptional<int64> FNodeModelMaster::GetUpdatedAt() const
    {
        return UpdatedAtValue;
    }

    FString FNodeModelMaster::GetUpdatedAtString() const
    {
        if (!UpdatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), UpdatedAtValue.GetValue());
    }
    TOptional<int64> FNodeModelMaster::GetRevision() const
    {
        return RevisionValue;
    }

    FString FNodeModelMaster::GetRevisionString() const
    {
        if (!RevisionValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), RevisionValue.GetValue());
    }

    TOptional<FString> FNodeModelMaster::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):skillTree:(?<namespaceName>.+):model:(?<nodeModelName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FNodeModelMaster::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):skillTree:(?<namespaceName>.+):model:(?<nodeModelName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FNodeModelMaster::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):skillTree:(?<namespaceName>.+):model:(?<nodeModelName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FNodeModelMaster::GetNodeModelNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):skillTree:(?<namespaceName>.+):model:(?<nodeModelName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FNodeModelMaster> FNodeModelMaster::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FNodeModelMaster>()
            ->WithNodeModelId(Data->HasField(ANSI_TO_TCHAR("nodeModelId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("nodeModelId"), v))
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
            ->WithReleaseVerifyActions(Data->HasField(ANSI_TO_TCHAR("releaseVerifyActions")) ? [Data]() -> TSharedPtr<TArray<Model::FVerifyActionPtr>>
                {
                    if (!Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("releaseVerifyActions")))
                    {
                        return nullptr;
                    }
                    auto v = MakeShared<TArray<Model::FVerifyActionPtr>>();
                    for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("releaseVerifyActions")))
                    {
                        v->Add(Model::FVerifyAction::FromJson(JsonObjectValue->AsObject()));
                    }
                    return v;
                 }() : nullptr)
            ->WithReleaseConsumeActions(Data->HasField(ANSI_TO_TCHAR("releaseConsumeActions")) ? [Data]() -> TSharedPtr<TArray<Model::FConsumeActionPtr>>
                {
                    if (!Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("releaseConsumeActions")))
                    {
                        return nullptr;
                    }
                    auto v = MakeShared<TArray<Model::FConsumeActionPtr>>();
                    for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("releaseConsumeActions")))
                    {
                        v->Add(Model::FConsumeAction::FromJson(JsonObjectValue->AsObject()));
                    }
                    return v;
                 }() : nullptr)
            ->WithRestrainReturnRate(Data->HasField(ANSI_TO_TCHAR("restrainReturnRate")) ? [Data]() -> TOptional<float>
                {
                    float v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("restrainReturnRate"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<float>();
                }() : TOptional<float>())
            ->WithPremiseNodeNames(Data->HasField(ANSI_TO_TCHAR("premiseNodeNames")) ? [Data]() -> TSharedPtr<TArray<FString>>
                {
                    if (!Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("premiseNodeNames")))
                    {
                        return nullptr;
                    }
                    auto v = MakeShared<TArray<FString>>();
                    for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("premiseNodeNames")))
                    {
                        v->Add(JsonObjectValue->AsString());
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

    TSharedPtr<FJsonObject> FNodeModelMaster::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (NodeModelIdValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("nodeModelId"), NodeModelIdValue.GetValue());
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
        if (ReleaseVerifyActionsValue != nullptr && ReleaseVerifyActionsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *ReleaseVerifyActionsValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField(TEXT("releaseVerifyActions"), v);
        }
        if (ReleaseConsumeActionsValue != nullptr && ReleaseConsumeActionsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *ReleaseConsumeActionsValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField(TEXT("releaseConsumeActions"), v);
        }
        if (RestrainReturnRateValue.IsSet())
        {
            JsonRootObject->SetNumberField(TEXT("restrainReturnRate"), RestrainReturnRateValue.GetValue());
        }
        if (PremiseNodeNamesValue != nullptr && PremiseNodeNamesValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *PremiseNodeNamesValue)
            {
                v.Add(MakeShared<FJsonValueString>(JsonObjectValue));
            }
            JsonRootObject->SetArrayField(TEXT("premiseNodeNames"), v);
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

    FString FNodeModelMaster::TypeName = "NodeModelMaster";
}
#include "SkillTree/Model/Cache/NodeModelMaster.h"

namespace Gs2::SkillTree::Model::Cache
{
    FString FNodeModelMasterCache::CreateCacheParentKey(
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<int32> CacheOwnerArgumentTimeOffset
    )
    {
        return FString("skillTree:")
            + CacheOwnerArgumentNamespaceName.Get(FString()) + FString(":")
            + FString::FromInt(CacheOwnerArgumentTimeOffset.Get(0)) + FString(":NodeModelMaster");
    }

    FString FNodeModelMasterCache::CreateCacheKey(
        TOptional<FString> CacheOwnerArgumentNodeModelName
    )
    {
        return
            FString()
            + CacheOwnerArgumentNodeModelName.Get(FString())
            ;
    }

    bool FNodeModelMasterCache::TryGet(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<FString> CacheOwnerArgumentNodeModelName,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        Gs2::SkillTree::Model::FNodeModelMasterPtr* CacheOwnerArgumentOutItem
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid())
        {
            if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
            return false;
        }
        if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
        Gs2::SkillTree::Model::FNodeModelMasterPtr CacheOwnerValue;
        const bool CacheOwnerFound = CacheSnapshot->TryGet<Gs2::SkillTree::Model::FNodeModelMaster>(
            CreateCacheParentKey(
                CacheOwnerArgumentNamespaceName,
                CacheOwnerArgumentTimeOffset
            ),
            CreateCacheKey(
                CacheOwnerArgumentNodeModelName
            ),
            &CacheOwnerValue
        );
        if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = CacheOwnerFound ? CacheOwnerValue : nullptr;
        return CacheOwnerFound;
    }

    void FNodeModelMasterCache::Put(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<FString> CacheOwnerArgumentNodeModelName,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        const Gs2::SkillTree::Model::FNodeModelMasterPtr& CacheOwnerArgumentItem
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid()) return;
        const auto CacheOwnerParentKey = CreateCacheParentKey(
            CacheOwnerArgumentNamespaceName,
            CacheOwnerArgumentTimeOffset
        );
        const auto CacheOwnerKey = CreateCacheKey(
            CacheOwnerArgumentNodeModelName
        );
        auto CacheOwnerValue = CacheOwnerArgumentItem;
        Gs2::SkillTree::Model::FNodeModelMasterPtr CacheOwnerExisting;
        if (CacheSnapshot->TryGet<Gs2::SkillTree::Model::FNodeModelMaster>(CacheOwnerParentKey, CacheOwnerKey, &CacheOwnerExisting))
        {
            const int64 CacheOwnerOldRevision = CacheOwnerExisting.IsValid() ? CacheOwnerExisting->GetRevision().Get(-1) : -1;
            const int64 CacheOwnerNewRevision = CacheOwnerValue.IsValid() ? CacheOwnerValue->GetRevision().Get(-1) : -1;
            if (CacheOwnerOldRevision > CacheOwnerNewRevision && CacheOwnerNewRevision > 1) return;
            if (CacheOwnerOldRevision == CacheOwnerNewRevision) return;
        }
        CacheSnapshot->Put(Gs2::SkillTree::Model::FNodeModelMaster::TypeName, CacheOwnerParentKey, CacheOwnerKey, CacheOwnerValue,
            FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
        );
    }

    FString FNodeModelMasterCache::PutUserData(
        const Gs2::Core::Domain::FCacheDatabasePtr& Cache,
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<int32> TimeOffset,
        const Gs2::SkillTree::Model::FNodeModelMasterPtr& Item
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

    void FNodeModelMasterCache::Delete(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<FString> CacheOwnerArgumentNodeModelName,
        TOptional<int32> CacheOwnerArgumentTimeOffset
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid()) return;
        CacheSnapshot->Delete(Gs2::SkillTree::Model::FNodeModelMaster::TypeName, CreateCacheParentKey(
            CacheOwnerArgumentNamespaceName,
            CacheOwnerArgumentTimeOffset
        ), CreateCacheKey(
            CacheOwnerArgumentNodeModelName
        ));
    }

    Gs2::Core::Model::FGs2ErrorPtr FNodeModelMasterCache::Fetch(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<FString> CacheOwnerArgumentNodeModelName,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        const TFunction<Gs2::Core::Model::FGs2ErrorPtr(Gs2::SkillTree::Model::FNodeModelMasterPtr*)>& CacheOwnerArgumentFetchImpl,
        Gs2::SkillTree::Model::FNodeModelMasterPtr* CacheOwnerArgumentOutItem
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
        Gs2::SkillTree::Model::FNodeModelMasterPtr CacheOwnerFetchedItem;
        const auto CacheOwnerError = FetchImplSnapshot(&CacheOwnerFetchedItem);
        if (!CacheOwnerError)
        {
            Put(
                CacheSnapshot,
                CacheOwnerArgumentNamespaceName,
                CacheOwnerArgumentNodeModelName,
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
            CacheOwnerArgumentNodeModelName,
            CacheOwnerArgumentTimeOffset,
            nullptr
        );
        if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
        const auto CacheOwnerDetails = CacheOwnerError->GetErrors();
        if (CacheOwnerDetails.IsValid() && CacheOwnerDetails->Num() > 0 && (*CacheOwnerDetails)[0].IsValid() && (*CacheOwnerDetails)[0]->GetComponent() == TEXT("nodeModelMaster"))
        {
            return nullptr;
        }
        if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
        return CacheOwnerError;
    }

    Gs2::Core::Domain::CallbackID FNodeModelMasterCache::ListSubscribe(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        TFunction<void(TArray<Gs2::SkillTree::Model::FNodeModelMasterPtr>)> CacheOwnerArgumentCallback
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid()) return 0;
        return CacheSnapshot->ListSubscribeTyped(Gs2::SkillTree::Model::FNodeModelMaster::TypeName, CreateCacheParentKey(
            CacheOwnerArgumentNamespaceName,
            CacheOwnerArgumentTimeOffset
        ), [CacheOwnerArgumentCallback](const TArray<FGs2ObjectPtr>& CacheOwnerValues)
        {
            TArray<Gs2::SkillTree::Model::FNodeModelMasterPtr> CacheOwnerTypedValues;
            for (const auto& CacheOwnerValue : CacheOwnerValues) if (CacheOwnerValue) CacheOwnerTypedValues.Add(StaticCastSharedPtr<Gs2::SkillTree::Model::FNodeModelMaster>(CacheOwnerValue));
            if (CacheOwnerArgumentCallback) CacheOwnerArgumentCallback(CacheOwnerTypedValues);
        });
    }

    void FNodeModelMasterCache::ListUnsubscribe(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        Gs2::Core::Domain::CallbackID CacheOwnerArgumentCallbackID
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid()) return;
        CacheSnapshot->ListUnsubscribe(Gs2::SkillTree::Model::FNodeModelMaster::TypeName, CreateCacheParentKey(
            CacheOwnerArgumentNamespaceName,
            CacheOwnerArgumentTimeOffset
        ), CacheOwnerArgumentCallbackID);
    }
}