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

#include "Log/Model/Facet.h"

namespace Gs2::Log::Model
{
    FFacet::FFacet():
        FieldValue(TOptional<FString>()),
        ValuesValue(nullptr),
        RangeValue(nullptr),
        GlobalRangeValue(nullptr)
    {
    }

    FFacet::FFacet(
        const FFacet& From
    ):
        FieldValue(From.FieldValue),
        ValuesValue(From.ValuesValue),
        RangeValue(From.RangeValue),
        GlobalRangeValue(From.GlobalRangeValue)
    {
    }

    TSharedPtr<FFacet> FFacet::WithField(
        const TOptional<FString> Field
    )
    {
        this->FieldValue = Field;
        return SharedThis(this);
    }

    TSharedPtr<FFacet> FFacet::WithValues(
        const TSharedPtr<TArray<TSharedPtr<Model::FFacetValueCount>>> Values
    )
    {
        this->ValuesValue = Values;
        return SharedThis(this);
    }

    TSharedPtr<FFacet> FFacet::WithRange(
        const TSharedPtr<FNumericRange> Range
    )
    {
        this->RangeValue = Range;
        return SharedThis(this);
    }

    TSharedPtr<FFacet> FFacet::WithGlobalRange(
        const TSharedPtr<FNumericRange> GlobalRange
    )
    {
        this->GlobalRangeValue = GlobalRange;
        return SharedThis(this);
    }
    TOptional<FString> FFacet::GetField() const
    {
        return FieldValue;
    }
    TSharedPtr<TArray<TSharedPtr<Model::FFacetValueCount>>> FFacet::GetValues() const
    {
        return ValuesValue;
    }
    TSharedPtr<FNumericRange> FFacet::GetRange() const
    {
        return RangeValue;
    }
    TSharedPtr<FNumericRange> FFacet::GetGlobalRange() const
    {
        return GlobalRangeValue;
    }

    TSharedPtr<FFacet> FFacet::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FFacet>()
            ->WithField(Data->HasField(ANSI_TO_TCHAR("field")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("field"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithValues(Data->HasField(ANSI_TO_TCHAR("values")) ? [Data]() -> TSharedPtr<TArray<Model::FFacetValueCountPtr>>
                {
                    auto v = MakeShared<TArray<Model::FFacetValueCountPtr>>();
                    if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("values")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("values")))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("values")))
                        {
                            v->Add(Model::FFacetValueCount::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<Model::FFacetValueCountPtr>>())
            ->WithRange(Data->HasField(ANSI_TO_TCHAR("range")) ? [Data]() -> Model::FNumericRangePtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("range")))
                    {
                        return nullptr;
                    }
                    return Model::FNumericRange::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("range")));
                 }() : nullptr)
            ->WithGlobalRange(Data->HasField(ANSI_TO_TCHAR("globalRange")) ? [Data]() -> Model::FNumericRangePtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("globalRange")))
                    {
                        return nullptr;
                    }
                    return Model::FNumericRange::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("globalRange")));
                 }() : nullptr);
    }

    TSharedPtr<FJsonObject> FFacet::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (FieldValue.IsSet())
        {
            JsonRootObject->SetStringField("field", FieldValue.GetValue());
        }
        if (ValuesValue != nullptr && ValuesValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *ValuesValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("values", v);
        }
        if (RangeValue != nullptr && RangeValue.IsValid())
        {
            JsonRootObject->SetObjectField("range", RangeValue->ToJson());
        }
        if (GlobalRangeValue != nullptr && GlobalRangeValue.IsValid())
        {
            JsonRootObject->SetObjectField("globalRange", GlobalRangeValue->ToJson());
        }
        return JsonRootObject;
    }

    FString FFacet::TypeName = "Facet";
}