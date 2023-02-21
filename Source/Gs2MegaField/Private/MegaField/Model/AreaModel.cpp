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

#include "MegaField/Model/AreaModel.h"

namespace Gs2::MegaField::Model
{
    FAreaModel::FAreaModel():
        AreaModelIdValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        LayerModelsValue(nullptr)
    {
    }

    FAreaModel::FAreaModel(
        const FAreaModel& From
    ):
        AreaModelIdValue(From.AreaModelIdValue),
        NameValue(From.NameValue),
        MetadataValue(From.MetadataValue),
        LayerModelsValue(From.LayerModelsValue)
    {
    }

    TSharedPtr<FAreaModel> FAreaModel::WithAreaModelId(
        const TOptional<FString> AreaModelId
    )
    {
        this->AreaModelIdValue = AreaModelId;
        return SharedThis(this);
    }

    TSharedPtr<FAreaModel> FAreaModel::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FAreaModel> FAreaModel::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FAreaModel> FAreaModel::WithLayerModels(
        const TSharedPtr<TArray<TSharedPtr<Model::FLayerModel>>> LayerModels
    )
    {
        this->LayerModelsValue = LayerModels;
        return SharedThis(this);
    }
    TOptional<FString> FAreaModel::GetAreaModelId() const
    {
        return AreaModelIdValue;
    }
    TOptional<FString> FAreaModel::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FAreaModel::GetMetadata() const
    {
        return MetadataValue;
    }
    TSharedPtr<TArray<TSharedPtr<Model::FLayerModel>>> FAreaModel::GetLayerModels() const
    {
        return LayerModelsValue;
    }

    TOptional<FString> FAreaModel::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):megaField:(?<namespaceName>.+):model:area:(?<areaModelName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FAreaModel::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):megaField:(?<namespaceName>.+):model:area:(?<areaModelName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FAreaModel::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):megaField:(?<namespaceName>.+):model:area:(?<areaModelName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FAreaModel::GetAreaModelNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):megaField:(?<namespaceName>.+):model:area:(?<areaModelName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FAreaModel> FAreaModel::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FAreaModel>()
            ->WithAreaModelId(Data->HasField("areaModelId") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("areaModelId", v))
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
            ->WithMetadata(Data->HasField("metadata") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("metadata", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithLayerModels(Data->HasField("layerModels") ? [Data]() -> TSharedPtr<TArray<Model::FLayerModelPtr>>
                {
                    auto v = MakeShared<TArray<Model::FLayerModelPtr>>();
                    if (!Data->HasTypedField<EJson::Null>("layerModels") && Data->HasTypedField<EJson::Array>("layerModels"))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField("layerModels"))
                        {
                            v->Add(Model::FLayerModel::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : nullptr);
    }

    TSharedPtr<FJsonObject> FAreaModel::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (AreaModelIdValue.IsSet())
        {
            JsonRootObject->SetStringField("areaModelId", AreaModelIdValue.GetValue());
        }
        if (NameValue.IsSet())
        {
            JsonRootObject->SetStringField("name", NameValue.GetValue());
        }
        if (MetadataValue.IsSet())
        {
            JsonRootObject->SetStringField("metadata", MetadataValue.GetValue());
        }
        if (LayerModelsValue != nullptr && LayerModelsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *LayerModelsValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("layerModels", v);
        }
        return JsonRootObject;
    }

    FString FAreaModel::TypeName = "AreaModel";
}