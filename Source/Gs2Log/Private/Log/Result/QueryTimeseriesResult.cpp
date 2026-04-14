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

#include "Log/Result/QueryTimeseriesResult.h"

namespace Gs2::Log::Result
{
    FQueryTimeseriesResult::FQueryTimeseriesResult():
        ItemsValue(nullptr),
        TimeseriesMetadataValue(nullptr),
        NextPageTokenValue(TOptional<FString>())
    {
    }

    FQueryTimeseriesResult::FQueryTimeseriesResult(
        const FQueryTimeseriesResult& From
    ):
        ItemsValue(From.ItemsValue),
        TimeseriesMetadataValue(From.TimeseriesMetadataValue),
        NextPageTokenValue(From.NextPageTokenValue)
    {
    }

    TSharedPtr<FQueryTimeseriesResult> FQueryTimeseriesResult::WithItems(
        const TSharedPtr<TArray<TSharedPtr<Model::FTimeseriesPoint>>> Items
    )
    {
        this->ItemsValue = Items;
        return SharedThis(this);
    }

    TSharedPtr<FQueryTimeseriesResult> FQueryTimeseriesResult::WithTimeseriesMetadata(
        const TSharedPtr<Model::FTimeseriesMetadata> TimeseriesMetadata
    )
    {
        this->TimeseriesMetadataValue = TimeseriesMetadata;
        return SharedThis(this);
    }

    TSharedPtr<FQueryTimeseriesResult> FQueryTimeseriesResult::WithNextPageToken(
        const TOptional<FString> NextPageToken
    )
    {
        this->NextPageTokenValue = NextPageToken;
        return SharedThis(this);
    }

    TSharedPtr<TArray<TSharedPtr<Model::FTimeseriesPoint>>> FQueryTimeseriesResult::GetItems() const
    {
        if (!ItemsValue.IsValid())
        {
            return nullptr;
        }
        return ItemsValue;
    }

    TSharedPtr<Model::FTimeseriesMetadata> FQueryTimeseriesResult::GetTimeseriesMetadata() const
    {
        if (!TimeseriesMetadataValue.IsValid())
        {
            return nullptr;
        }
        return TimeseriesMetadataValue;
    }

    TOptional<FString> FQueryTimeseriesResult::GetNextPageToken() const
    {
        return NextPageTokenValue;
    }

    TSharedPtr<FQueryTimeseriesResult> FQueryTimeseriesResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FQueryTimeseriesResult>()
            ->WithItems(Data->HasField(ANSI_TO_TCHAR("items")) ? [Data]() -> TSharedPtr<TArray<Model::FTimeseriesPointPtr>>
                 {
                    auto v = MakeShared<TArray<Model::FTimeseriesPointPtr>>();
                    if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("items")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("items")))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("items")))
                        {
                            v->Add(Model::FTimeseriesPoint::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<Model::FTimeseriesPointPtr>>())
            ->WithTimeseriesMetadata(Data->HasField(ANSI_TO_TCHAR("timeseriesMetadata")) ? [Data]() -> Model::FTimeseriesMetadataPtr
                 {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("timeseriesMetadata")))
                    {
                        return nullptr;
                    }
                    return Model::FTimeseriesMetadata::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("timeseriesMetadata")));
                 }() : nullptr)
            ->WithNextPageToken(Data->HasField(ANSI_TO_TCHAR("nextPageToken")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("nextPageToken"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FQueryTimeseriesResult::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ItemsValue != nullptr && ItemsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *ItemsValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("items", v);
        }
        if (TimeseriesMetadataValue != nullptr && TimeseriesMetadataValue.IsValid())
        {
            JsonRootObject->SetObjectField("timeseriesMetadata", TimeseriesMetadataValue->ToJson());
        }
        if (NextPageTokenValue.IsSet())
        {
            JsonRootObject->SetStringField("nextPageToken", NextPageTokenValue.GetValue());
        }
        return JsonRootObject;
    }
}