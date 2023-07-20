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

#include "Enchant/Model/RarityParameterModelMaster.h"

namespace Gs2::Enchant::Model
{
    FRarityParameterModelMaster::FRarityParameterModelMaster():
        RarityParameterModelIdValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        MaximumParameterCountValue(TOptional<int32>()),
        ParameterCountsValue(nullptr),
        ParametersValue(nullptr),
        CreatedAtValue(TOptional<int64>()),
        UpdatedAtValue(TOptional<int64>())
    {
    }

    FRarityParameterModelMaster::FRarityParameterModelMaster(
        const FRarityParameterModelMaster& From
    ):
        RarityParameterModelIdValue(From.RarityParameterModelIdValue),
        NameValue(From.NameValue),
        DescriptionValue(From.DescriptionValue),
        MetadataValue(From.MetadataValue),
        MaximumParameterCountValue(From.MaximumParameterCountValue),
        ParameterCountsValue(From.ParameterCountsValue),
        ParametersValue(From.ParametersValue),
        CreatedAtValue(From.CreatedAtValue),
        UpdatedAtValue(From.UpdatedAtValue)
    {
    }

    TSharedPtr<FRarityParameterModelMaster> FRarityParameterModelMaster::WithRarityParameterModelId(
        const TOptional<FString> RarityParameterModelId
    )
    {
        this->RarityParameterModelIdValue = RarityParameterModelId;
        return SharedThis(this);
    }

