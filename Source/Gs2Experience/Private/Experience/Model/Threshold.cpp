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

#include "Experience/Model/Threshold.h"

namespace Gs2::Experience::Model
{
    FThreshold::FThreshold():
        MetadataValue(TOptional<FString>()),
        ValuesValue(nullptr)
    {
    }

    FThreshold::FThreshold(
        const FThreshold& From
    ):
        MetadataValue(From.MetadataValue),
        ValuesValue(From.ValuesValue)
    {
    }

    TSharedPtr<FThreshold> FThreshold::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FThreshold> FThreshold::WithValues(
        const TSharedPtr<TArray<int64>> Values
    )
    {
        this->ValuesValue = Values;
        return SharedThis(this);
    }
    TOptional<FString> FThreshold::GetMetadata() const
    {
        return MetadataValue;
    }
    TSharedPtr<TArray<int64>> FThreshold::GetValues() const
    {
        return ValuesValue;
    }

    TSharedPtr<FThreshold> FThreshold::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FThreshold>()
            ->WithMetadata(Data->HasField("metadata") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("metadata", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithValues(Data->HasField("values") ? [Data]() -> TSharedPtr<TArray<int64>>
                {
                    auto v = MakeShared<TArray<int64>>();
                    if (!Data->HasTypedField<EJson::Null>("values") && Data->HasTypedField<EJson::Array>("values"))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField("values"))
                        {
                            v->Add(JsonObjectValue->AsNumber());
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<int64>>());
    }

    TSharedPtr<FJsonObject> FThreshold::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (MetadataValue.IsSet())
        {
            JsonRootObject->SetStringField("metadata", MetadataValue.GetValue());
        }
        if (ValuesValue != nullptr && ValuesValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *ValuesValue)
            {
                v.Add(MakeShared<FJsonValueString>(FString::Printf(TEXT("%lld"), JsonObjectValue)));
            }
            JsonRootObject->SetArrayField("values", v);
        }
        return JsonRootObject;
    }

    FString FThreshold::TypeName = "Threshold";
}