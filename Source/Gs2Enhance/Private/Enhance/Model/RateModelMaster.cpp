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

#include "Enhance/Model/RateModelMaster.h"

namespace Gs2::Enhance::Model
{
    FRateModelMaster::FRateModelMaster():
        RateModelIdValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        TargetInventoryModelIdValue(TOptional<FString>()),
        AcquireExperienceSuffixValue(TOptional<FString>()),
        MaterialInventoryModelIdValue(TOptional<FString>()),
        AcquireExperienceHierarchyValue(nullptr),
        ExperienceModelIdValue(TOptional<FString>()),
        BonusRatesValue(nullptr),
        CreatedAtValue(TOptional<int64>()),
        UpdatedAtValue(TOptional<int64>()),
        RevisionValue(TOptional<int64>())
    {
    }

    FRateModelMaster::FRateModelMaster(
        const FRateModelMaster& From
    ):
        RateModelIdValue(From.RateModelIdValue),
        NameValue(From.NameValue),
        DescriptionValue(From.DescriptionValue),
        MetadataValue(From.MetadataValue),
        TargetInventoryModelIdValue(From.TargetInventoryModelIdValue),
        AcquireExperienceSuffixValue(From.AcquireExperienceSuffixValue),
        MaterialInventoryModelIdValue(From.MaterialInventoryModelIdValue),
        AcquireExperienceHierarchyValue(From.AcquireExperienceHierarchyValue),
        ExperienceModelIdValue(From.ExperienceModelIdValue),
        BonusRatesValue(From.BonusRatesValue),
        CreatedAtValue(From.CreatedAtValue),
        UpdatedAtValue(From.UpdatedAtValue),
        RevisionValue(From.RevisionValue)
    {
    }

    TSharedPtr<FRateModelMaster> FRateModelMaster::WithRateModelId(
        const TOptional<FString> RateModelId
    )
    {
        this->RateModelIdValue = RateModelId;
        return SharedThis(this);
    }

