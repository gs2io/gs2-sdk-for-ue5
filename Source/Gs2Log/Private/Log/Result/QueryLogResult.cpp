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

#include "Log/Result/QueryLogResult.h"

namespace Gs2::Log::Result
{
    FQueryLogResult::FQueryLogResult():
        ItemsValue(nullptr),
        TotalEntryCountValue(TOptional<int32>()),
        NextPageTokenValue(TOptional<FString>())
    {
    }

    FQueryLogResult::FQueryLogResult(
        const FQueryLogResult& From
    ):
        ItemsValue(From.ItemsValue),
        TotalEntryCountValue(From.TotalEntryCountValue),
        NextPageTokenValue(From.NextPageTokenValue)
    {
    }

    TSharedPtr<FQueryLogResult> FQueryLogResult::WithItems(
        const TSharedPtr<TArray<TSharedPtr<Model::FLogEntry>>> Items
    )
    {
        this->ItemsValue = Items;
        return SharedThis(this);
    }

    TSharedPtr<FQueryLogResult> FQueryLogResult::WithTotalEntryCount(
        const TOptional<int32> TotalEntryCount
    )
    {
        this->TotalEntryCountValue = TotalEntryCount;
        return SharedThis(this);
    }

    TSharedPtr<FQueryLogResult> FQueryLogResult::WithNextPageToken(
        const TOptional<FString> NextPageToken
    )
    {
        this->NextPageTokenValue = NextPageToken;
        return SharedThis(this);
    }

    TSharedPtr<TArray<TSharedPtr<Model::FLogEntry>>> FQueryLogResult::GetItems() const
    {
        if (!ItemsValue.IsValid())
        {
            return nullptr;
        }
        return ItemsValue;
    }

    TOptional<int32> FQueryLogResult::GetTotalEntryCount() const
    {
        return TotalEntryCountValue;
    }

    FString FQueryLogResult::GetTotalEntryCountString() const
    {
        if (!TotalEntryCountValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), TotalEntryCountValue.GetValue());
    }

    TOptional<FString> FQueryLogResult::GetNextPageToken() const
    {
        return NextPageTokenValue;
    }

    TSharedPtr<FQueryLogResult> FQueryLogResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FQueryLogResult>()
            ->WithItems(Data->HasField(ANSI_TO_TCHAR("items")) ? [Data]() -> TSharedPtr<TArray<Model::FLogEntryPtr>>
                 {
                    auto v = MakeShared<TArray<Model::FLogEntryPtr>>();
                    if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("items")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("items")))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("items")))
                        {
                            v->Add(Model::FLogEntry::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<Model::FLogEntryPtr>>())
            ->WithTotalEntryCount(Data->HasField(ANSI_TO_TCHAR("totalEntryCount")) ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("totalEntryCount"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
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

    TSharedPtr<FJsonObject> FQueryLogResult::ToJson() const
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
        if (TotalEntryCountValue.IsSet())
        {
            JsonRootObject->SetNumberField("totalEntryCount", TotalEntryCountValue.GetValue());
        }
        if (NextPageTokenValue.IsSet())
        {
            JsonRootObject->SetStringField("nextPageToken", NextPageTokenValue.GetValue());
        }
        return JsonRootObject;
    }
}