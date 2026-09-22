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

#include "Log/Model/TimeseriesMetadata.h"

namespace Gs2::Log::Model
{
    FTimeseriesMetadata::FTimeseriesMetadata():
        KeysValue(nullptr),
        GroupByValue(nullptr)
    {
    }

    FTimeseriesMetadata::FTimeseriesMetadata(
        const FTimeseriesMetadata& From
    ):
        KeysValue(From.KeysValue),
        GroupByValue(From.GroupByValue)
    {
    }

    TSharedPtr<FTimeseriesMetadata> FTimeseriesMetadata::WithKeys(
        const TSharedPtr<TArray<FString>> Keys
    )
    {
        this->KeysValue = Keys;
        return SharedThis(this);
    }

    TSharedPtr<FTimeseriesMetadata> FTimeseriesMetadata::WithGroupBy(
        const TSharedPtr<TArray<FString>> GroupBy
    )
    {
        this->GroupByValue = GroupBy;
        return SharedThis(this);
    }
    TSharedPtr<TArray<FString>> FTimeseriesMetadata::GetKeys() const
    {
        return KeysValue;
    }
    TSharedPtr<TArray<FString>> FTimeseriesMetadata::GetGroupBy() const
    {
        return GroupByValue;
    }

    TSharedPtr<FTimeseriesMetadata> FTimeseriesMetadata::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FTimeseriesMetadata>()
            ->WithKeys(Data->HasField(ANSI_TO_TCHAR("keys")) ? [Data]() -> TSharedPtr<TArray<FString>>
                {
                    if (!Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("keys")))
                    {
                        return nullptr;
                    }
                    auto v = MakeShared<TArray<FString>>();
                    for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("keys")))
                    {
                        v->Add(JsonObjectValue->AsString());
                    }
                    return v;
                 }() : nullptr)
            ->WithGroupBy(Data->HasField(ANSI_TO_TCHAR("groupBy")) ? [Data]() -> TSharedPtr<TArray<FString>>
                {
                    if (!Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("groupBy")))
                    {
                        return nullptr;
                    }
                    auto v = MakeShared<TArray<FString>>();
                    for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("groupBy")))
                    {
                        v->Add(JsonObjectValue->AsString());
                    }
                    return v;
                 }() : nullptr);
    }

    TSharedPtr<FJsonObject> FTimeseriesMetadata::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (KeysValue != nullptr && KeysValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *KeysValue)
            {
                v.Add(MakeShared<FJsonValueString>(JsonObjectValue));
            }
            JsonRootObject->SetArrayField(TEXT("keys"), v);
        }
        if (GroupByValue != nullptr && GroupByValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *GroupByValue)
            {
                v.Add(MakeShared<FJsonValueString>(JsonObjectValue));
            }
            JsonRootObject->SetArrayField(TEXT("groupBy"), v);
        }
        return JsonRootObject;
    }

    FString FTimeseriesMetadata::TypeName = "TimeseriesMetadata";
}