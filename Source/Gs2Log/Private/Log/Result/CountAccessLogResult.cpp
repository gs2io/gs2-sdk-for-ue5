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

#include "Log/Result/CountAccessLogResult.h"

namespace Gs2::Log::Result
{
    FCountAccessLogResult::FCountAccessLogResult():
        ItemsValue(nullptr),
        NextPageTokenValue(TOptional<FString>()),
        TotalCountValue(TOptional<int64>()),
        ScanSizeValue(TOptional<int64>())
    {
    }

    FCountAccessLogResult::FCountAccessLogResult(
        const FCountAccessLogResult& From
    ):
        ItemsValue(From.ItemsValue),
        NextPageTokenValue(From.NextPageTokenValue),
        TotalCountValue(From.TotalCountValue),
        ScanSizeValue(From.ScanSizeValue)
    {
    }

    TSharedPtr<FCountAccessLogResult> FCountAccessLogResult::WithItems(
        const TSharedPtr<TArray<TSharedPtr<Model::FAccessLogCount>>> Items
    )
    {
        this->ItemsValue = Items;
        return SharedThis(this);
    }

    TSharedPtr<FCountAccessLogResult> FCountAccessLogResult::WithNextPageToken(
        const TOptional<FString> NextPageToken
    )
    {
        this->NextPageTokenValue = NextPageToken;
        return SharedThis(this);
    }

    TSharedPtr<FCountAccessLogResult> FCountAccessLogResult::WithTotalCount(
        const TOptional<int64> TotalCount
    )
    {
        this->TotalCountValue = TotalCount;
        return SharedThis(this);
    }

    TSharedPtr<FCountAccessLogResult> FCountAccessLogResult::WithScanSize(
        const TOptional<int64> ScanSize
    )
    {
        this->ScanSizeValue = ScanSize;
        return SharedThis(this);
    }

    TSharedPtr<TArray<TSharedPtr<Model::FAccessLogCount>>> FCountAccessLogResult::GetItems() const
    {
        if (!ItemsValue.IsValid())
        {
            return nullptr;
        }
        return ItemsValue;
    }

    TOptional<FString> FCountAccessLogResult::GetNextPageToken() const
    {
        return NextPageTokenValue;
    }

    TOptional<int64> FCountAccessLogResult::GetTotalCount() const
    {
        return TotalCountValue;
    }

    FString FCountAccessLogResult::GetTotalCountString() const
    {
        if (!TotalCountValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), TotalCountValue.GetValue());
    }

    TOptional<int64> FCountAccessLogResult::GetScanSize() const
    {
        return ScanSizeValue;
    }

    FString FCountAccessLogResult::GetScanSizeString() const
    {
        if (!ScanSizeValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), ScanSizeValue.GetValue());
    }

    TSharedPtr<FCountAccessLogResult> FCountAccessLogResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FCountAccessLogResult>()
            ->WithItems(Data->HasField(ANSI_TO_TCHAR("items")) ? [Data]() -> TSharedPtr<TArray<Model::FAccessLogCountPtr>>
                 {
                    auto v = MakeShared<TArray<Model::FAccessLogCountPtr>>();
                    if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("items")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("items")))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("items")))
                        {
                            v->Add(Model::FAccessLogCount::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<Model::FAccessLogCountPtr>>())
            ->WithNextPageToken(Data->HasField(ANSI_TO_TCHAR("nextPageToken")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("nextPageToken"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithTotalCount(Data->HasField(ANSI_TO_TCHAR("totalCount")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("totalCount"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithScanSize(Data->HasField(ANSI_TO_TCHAR("scanSize")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("scanSize"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>());
    }

    TSharedPtr<FJsonObject> FCountAccessLogResult::ToJson() const
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
        if (NextPageTokenValue.IsSet())
        {
            JsonRootObject->SetStringField("nextPageToken", NextPageTokenValue.GetValue());
        }
        if (TotalCountValue.IsSet())
        {
            JsonRootObject->SetStringField("totalCount", FString::Printf(TEXT("%lld"), TotalCountValue.GetValue()));
        }
        if (ScanSizeValue.IsSet())
        {
            JsonRootObject->SetStringField("scanSize", FString::Printf(TEXT("%lld"), ScanSizeValue.GetValue()));
        }
        return JsonRootObject;
    }
}