    TSharedPtr<FRateModelMaster> FRateModelMaster::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FRateModelMaster> FRateModelMaster::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
        return SharedThis(this);
    }

    TSharedPtr<FRateModelMaster> FRateModelMaster::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FRateModelMaster> FRateModelMaster::WithTargetInventoryModelId(
        const TOptional<FString> TargetInventoryModelId
    )
    {
        this->TargetInventoryModelIdValue = TargetInventoryModelId;
        return SharedThis(this);
    }

    TSharedPtr<FRateModelMaster> FRateModelMaster::WithAcquireExperienceSuffix(
        const TOptional<FString> AcquireExperienceSuffix
    )
    {
        this->AcquireExperienceSuffixValue = AcquireExperienceSuffix;
        return SharedThis(this);
    }

    TSharedPtr<FRateModelMaster> FRateModelMaster::WithMaterialInventoryModelId(
        const TOptional<FString> MaterialInventoryModelId
    )
    {
        this->MaterialInventoryModelIdValue = MaterialInventoryModelId;
        return SharedThis(this);
    }

    TSharedPtr<FRateModelMaster> FRateModelMaster::WithAcquireExperienceHierarchy(
        const TSharedPtr<TArray<FString>> AcquireExperienceHierarchy
    )
    {
        this->AcquireExperienceHierarchyValue = AcquireExperienceHierarchy;
        return SharedThis(this);
    }

    TSharedPtr<FRateModelMaster> FRateModelMaster::WithExperienceModelId(
        const TOptional<FString> ExperienceModelId
    )
    {
        this->ExperienceModelIdValue = ExperienceModelId;
        return SharedThis(this);
    }

    TSharedPtr<FRateModelMaster> FRateModelMaster::WithBonusRates(
        const TSharedPtr<TArray<TSharedPtr<Model::FBonusRate>>> BonusRates
    )
    {
        this->BonusRatesValue = BonusRates;
        return SharedThis(this);
    }

    TSharedPtr<FRateModelMaster> FRateModelMaster::WithCreatedAt(
        const TOptional<int64> CreatedAt
    )
    {
        this->CreatedAtValue = CreatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FRateModelMaster> FRateModelMaster::WithUpdatedAt(
        const TOptional<int64> UpdatedAt
    )
    {
        this->UpdatedAtValue = UpdatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FRateModelMaster> FRateModelMaster::WithRevision(
        const TOptional<int64> Revision
    )
    {
        this->RevisionValue = Revision;
        return SharedThis(this);
    }
    TOptional<FString> FRateModelMaster::GetRateModelId() const
    {
        return RateModelIdValue;
    }
    TOptional<FString> FRateModelMaster::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FRateModelMaster::GetDescription() const
    {
        return DescriptionValue;
    }
    TOptional<FString> FRateModelMaster::GetMetadata() const
    {
        return MetadataValue;
    }
    TOptional<FString> FRateModelMaster::GetTargetInventoryModelId() const
    {
        return TargetInventoryModelIdValue;
    }
    TOptional<FString> FRateModelMaster::GetAcquireExperienceSuffix() const
    {
        return AcquireExperienceSuffixValue;
    }
    TOptional<FString> FRateModelMaster::GetMaterialInventoryModelId() const
    {
        return MaterialInventoryModelIdValue;
    }
    TSharedPtr<TArray<FString>> FRateModelMaster::GetAcquireExperienceHierarchy() const
    {
        return AcquireExperienceHierarchyValue;
    }
    TOptional<FString> FRateModelMaster::GetExperienceModelId() const
    {
        return ExperienceModelIdValue;
    }
    TSharedPtr<TArray<TSharedPtr<Model::FBonusRate>>> FRateModelMaster::GetBonusRates() const
    {
        return BonusRatesValue;
    }
    TOptional<int64> FRateModelMaster::GetCreatedAt() const
    {
        return CreatedAtValue;
    }

    FString FRateModelMaster::GetCreatedAtString() const
    {
        if (!CreatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue());
    }
    TOptional<int64> FRateModelMaster::GetUpdatedAt() const
    {
        return UpdatedAtValue;
    }

    FString FRateModelMaster::GetUpdatedAtString() const
    {
        if (!UpdatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), UpdatedAtValue.GetValue());
    }
    TOptional<int64> FRateModelMaster::GetRevision() const
    {
        return RevisionValue;
    }

    FString FRateModelMaster::GetRevisionString() const
    {
        if (!RevisionValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), RevisionValue.GetValue());
    }

    TOptional<FString> FRateModelMaster::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):enhance:(?<namespaceName>.+):rateModelMaster:(?<rateName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FRateModelMaster::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):enhance:(?<namespaceName>.+):rateModelMaster:(?<rateName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FRateModelMaster::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):enhance:(?<namespaceName>.+):rateModelMaster:(?<rateName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FRateModelMaster::GetRateNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):enhance:(?<namespaceName>.+):rateModelMaster:(?<rateName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FRateModelMaster> FRateModelMaster::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FRateModelMaster>()
            ->WithRateModelId(Data->HasField("rateModelId") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("rateModelId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithName(Data->HasField("name") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("name", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithDescription(Data->HasField("description") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("description", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithMetadata(Data->HasField("metadata") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("metadata", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithTargetInventoryModelId(Data->HasField("targetInventoryModelId") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("targetInventoryModelId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithAcquireExperienceSuffix(Data->HasField("acquireExperienceSuffix") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("acquireExperienceSuffix", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithMaterialInventoryModelId(Data->HasField("materialInventoryModelId") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("materialInventoryModelId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithAcquireExperienceHierarchy(Data->HasField("acquireExperienceHierarchy") ? [Data]() -> TSharedPtr<TArray<FString>>
                {
                    auto v = MakeShared<TArray<FString>>();
                    if (!Data->HasTypedField<EJson::Null>("acquireExperienceHierarchy") && Data->HasTypedField<EJson::Array>("acquireExperienceHierarchy"))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField("acquireExperienceHierarchy"))
                        {
                            v->Add(JsonObjectValue->AsString());
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<FString>>())
            ->WithExperienceModelId(Data->HasField("experienceModelId") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("experienceModelId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithBonusRates(Data->HasField("bonusRates") ? [Data]() -> TSharedPtr<TArray<Model::FBonusRatePtr>>
                {
                    auto v = MakeShared<TArray<Model::FBonusRatePtr>>();
                    if (!Data->HasTypedField<EJson::Null>("bonusRates") && Data->HasTypedField<EJson::Array>("bonusRates"))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField("bonusRates"))
                        {
                            v->Add(Model::FBonusRate::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<Model::FBonusRatePtr>>())
            ->WithCreatedAt(Data->HasField("createdAt") ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField("createdAt", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithUpdatedAt(Data->HasField("updatedAt") ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField("updatedAt", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithRevision(Data->HasField("revision") ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField("revision", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>());
    }

    TSharedPtr<FJsonObject> FRateModelMaster::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (RateModelIdValue.IsSet())
        {
            JsonRootObject->SetStringField("rateModelId", RateModelIdValue.GetValue());
        }
        if (NameValue.IsSet())
        {
            JsonRootObject->SetStringField("name", NameValue.GetValue());
        }
        if (DescriptionValue.IsSet())
        {
            JsonRootObject->SetStringField("description", DescriptionValue.GetValue());
        }
        if (MetadataValue.IsSet())
        {
            JsonRootObject->SetStringField("metadata", MetadataValue.GetValue());
        }
        if (TargetInventoryModelIdValue.IsSet())
        {
            JsonRootObject->SetStringField("targetInventoryModelId", TargetInventoryModelIdValue.GetValue());
        }
        if (AcquireExperienceSuffixValue.IsSet())
        {
            JsonRootObject->SetStringField("acquireExperienceSuffix", AcquireExperienceSuffixValue.GetValue());
        }
        if (MaterialInventoryModelIdValue.IsSet())
        {
            JsonRootObject->SetStringField("materialInventoryModelId", MaterialInventoryModelIdValue.GetValue());
        }
        if (AcquireExperienceHierarchyValue != nullptr && AcquireExperienceHierarchyValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *AcquireExperienceHierarchyValue)
            {
                v.Add(MakeShared<FJsonValueString>(JsonObjectValue));
            }
            JsonRootObject->SetArrayField("acquireExperienceHierarchy", v);
        }
        if (ExperienceModelIdValue.IsSet())
        {
            JsonRootObject->SetStringField("experienceModelId", ExperienceModelIdValue.GetValue());
        }
        if (BonusRatesValue != nullptr && BonusRatesValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *BonusRatesValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("bonusRates", v);
        }
        if (CreatedAtValue.IsSet())
        {
            JsonRootObject->SetStringField("createdAt", FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue()));
        }
        if (UpdatedAtValue.IsSet())
        {
            JsonRootObject->SetStringField("updatedAt", FString::Printf(TEXT("%lld"), UpdatedAtValue.GetValue()));
        }
        if (RevisionValue.IsSet())
        {
            JsonRootObject->SetStringField("revision", FString::Printf(TEXT("%lld"), RevisionValue.GetValue()));
        }
        return JsonRootObject;
    }

    FString FRateModelMaster::TypeName = "RateModelMaster";
}