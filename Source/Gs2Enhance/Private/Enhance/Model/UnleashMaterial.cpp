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

#include "Enhance/Model/UnleashMaterial.h"

namespace Gs2::Enhance::Model
{
    FUnleashMaterial::FUnleashMaterial():
        NameValue(TOptional<FString>()),
        MaterialTypeValue(TOptional<FString>()),
        IndividualSettingValue(nullptr),
        QuantitySettingValue(nullptr)
    {
    }

    FUnleashMaterial::FUnleashMaterial(
        const FUnleashMaterial& From
    ):
        NameValue(From.NameValue),
        MaterialTypeValue(From.MaterialTypeValue),
        IndividualSettingValue(From.IndividualSettingValue),
        QuantitySettingValue(From.QuantitySettingValue)
    {
    }

    TSharedPtr<FUnleashMaterial> FUnleashMaterial::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FUnleashMaterial> FUnleashMaterial::WithMaterialType(
        const TOptional<FString> MaterialType
    )
    {
        this->MaterialTypeValue = MaterialType;
        return SharedThis(this);
    }

    TSharedPtr<FUnleashMaterial> FUnleashMaterial::WithIndividualSetting(
        const TSharedPtr<FUnleashIndividualMaterialSetting> IndividualSetting
    )
    {
        this->IndividualSettingValue = IndividualSetting;
        return SharedThis(this);
    }

    TSharedPtr<FUnleashMaterial> FUnleashMaterial::WithQuantitySetting(
        const TSharedPtr<FUnleashQuantityMaterialSetting> QuantitySetting
    )
    {
        this->QuantitySettingValue = QuantitySetting;
        return SharedThis(this);
    }
    TOptional<FString> FUnleashMaterial::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FUnleashMaterial::GetMaterialType() const
    {
        return MaterialTypeValue;
    }
    TSharedPtr<FUnleashIndividualMaterialSetting> FUnleashMaterial::GetIndividualSetting() const
    {
        return IndividualSettingValue;
    }
    TSharedPtr<FUnleashQuantityMaterialSetting> FUnleashMaterial::GetQuantitySetting() const
    {
        return QuantitySettingValue;
    }

    TSharedPtr<FUnleashMaterial> FUnleashMaterial::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FUnleashMaterial>()
            ->WithName(Data->HasField(ANSI_TO_TCHAR("name")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("name"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithMaterialType(Data->HasField(ANSI_TO_TCHAR("materialType")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("materialType"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithIndividualSetting(Data->HasField(ANSI_TO_TCHAR("individualSetting")) ? [Data]() -> Model::FUnleashIndividualMaterialSettingPtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("individualSetting")))
                    {
                        return nullptr;
                    }
                    return Model::FUnleashIndividualMaterialSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("individualSetting")));
                 }() : nullptr)
            ->WithQuantitySetting(Data->HasField(ANSI_TO_TCHAR("quantitySetting")) ? [Data]() -> Model::FUnleashQuantityMaterialSettingPtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("quantitySetting")))
                    {
                        return nullptr;
                    }
                    return Model::FUnleashQuantityMaterialSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("quantitySetting")));
                 }() : nullptr);
    }

    TSharedPtr<FJsonObject> FUnleashMaterial::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (NameValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("name"), NameValue.GetValue());
        }
        if (MaterialTypeValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("materialType"), MaterialTypeValue.GetValue());
        }
        if (IndividualSettingValue != nullptr && IndividualSettingValue.IsValid())
        {
            JsonRootObject->SetObjectField(TEXT("individualSetting"), IndividualSettingValue->ToJson());
        }
        if (QuantitySettingValue != nullptr && QuantitySettingValue.IsValid())
        {
            JsonRootObject->SetObjectField(TEXT("quantitySetting"), QuantitySettingValue->ToJson());
        }
        return JsonRootObject;
    }

    FString FUnleashMaterial::TypeName = "UnleashMaterial";
}