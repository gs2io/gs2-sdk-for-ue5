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

#include "Log/Result/CountExecuteStampSheetLogResult.h"

namespace Gs2::Log::Result
{
    FCountExecuteStampSheetLogResult::FCountExecuteStampSheetLogResult():
        ItemsValue(nullptr),
        NextPageTokenValue(TOptional<FString>()),
        TotalCountValue(TOptional<int64>()),
        ScanSizeValue(TOptional<int64>())
    {
    }

    FCountExecuteStampSheetLogResult::FCountExecuteStampSheetLogResult(
        const FCountExecuteStampSheetLogResult& From
    ):
        ItemsValue(From.ItemsValue),
        NextPageTokenValue(From.NextPageTokenValue),
        TotalCountValue(From.TotalCountValue),
        ScanSizeValue(From.ScanSizeValue)
    {
    }

    TSharedPtr<FCountExecuteStampSheetLogResult> FCountExecuteStampSheetLogResult::WithItems(
        const TSharedPtr<TArray<TSharedPtr<Model::FExecuteStampSheetLogCount>>> Items
    )
    {
        this->ItemsValue = Items;
        return SharedThis(this);
    }

    TSharedPtr<FCountExecuteStampSheetLogResult> FCountExecuteStampSheetLogResult::WithNextPageToken(
        const TOptional<FString> NextPageToken
    )
    {
        this->NextPageTokenValue = NextPageToken;
        return SharedThis(this);
    }

    TSharedPtr<FCountExecuteStampSheetLogResult> FCountExecuteStampSheetLogResult::WithTotalCount(
        const TOptional<int64> TotalCount
    )
    {
        this->TotalCountValue = TotalCount;
        return SharedThis(this);
    }

    TSharedPtr<FCountExecuteStampSheetLogResult> FCountExecuteStampSheetLogResult::WithScanSize(
        const TOptional<int64> ScanSize
    )
    {
        this->ScanSizeValue = ScanSize;
        return SharedThis(this);
    }

    TSharedPtr<TArray<TSharedPtr<Model::FExecuteStampSheetLogCount>>> FCountExecuteStampSheetLogResult::GetItems() const
    {
        if (!ItemsValue.IsValid())
        {
            return nullptr;
        }
        return ItemsValue;
    }

    TOptional<FString> FCountExecuteStampSheetLogResult::GetNextPageToken() const
    {
        return NextPageTokenValue;
    }

    TOptional<int64> FCountExecuteStampSheetLogResult::GetTotalCount() const
    {
        return TotalCountValue;
    }

    FString FCountExecuteStampSheetLogResult::GetTotalCountString() const
    {
        if (!TotalCountValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), TotalCountValue.GetValue());
    }

    TOptional<int64> FCountExecuteStampSheetLogResult::GetScanSize() const
    {
        return ScanSizeValue;
    }

    FString FCountExecuteStampSheetLogResult::GetScanSizeString() const
    {
        if (!ScanSizeValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), ScanSizeValue.GetValue());
    }

    TSharedPtr<FCountExecuteStampSheetLogResult> FCountExecuteStampSheetLogResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FCountExecuteStampSheetLogResult>()
            ->WithItems(Data->HasField(ANSI_TO_TCHAR("items")) ? [Data]() -> TSharedPtr<TArray<Model::FExecuteStampSheetLogCountPtr>>
                 {
                    auto v = MakeShared<TArray<Model::FExecuteStampSheetLogCountPtr>>();
                    if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("items")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("items")))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("items")))
                        {
                            v->Add(Model::FExecuteStampSheetLogCount::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<Model::FExecuteStampSheetLogCountPtr>>())
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

    TSharedPtr<FJsonObject> FCountExecuteStampSheetLogResult::ToJson() const
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