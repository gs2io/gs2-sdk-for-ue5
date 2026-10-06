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

#include "Enhance/Model/UnleashRecipe.h"

namespace Gs2::Enhance::Model
{
    FUnleashRecipe::FUnleashRecipe():
        NameValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        TargetGroupKeysValue(nullptr),
        MaterialsValue(nullptr)
    {
    }

    FUnleashRecipe::FUnleashRecipe(
        const FUnleashRecipe& From
    ):
        NameValue(From.NameValue),
        MetadataValue(From.MetadataValue),
        TargetGroupKeysValue(From.TargetGroupKeysValue),
        MaterialsValue(From.MaterialsValue)
    {
    }

    TSharedPtr<FUnleashRecipe> FUnleashRecipe::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FUnleashRecipe> FUnleashRecipe::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FUnleashRecipe> FUnleashRecipe::WithTargetGroupKeys(
        const TSharedPtr<TArray<FString>> TargetGroupKeys
    )
    {
        this->TargetGroupKeysValue = TargetGroupKeys;
        return SharedThis(this);
    }

    TSharedPtr<FUnleashRecipe> FUnleashRecipe::WithMaterials(
        const TSharedPtr<TArray<TSharedPtr<Model::FUnleashMaterial>>> Materials
    )
    {
        this->MaterialsValue = Materials;
        return SharedThis(this);
    }
    TOptional<FString> FUnleashRecipe::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FUnleashRecipe::GetMetadata() const
    {
        return MetadataValue;
    }
    TSharedPtr<TArray<FString>> FUnleashRecipe::GetTargetGroupKeys() const
    {
        return TargetGroupKeysValue;
    }
    TSharedPtr<TArray<TSharedPtr<Model::FUnleashMaterial>>> FUnleashRecipe::GetMaterials() const
    {
        return MaterialsValue;
    }

    TSharedPtr<FUnleashRecipe> FUnleashRecipe::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FUnleashRecipe>()
            ->WithName(Data->HasField(ANSI_TO_TCHAR("name")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("name"), v))
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
            ->WithTargetGroupKeys(Data->HasField(ANSI_TO_TCHAR("targetGroupKeys")) ? [Data]() -> TSharedPtr<TArray<FString>>
                {
                    if (!Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("targetGroupKeys")))
                    {
                        return nullptr;
                    }
                    auto v = MakeShared<TArray<FString>>();
                    for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("targetGroupKeys")))
                    {
                        v->Add(JsonObjectValue->AsString());
                    }
                    return v;
                 }() : nullptr)
            ->WithMaterials(Data->HasField(ANSI_TO_TCHAR("materials")) ? [Data]() -> TSharedPtr<TArray<Model::FUnleashMaterialPtr>>
                {
                    if (!Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("materials")))
                    {
                        return nullptr;
                    }
                    auto v = MakeShared<TArray<Model::FUnleashMaterialPtr>>();
                    for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("materials")))
                    {
                        v->Add(Model::FUnleashMaterial::FromJson(JsonObjectValue->AsObject()));
                    }
                    return v;
                 }() : nullptr);
    }

    TSharedPtr<FJsonObject> FUnleashRecipe::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (NameValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("name"), NameValue.GetValue());
        }
        if (MetadataValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("metadata"), MetadataValue.GetValue());
        }
        if (TargetGroupKeysValue != nullptr && TargetGroupKeysValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *TargetGroupKeysValue)
            {
                v.Add(MakeShared<FJsonValueString>(JsonObjectValue));
            }
            JsonRootObject->SetArrayField(TEXT("targetGroupKeys"), v);
        }
        if (MaterialsValue != nullptr && MaterialsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *MaterialsValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField(TEXT("materials"), v);
        }
        return JsonRootObject;
    }

    FString FUnleashRecipe::TypeName = "UnleashRecipe";
}