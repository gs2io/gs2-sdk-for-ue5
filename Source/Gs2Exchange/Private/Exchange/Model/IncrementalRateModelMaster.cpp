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

#include "Exchange/Model/IncrementalRateModelMaster.h"

namespace Gs2::Exchange::Model
{
    FIncrementalRateModelMaster::FIncrementalRateModelMaster():
        IncrementalRateModelIdValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        ConsumeActionValue(nullptr),
        CalculateTypeValue(TOptional<FString>()),
        BaseValueValue(TOptional<int64>()),
        CoefficientValueValue(TOptional<int64>()),
        CalculateScriptIdValue(TOptional<FString>()),
        ExchangeCountIdValue(TOptional<FString>()),
        MaximumExchangeCountValue(TOptional<int32>()),
        AcquireActionsValue(nullptr),
        CreatedAtValue(TOptional<int64>()),
        UpdatedAtValue(TOptional<int64>()),
        RevisionValue(TOptional<int64>())
    {
    }

    FIncrementalRateModelMaster::FIncrementalRateModelMaster(
        const FIncrementalRateModelMaster& From
    ):
        IncrementalRateModelIdValue(From.IncrementalRateModelIdValue),
        NameValue(From.NameValue),
        DescriptionValue(From.DescriptionValue),
        MetadataValue(From.MetadataValue),
        ConsumeActionValue(From.ConsumeActionValue),
        CalculateTypeValue(From.CalculateTypeValue),
        BaseValueValue(From.BaseValueValue),
        CoefficientValueValue(From.CoefficientValueValue),
        CalculateScriptIdValue(From.CalculateScriptIdValue),
        ExchangeCountIdValue(From.ExchangeCountIdValue),
        MaximumExchangeCountValue(From.MaximumExchangeCountValue),
        AcquireActionsValue(From.AcquireActionsValue),
        CreatedAtValue(From.CreatedAtValue),
        UpdatedAtValue(From.UpdatedAtValue),
        RevisionValue(From.RevisionValue)
    {
    }

    TSharedPtr<FIncrementalRateModelMaster> FIncrementalRateModelMaster::WithIncrementalRateModelId(
        const TOptional<FString> IncrementalRateModelId
    )
    {
        this->IncrementalRateModelIdValue = IncrementalRateModelId;
        return SharedThis(this);
    }

