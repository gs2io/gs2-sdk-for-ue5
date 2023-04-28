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

#include "Stamina/Model/MaxStaminaTable.h"

namespace Gs2::Stamina::Model
{
    FMaxStaminaTable::FMaxStaminaTable():
        MaxStaminaTableIdValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        ExperienceModelIdValue(TOptional<FString>()),
        ValuesValue(nullptr)
    {
    }

    FMaxStaminaTable::FMaxStaminaTable(
        const FMaxStaminaTable& From
    ):
        MaxStaminaTableIdValue(From.MaxStaminaTableIdValue),
        NameValue(From.NameValue),
        MetadataValue(From.MetadataValue),
        ExperienceModelIdValue(From.ExperienceModelIdValue),
        ValuesValue(From.ValuesValue)
    {
    }

    TSharedPtr<FMaxStaminaTable> FMaxStaminaTable::WithMaxStaminaTableId(
        const TOptional<FString> MaxStaminaTableId
    )
    {
        this->MaxStaminaTableIdValue = MaxStaminaTableId;
        return SharedThis(this);
    }

    TSharedPtr<FMaxStaminaTable> FMaxStaminaTable::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FMaxStaminaTable> FMaxStaminaTable::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FMaxStaminaTable> FMaxStaminaTable::WithExperienceModelId(
        const TOptional<FString> ExperienceModelId
    )
    {
        this->ExperienceModelIdValue = ExperienceModelId;
        return SharedThis(this);
    }

    TSharedPtr<FMaxStaminaTable> FMaxStaminaTable::WithValues(
        const TSharedPtr<TArray<int32>> Values
    )
    {
        this->ValuesValue = Values;
        return SharedThis(this);
    }
    TOptional<FString> FMaxStaminaTable::GetMaxStaminaTableId() const
    {
        return MaxStaminaTableIdValue;
    }
    TOptional<FString> FMaxStaminaTable::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FMaxStaminaTable::GetMetadata() const
    {
        return MetadataValue;
    }
    TOptional<FString> FMaxStaminaTable::GetExperienceModelId() const
    {
        return ExperienceModelIdValue;
    }
    TSharedPtr<TArray<int32>> FMaxStaminaTable::GetValues() const
    {
        return ValuesValue;
    }

    TOptional<FString> FMaxStaminaTable::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):stamina:(?<namespaceName>.+):maxStaminaTable:(?<maxStaminaTableName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FMaxStaminaTable::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):stamina:(?<namespaceName>.+):maxStaminaTable:(?<maxStaminaTableName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FMaxStaminaTable::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):stamina:(?<namespaceName>.+):maxStaminaTable:(?<maxStaminaTableName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FMaxStaminaTable::GetMaxStaminaTableNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):stamina:(?<namespaceName>.+):maxStaminaTable:(?<maxStaminaTableName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FMaxStaminaTable> FMaxStaminaTable::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FMaxStaminaTable>()
            ->WithMaxStaminaTableId(Data->HasField("maxStaminaTableId") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("maxStaminaTableId", v))
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
            ->WithExperienceModelId(Data->HasField("experienceModelId") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("experienceModelId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithValues(Data->HasField("values") ? [Data]() -> TSharedPtr<TArray<int32>>
                {
                    auto v = MakeShared<TArray<int32>>();
                    if (!Data->HasTypedField<EJson::Null>("values") && Data->HasTypedField<EJson::Array>("values"))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField("values"))
                        {
                            v->Add(JsonObjectValue->AsNumber());
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<int32>>());
    }

    TSharedPtr<FJsonObject> FMaxStaminaTable::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (MaxStaminaTableIdValue.IsSet())
        {
            JsonRootObject->SetStringField("maxStaminaTableId", MaxStaminaTableIdValue.GetValue());
        }
        if (NameValue.IsSet())
        {
            JsonRootObject->SetStringField("name", NameValue.GetValue());
        }
        if (MetadataValue.IsSet())
        {
            JsonRootObject->SetStringField("metadata", MetadataValue.GetValue());
        }
        if (ExperienceModelIdValue.IsSet())
        {
            JsonRootObject->SetStringField("experienceModelId", ExperienceModelIdValue.GetValue());
        }
        if (ValuesValue != nullptr && ValuesValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *ValuesValue)
            {
                v.Add(MakeShared<FJsonValueNumber>(JsonObjectValue));
            }
            JsonRootObject->SetArrayField("values", v);
        }
        return JsonRootObject;
    }

    FString FMaxStaminaTable::TypeName = "MaxStaminaTable";
}