    TSharedPtr<FRarityParameterModelMaster> FRarityParameterModelMaster::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FRarityParameterModelMaster> FRarityParameterModelMaster::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
        return SharedThis(this);
    }

    TSharedPtr<FRarityParameterModelMaster> FRarityParameterModelMaster::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FRarityParameterModelMaster> FRarityParameterModelMaster::WithMaximumParameterCount(
        const TOptional<int32> MaximumParameterCount
    )
    {
        this->MaximumParameterCountValue = MaximumParameterCount;
        return SharedThis(this);
    }

    TSharedPtr<FRarityParameterModelMaster> FRarityParameterModelMaster::WithParameterCounts(
        const TSharedPtr<TArray<TSharedPtr<Model::FRarityParameterCountModel>>> ParameterCounts
    )
    {
        this->ParameterCountsValue = ParameterCounts;
        return SharedThis(this);
    }

    TSharedPtr<FRarityParameterModelMaster> FRarityParameterModelMaster::WithParameters(
        const TSharedPtr<TArray<TSharedPtr<Model::FRarityParameterValueModel>>> Parameters
    )
    {
        this->ParametersValue = Parameters;
        return SharedThis(this);
    }

    TSharedPtr<FRarityParameterModelMaster> FRarityParameterModelMaster::WithCreatedAt(
        const TOptional<int64> CreatedAt
    )
    {
        this->CreatedAtValue = CreatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FRarityParameterModelMaster> FRarityParameterModelMaster::WithUpdatedAt(
        const TOptional<int64> UpdatedAt
    )
    {
        this->UpdatedAtValue = UpdatedAt;
        return SharedThis(this);
    }
    TOptional<FString> FRarityParameterModelMaster::GetRarityParameterModelId() const
    {
        return RarityParameterModelIdValue;
    }
    TOptional<FString> FRarityParameterModelMaster::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FRarityParameterModelMaster::GetDescription() const
    {
        return DescriptionValue;
    }
    TOptional<FString> FRarityParameterModelMaster::GetMetadata() const
    {
        return MetadataValue;
    }
    TOptional<int32> FRarityParameterModelMaster::GetMaximumParameterCount() const
    {
        return MaximumParameterCountValue;
    }

    FString FRarityParameterModelMaster::GetMaximumParameterCountString() const
    {
        if (!MaximumParameterCountValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), MaximumParameterCountValue.GetValue());
    }
    TSharedPtr<TArray<TSharedPtr<Model::FRarityParameterCountModel>>> FRarityParameterModelMaster::GetParameterCounts() const
    {
        return ParameterCountsValue;
    }
    TSharedPtr<TArray<TSharedPtr<Model::FRarityParameterValueModel>>> FRarityParameterModelMaster::GetParameters() const
    {
        return ParametersValue;
    }
    TOptional<int64> FRarityParameterModelMaster::GetCreatedAt() const
    {
        return CreatedAtValue;
    }

    FString FRarityParameterModelMaster::GetCreatedAtString() const
    {
        if (!CreatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue());
    }
    TOptional<int64> FRarityParameterModelMaster::GetUpdatedAt() const
    {
        return UpdatedAtValue;
    }

    FString FRarityParameterModelMaster::GetUpdatedAtString() const
    {
        if (!UpdatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), UpdatedAtValue.GetValue());
    }

    TOptional<FString> FRarityParameterModelMaster::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):enchant:(?<namespaceName>.+):model:rarity:(?<parameterName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FRarityParameterModelMaster::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):enchant:(?<namespaceName>.+):model:rarity:(?<parameterName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FRarityParameterModelMaster::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):enchant:(?<namespaceName>.+):model:rarity:(?<parameterName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FRarityParameterModelMaster::GetParameterNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):enchant:(?<namespaceName>.+):model:rarity:(?<parameterName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FRarityParameterModelMaster> FRarityParameterModelMaster::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FRarityParameterModelMaster>()
            ->WithRarityParameterModelId(Data->HasField("rarityParameterModelId") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("rarityParameterModelId", v))
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
            ->WithMaximumParameterCount(Data->HasField("maximumParameterCount") ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField("maximumParameterCount", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithParameterCounts(Data->HasField("parameterCounts") ? [Data]() -> TSharedPtr<TArray<Model::FRarityParameterCountModelPtr>>
                {
                    auto v = MakeShared<TArray<Model::FRarityParameterCountModelPtr>>();
                    if (!Data->HasTypedField<EJson::Null>("parameterCounts") && Data->HasTypedField<EJson::Array>("parameterCounts"))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField("parameterCounts"))
                        {
                            v->Add(Model::FRarityParameterCountModel::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<Model::FRarityParameterCountModelPtr>>())
            ->WithParameters(Data->HasField("parameters") ? [Data]() -> TSharedPtr<TArray<Model::FRarityParameterValueModelPtr>>
                {
                    auto v = MakeShared<TArray<Model::FRarityParameterValueModelPtr>>();
                    if (!Data->HasTypedField<EJson::Null>("parameters") && Data->HasTypedField<EJson::Array>("parameters"))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField("parameters"))
                        {
                            v->Add(Model::FRarityParameterValueModel::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<Model::FRarityParameterValueModelPtr>>())
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
                }() : TOptional<int64>());
    }

    TSharedPtr<FJsonObject> FRarityParameterModelMaster::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (RarityParameterModelIdValue.IsSet())
        {
            JsonRootObject->SetStringField("rarityParameterModelId", RarityParameterModelIdValue.GetValue());
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
        if (MaximumParameterCountValue.IsSet())
        {
            JsonRootObject->SetNumberField("maximumParameterCount", MaximumParameterCountValue.GetValue());
        }
        if (ParameterCountsValue != nullptr && ParameterCountsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *ParameterCountsValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("parameterCounts", v);
        }
        if (ParametersValue != nullptr && ParametersValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *ParametersValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("parameters", v);
        }
        if (CreatedAtValue.IsSet())
        {
            JsonRootObject->SetStringField("createdAt", FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue()));
        }
        if (UpdatedAtValue.IsSet())
        {
            JsonRootObject->SetStringField("updatedAt", FString::Printf(TEXT("%lld"), UpdatedAtValue.GetValue()));
        }
        return JsonRootObject;
    }

    FString FRarityParameterModelMaster::TypeName = "RarityParameterModelMaster";
}