    TSharedPtr<FIncrementalRateModelMaster> FIncrementalRateModelMaster::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FIncrementalRateModelMaster> FIncrementalRateModelMaster::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
        return SharedThis(this);
    }

    TSharedPtr<FIncrementalRateModelMaster> FIncrementalRateModelMaster::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FIncrementalRateModelMaster> FIncrementalRateModelMaster::WithConsumeAction(
        const TSharedPtr<FConsumeAction> ConsumeAction
    )
    {
        this->ConsumeActionValue = ConsumeAction;
        return SharedThis(this);
    }

    TSharedPtr<FIncrementalRateModelMaster> FIncrementalRateModelMaster::WithCalculateType(
        const TOptional<FString> CalculateType
    )
    {
        this->CalculateTypeValue = CalculateType;
        return SharedThis(this);
    }

    TSharedPtr<FIncrementalRateModelMaster> FIncrementalRateModelMaster::WithBaseValue(
        const TOptional<int64> BaseValue
    )
    {
        this->BaseValueValue = BaseValue;
        return SharedThis(this);
    }

    TSharedPtr<FIncrementalRateModelMaster> FIncrementalRateModelMaster::WithCoefficientValue(
        const TOptional<int64> CoefficientValue
    )
    {
        this->CoefficientValueValue = CoefficientValue;
        return SharedThis(this);
    }

    TSharedPtr<FIncrementalRateModelMaster> FIncrementalRateModelMaster::WithCalculateScriptId(
        const TOptional<FString> CalculateScriptId
    )
    {
        this->CalculateScriptIdValue = CalculateScriptId;
        return SharedThis(this);
    }

    TSharedPtr<FIncrementalRateModelMaster> FIncrementalRateModelMaster::WithExchangeCountId(
        const TOptional<FString> ExchangeCountId
    )
    {
        this->ExchangeCountIdValue = ExchangeCountId;
        return SharedThis(this);
    }

    TSharedPtr<FIncrementalRateModelMaster> FIncrementalRateModelMaster::WithMaximumExchangeCount(
        const TOptional<int32> MaximumExchangeCount
    )
    {
        this->MaximumExchangeCountValue = MaximumExchangeCount;
        return SharedThis(this);
    }

    TSharedPtr<FIncrementalRateModelMaster> FIncrementalRateModelMaster::WithAcquireActions(
        const TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> AcquireActions
    )
    {
        this->AcquireActionsValue = AcquireActions;
        return SharedThis(this);
    }

    TSharedPtr<FIncrementalRateModelMaster> FIncrementalRateModelMaster::WithCreatedAt(
        const TOptional<int64> CreatedAt
    )
    {
        this->CreatedAtValue = CreatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FIncrementalRateModelMaster> FIncrementalRateModelMaster::WithUpdatedAt(
        const TOptional<int64> UpdatedAt
    )
    {
        this->UpdatedAtValue = UpdatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FIncrementalRateModelMaster> FIncrementalRateModelMaster::WithRevision(
        const TOptional<int64> Revision
    )
    {
        this->RevisionValue = Revision;
        return SharedThis(this);
    }
    TOptional<FString> FIncrementalRateModelMaster::GetIncrementalRateModelId() const
    {
        return IncrementalRateModelIdValue;
    }
    TOptional<FString> FIncrementalRateModelMaster::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FIncrementalRateModelMaster::GetDescription() const
    {
        return DescriptionValue;
    }
    TOptional<FString> FIncrementalRateModelMaster::GetMetadata() const
    {
        return MetadataValue;
    }
    TSharedPtr<FConsumeAction> FIncrementalRateModelMaster::GetConsumeAction() const
    {
        return ConsumeActionValue;
    }
    TOptional<FString> FIncrementalRateModelMaster::GetCalculateType() const
    {
        return CalculateTypeValue;
    }
    TOptional<int64> FIncrementalRateModelMaster::GetBaseValue() const
    {
        return BaseValueValue;
    }

    FString FIncrementalRateModelMaster::GetBaseValueString() const
    {
        if (!BaseValueValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), BaseValueValue.GetValue());
    }
    TOptional<int64> FIncrementalRateModelMaster::GetCoefficientValue() const
    {
        return CoefficientValueValue;
    }

    FString FIncrementalRateModelMaster::GetCoefficientValueString() const
    {
        if (!CoefficientValueValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CoefficientValueValue.GetValue());
    }
    TOptional<FString> FIncrementalRateModelMaster::GetCalculateScriptId() const
    {
        return CalculateScriptIdValue;
    }
    TOptional<FString> FIncrementalRateModelMaster::GetExchangeCountId() const
    {
        return ExchangeCountIdValue;
    }
    TOptional<int32> FIncrementalRateModelMaster::GetMaximumExchangeCount() const
    {
        return MaximumExchangeCountValue;
    }

    FString FIncrementalRateModelMaster::GetMaximumExchangeCountString() const
    {
        if (!MaximumExchangeCountValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), MaximumExchangeCountValue.GetValue());
    }
    TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> FIncrementalRateModelMaster::GetAcquireActions() const
    {
        return AcquireActionsValue;
    }
    TOptional<int64> FIncrementalRateModelMaster::GetCreatedAt() const
    {
        return CreatedAtValue;
    }

    FString FIncrementalRateModelMaster::GetCreatedAtString() const
    {
        if (!CreatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue());
    }
    TOptional<int64> FIncrementalRateModelMaster::GetUpdatedAt() const
    {
        return UpdatedAtValue;
    }

    FString FIncrementalRateModelMaster::GetUpdatedAtString() const
    {
        if (!UpdatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), UpdatedAtValue.GetValue());
    }
    TOptional<int64> FIncrementalRateModelMaster::GetRevision() const
    {
        return RevisionValue;
    }

    FString FIncrementalRateModelMaster::GetRevisionString() const
    {
        if (!RevisionValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), RevisionValue.GetValue());
    }

    TOptional<FString> FIncrementalRateModelMaster::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):exchange:(?<namespaceName>.+):incremental:model:(?<rateName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FIncrementalRateModelMaster::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):exchange:(?<namespaceName>.+):incremental:model:(?<rateName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FIncrementalRateModelMaster::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):exchange:(?<namespaceName>.+):incremental:model:(?<rateName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FIncrementalRateModelMaster::GetRateNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):exchange:(?<namespaceName>.+):incremental:model:(?<rateName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FIncrementalRateModelMaster> FIncrementalRateModelMaster::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FIncrementalRateModelMaster>()
            ->WithIncrementalRateModelId(Data->HasField(ANSI_TO_TCHAR("incrementalRateModelId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("incrementalRateModelId"), v))
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
            ->WithConsumeAction(Data->HasField(ANSI_TO_TCHAR("consumeAction")) ? [Data]() -> Model::FConsumeActionPtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("consumeAction")))
                    {
                        return nullptr;
                    }
                    return Model::FConsumeAction::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("consumeAction")));
                 }() : nullptr)
            ->WithCalculateType(Data->HasField(ANSI_TO_TCHAR("calculateType")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("calculateType"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithBaseValue(Data->HasField(ANSI_TO_TCHAR("baseValue")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("baseValue"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithCoefficientValue(Data->HasField(ANSI_TO_TCHAR("coefficientValue")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("coefficientValue"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithCalculateScriptId(Data->HasField(ANSI_TO_TCHAR("calculateScriptId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("calculateScriptId"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithExchangeCountId(Data->HasField(ANSI_TO_TCHAR("exchangeCountId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("exchangeCountId"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithMaximumExchangeCount(Data->HasField(ANSI_TO_TCHAR("maximumExchangeCount")) ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("maximumExchangeCount"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithAcquireActions(Data->HasField(ANSI_TO_TCHAR("acquireActions")) ? [Data]() -> TSharedPtr<TArray<Model::FAcquireActionPtr>>
                {
                    if (!Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("acquireActions")))
                    {
                        return nullptr;
                    }
                    auto v = MakeShared<TArray<Model::FAcquireActionPtr>>();
                    for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("acquireActions")))
                    {
                        v->Add(Model::FAcquireAction::FromJson(JsonObjectValue->AsObject()));
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

    TSharedPtr<FJsonObject> FIncrementalRateModelMaster::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (IncrementalRateModelIdValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("incrementalRateModelId"), IncrementalRateModelIdValue.GetValue());
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
        if (ConsumeActionValue != nullptr && ConsumeActionValue.IsValid())
        {
            JsonRootObject->SetObjectField(TEXT("consumeAction"), ConsumeActionValue->ToJson());
        }
        if (CalculateTypeValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("calculateType"), CalculateTypeValue.GetValue());
        }
        if (BaseValueValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("baseValue"), FString::Printf(TEXT("%lld"), BaseValueValue.GetValue()));
        }
        if (CoefficientValueValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("coefficientValue"), FString::Printf(TEXT("%lld"), CoefficientValueValue.GetValue()));
        }
        if (CalculateScriptIdValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("calculateScriptId"), CalculateScriptIdValue.GetValue());
        }
        if (ExchangeCountIdValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("exchangeCountId"), ExchangeCountIdValue.GetValue());
        }
        if (MaximumExchangeCountValue.IsSet())
        {
            JsonRootObject->SetNumberField(TEXT("maximumExchangeCount"), MaximumExchangeCountValue.GetValue());
        }
        if (AcquireActionsValue != nullptr && AcquireActionsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *AcquireActionsValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField(TEXT("acquireActions"), v);
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

    FString FIncrementalRateModelMaster::TypeName = "IncrementalRateModelMaster";
}
#include "Exchange/Model/Cache/IncrementalRateModelMaster.h"

namespace Gs2::Exchange::Model::Cache
{
    FString FIncrementalRateModelMasterCache::CreateCacheParentKey(
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<int32> CacheOwnerArgumentTimeOffset
    )
    {
        return FString("exchange:")
            + CacheOwnerArgumentNamespaceName.Get(FString()) + FString(":")
            + FString::FromInt(CacheOwnerArgumentTimeOffset.Get(0)) + FString(":IncrementalRateModelMaster");
    }

    FString FIncrementalRateModelMasterCache::CreateCacheKey(
        TOptional<FString> CacheOwnerArgumentRateName
    )
    {
        return
            FString()
            + CacheOwnerArgumentRateName.Get(FString())
            ;
    }

    bool FIncrementalRateModelMasterCache::TryGet(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<FString> CacheOwnerArgumentRateName,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        Gs2::Exchange::Model::FIncrementalRateModelMasterPtr* CacheOwnerArgumentOutItem
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid())
        {
            if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
            return false;
        }
        if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
        Gs2::Exchange::Model::FIncrementalRateModelMasterPtr CacheOwnerValue;
        const bool CacheOwnerFound = CacheSnapshot->TryGet<Gs2::Exchange::Model::FIncrementalRateModelMaster>(
            CreateCacheParentKey(
                CacheOwnerArgumentNamespaceName,
                CacheOwnerArgumentTimeOffset
            ),
            CreateCacheKey(
                CacheOwnerArgumentRateName
            ),
            &CacheOwnerValue
        );
        if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = CacheOwnerFound ? CacheOwnerValue : nullptr;
        return CacheOwnerFound;
    }

    void FIncrementalRateModelMasterCache::Put(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<FString> CacheOwnerArgumentRateName,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        const Gs2::Exchange::Model::FIncrementalRateModelMasterPtr& CacheOwnerArgumentItem
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid()) return;
        const auto CacheOwnerParentKey = CreateCacheParentKey(
            CacheOwnerArgumentNamespaceName,
            CacheOwnerArgumentTimeOffset
        );
        const auto CacheOwnerKey = CreateCacheKey(
            CacheOwnerArgumentRateName
        );
        auto CacheOwnerValue = CacheOwnerArgumentItem;
        Gs2::Exchange::Model::FIncrementalRateModelMasterPtr CacheOwnerExisting;
        if (CacheSnapshot->TryGet<Gs2::Exchange::Model::FIncrementalRateModelMaster>(CacheOwnerParentKey, CacheOwnerKey, &CacheOwnerExisting))
        {
            const int64 CacheOwnerOldRevision = CacheOwnerExisting.IsValid() ? CacheOwnerExisting->GetRevision().Get(-1) : -1;
            const int64 CacheOwnerNewRevision = CacheOwnerValue.IsValid() ? CacheOwnerValue->GetRevision().Get(-1) : -1;
            if (CacheOwnerOldRevision > CacheOwnerNewRevision && CacheOwnerNewRevision > 1) return;
            if (CacheOwnerOldRevision == CacheOwnerNewRevision) return;
        }
        CacheSnapshot->Put(Gs2::Exchange::Model::FIncrementalRateModelMaster::TypeName, CacheOwnerParentKey, CacheOwnerKey, CacheOwnerValue,
            FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
        );
    }

    FString FIncrementalRateModelMasterCache::PutUserData(
        const Gs2::Core::Domain::FCacheDatabasePtr& Cache,
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<int32> TimeOffset,
        const Gs2::Exchange::Model::FIncrementalRateModelMasterPtr& Item
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

    void FIncrementalRateModelMasterCache::Delete(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<FString> CacheOwnerArgumentRateName,
        TOptional<int32> CacheOwnerArgumentTimeOffset
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid()) return;
        CacheSnapshot->Delete(Gs2::Exchange::Model::FIncrementalRateModelMaster::TypeName, CreateCacheParentKey(
            CacheOwnerArgumentNamespaceName,
            CacheOwnerArgumentTimeOffset
        ), CreateCacheKey(
            CacheOwnerArgumentRateName
        ));
    }

    Gs2::Core::Model::FGs2ErrorPtr FIncrementalRateModelMasterCache::Fetch(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<FString> CacheOwnerArgumentRateName,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        const TFunction<Gs2::Core::Model::FGs2ErrorPtr(Gs2::Exchange::Model::FIncrementalRateModelMasterPtr*)>& CacheOwnerArgumentFetchImpl,
        Gs2::Exchange::Model::FIncrementalRateModelMasterPtr* CacheOwnerArgumentOutItem
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
        Gs2::Exchange::Model::FIncrementalRateModelMasterPtr CacheOwnerFetchedItem;
        const auto CacheOwnerError = FetchImplSnapshot(&CacheOwnerFetchedItem);
        if (!CacheOwnerError)
        {
            Put(
                CacheSnapshot,
                CacheOwnerArgumentNamespaceName,
                CacheOwnerArgumentRateName,
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
            CacheOwnerArgumentRateName,
            CacheOwnerArgumentTimeOffset,
            nullptr
        );
        if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
        const auto CacheOwnerDetails = CacheOwnerError->GetErrors();
        if (CacheOwnerDetails.IsValid() && CacheOwnerDetails->Num() > 0 && (*CacheOwnerDetails)[0].IsValid() && (*CacheOwnerDetails)[0]->GetComponent() == TEXT("incrementalRateModelMaster"))
        {
            return nullptr;
        }
        if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
        return CacheOwnerError;
    }

    Gs2::Core::Domain::CallbackID FIncrementalRateModelMasterCache::ListSubscribe(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        TFunction<void(TArray<Gs2::Exchange::Model::FIncrementalRateModelMasterPtr>)> CacheOwnerArgumentCallback
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid()) return 0;
        return CacheSnapshot->ListSubscribeTyped(Gs2::Exchange::Model::FIncrementalRateModelMaster::TypeName, CreateCacheParentKey(
            CacheOwnerArgumentNamespaceName,
            CacheOwnerArgumentTimeOffset
        ), [CacheOwnerArgumentCallback](const TArray<FGs2ObjectPtr>& CacheOwnerValues)
        {
            TArray<Gs2::Exchange::Model::FIncrementalRateModelMasterPtr> CacheOwnerTypedValues;
            for (const auto& CacheOwnerValue : CacheOwnerValues) if (CacheOwnerValue) CacheOwnerTypedValues.Add(StaticCastSharedPtr<Gs2::Exchange::Model::FIncrementalRateModelMaster>(CacheOwnerValue));
            if (CacheOwnerArgumentCallback) CacheOwnerArgumentCallback(CacheOwnerTypedValues);
        });
    }

    void FIncrementalRateModelMasterCache::ListUnsubscribe(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        Gs2::Core::Domain::CallbackID CacheOwnerArgumentCallbackID
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid()) return;
        CacheSnapshot->ListUnsubscribe(Gs2::Exchange::Model::FIncrementalRateModelMaster::TypeName, CreateCacheParentKey(
            CacheOwnerArgumentNamespaceName,
            CacheOwnerArgumentTimeOffset
        ), CacheOwnerArgumentCallbackID);
    }
}