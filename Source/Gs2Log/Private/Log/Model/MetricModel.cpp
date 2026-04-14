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

#include "Log/Model/MetricModel.h"

namespace Gs2::Log::Model
{
    FMetricModel::FMetricModel():
        NameValue(TOptional<FString>()),
        TypeValue(TOptional<FString>()),
        LabelsValue(nullptr)
    {
    }

    FMetricModel::FMetricModel(
        const FMetricModel& From
    ):
        NameValue(From.NameValue),
        TypeValue(From.TypeValue),
        LabelsValue(From.LabelsValue)
    {
    }

    TSharedPtr<FMetricModel> FMetricModel::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FMetricModel> FMetricModel::WithType(
        const TOptional<FString> Type
    )
    {
        this->TypeValue = Type;
        return SharedThis(this);
    }

    TSharedPtr<FMetricModel> FMetricModel::WithLabels(
        const TSharedPtr<TArray<FString>> Labels
    )
    {
        this->LabelsValue = Labels;
        return SharedThis(this);
    }
    TOptional<FString> FMetricModel::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FMetricModel::GetType() const
    {
        return TypeValue;
    }
    TSharedPtr<TArray<FString>> FMetricModel::GetLabels() const
    {
        return LabelsValue;
    }

    TSharedPtr<FMetricModel> FMetricModel::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FMetricModel>()
            ->WithName(Data->HasField(ANSI_TO_TCHAR("name")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("name"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithType(Data->HasField(ANSI_TO_TCHAR("type")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("type"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithLabels(Data->HasField(ANSI_TO_TCHAR("labels")) ? [Data]() -> TSharedPtr<TArray<FString>>
                {
                    auto v = MakeShared<TArray<FString>>();
                    if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("labels")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("labels")))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("labels")))
                        {
                            v->Add(JsonObjectValue->AsString());
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<FString>>());
    }

    TSharedPtr<FJsonObject> FMetricModel::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (NameValue.IsSet())
        {
            JsonRootObject->SetStringField("name", NameValue.GetValue());
        }
        if (TypeValue.IsSet())
        {
            JsonRootObject->SetStringField("type", TypeValue.GetValue());
        }
        if (LabelsValue != nullptr && LabelsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *LabelsValue)
            {
                v.Add(MakeShared<FJsonValueString>(JsonObjectValue));
            }
            JsonRootObject->SetArrayField("labels", v);
        }
        return JsonRootObject;
    }

    FString FMetricModel::TypeName = "MetricModel";
}