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

#include "Enhance/Model/RateModel.h"

namespace Gs2::Enhance::Model
{
    FRateModel::FRateModel():
        RateModelIdValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        TargetInventoryModelIdValue(TOptional<FString>()),
        AcquireExperienceSuffixValue(TOptional<FString>()),
        MaterialInventoryModelIdValue(TOptional<FString>()),
        AcquireExperienceHierarchyValue(nullptr),
        ExperienceModelIdValue(TOptional<FString>()),
        BonusRatesValue(nullptr)
    {
    }

    FRateModel::FRateModel(
        const FRateModel& From
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
        BonusRatesValue(From.BonusRatesValue)
    {
    }

    TSharedPtr<FRateModel> FRateModel::WithRateModelId(
        const TOptional<FString> RateModelId
    )
    {
        this->RateModelIdValue = RateModelId;
        return SharedThis(this);
    }

    TSharedPtr<FRateModel> FRateModel::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FRateModel> FRateModel::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
        return SharedThis(this);
    }

    TSharedPtr<FRateModel> FRateModel::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FRateModel> FRateModel::WithTargetInventoryModelId(
        const TOptional<FString> TargetInventoryModelId
    )
    {
        this->TargetInventoryModelIdValue = TargetInventoryModelId;
        return SharedThis(this);
    }

    TSharedPtr<FRateModel> FRateModel::WithAcquireExperienceSuffix(
        const TOptional<FString> AcquireExperienceSuffix
    )
    {
        this->AcquireExperienceSuffixValue = AcquireExperienceSuffix;
        return SharedThis(this);
    }

    TSharedPtr<FRateModel> FRateModel::WithMaterialInventoryModelId(
        const TOptional<FString> MaterialInventoryModelId
    )
    {
        this->MaterialInventoryModelIdValue = MaterialInventoryModelId;
        return SharedThis(this);
    }

    TSharedPtr<FRateModel> FRateModel::WithAcquireExperienceHierarchy(
        const TSharedPtr<TArray<FString>> AcquireExperienceHierarchy
    )
    {
        this->AcquireExperienceHierarchyValue = AcquireExperienceHierarchy;
        return SharedThis(this);
    }

    TSharedPtr<FRateModel> FRateModel::WithExperienceModelId(
        const TOptional<FString> ExperienceModelId
    )
    {
        this->ExperienceModelIdValue = ExperienceModelId;
        return SharedThis(this);
    }

    TSharedPtr<FRateModel> FRateModel::WithBonusRates(
        const TSharedPtr<TArray<TSharedPtr<Model::FBonusRate>>> BonusRates
    )
    {
        this->BonusRatesValue = BonusRates;
        return SharedThis(this);
    }
    TOptional<FString> FRateModel::GetRateModelId() const
    {
        return RateModelIdValue;
    }
    TOptional<FString> FRateModel::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FRateModel::GetDescription() const
    {
        return DescriptionValue;
    }
    TOptional<FString> FRateModel::GetMetadata() const
    {
        return MetadataValue;
    }
    TOptional<FString> FRateModel::GetTargetInventoryModelId() const
    {
        return TargetInventoryModelIdValue;
    }
    TOptional<FString> FRateModel::GetAcquireExperienceSuffix() const
    {
        return AcquireExperienceSuffixValue;
    }
    TOptional<FString> FRateModel::GetMaterialInventoryModelId() const
    {
        return MaterialInventoryModelIdValue;
    }
    TSharedPtr<TArray<FString>> FRateModel::GetAcquireExperienceHierarchy() const
    {
        return AcquireExperienceHierarchyValue;
    }
    TOptional<FString> FRateModel::GetExperienceModelId() const
    {
        return ExperienceModelIdValue;
    }
    TSharedPtr<TArray<TSharedPtr<Model::FBonusRate>>> FRateModel::GetBonusRates() const
    {
        return BonusRatesValue;
    }

    TOptional<FString> FRateModel::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):enhance:(?<namespaceName>.+):rateModel:(?<rateName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FRateModel::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):enhance:(?<namespaceName>.+):rateModel:(?<rateName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FRateModel::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):enhance:(?<namespaceName>.+):rateModel:(?<rateName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FRateModel::GetRateNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):enhance:(?<namespaceName>.+):rateModel:(?<rateName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FRateModel> FRateModel::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FRateModel>()
            ->WithRateModelId(Data->HasField("rateModelId") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("rateModelId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithName(Data->HasField("name") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("name", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithDescription(Data->HasField("description") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("description", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithMetadata(Data->HasField("metadata") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("metadata", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithTargetInventoryModelId(Data->HasField("targetInventoryModelId") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("targetInventoryModelId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithAcquireExperienceSuffix(Data->HasField("acquireExperienceSuffix") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("acquireExperienceSuffix", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithMaterialInventoryModelId(Data->HasField("materialInventoryModelId") ? [Data]() -> TOptional<FString>
                {
                    FString v;
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
                    FString v;
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
                 }() : MakeShared<TArray<Model::FBonusRatePtr>>());
    }

    TSharedPtr<FJsonObject> FRateModel::ToJson() const
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
        return JsonRootObject;
    }

    FString FRateModel::TypeName = "RateModel";
}