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

#include "Realtime/Result/DescribeRoomsResult.h"

namespace Gs2::Realtime::Result
{
    FDescribeRoomsResult::FDescribeRoomsResult():
        ItemsValue(nullptr),
        NextPageTokenValue(TOptional<FString>())
    {
    }

    FDescribeRoomsResult::FDescribeRoomsResult(
        const FDescribeRoomsResult& From
    ):
        ItemsValue(From.ItemsValue),
        NextPageTokenValue(From.NextPageTokenValue)
    {
    }

    TSharedPtr<FDescribeRoomsResult> FDescribeRoomsResult::WithItems(
        const TSharedPtr<TArray<TSharedPtr<Model::FRoom>>> Items
    )
    {
        this->ItemsValue = Items;
        return SharedThis(this);
    }

    TSharedPtr<FDescribeRoomsResult> FDescribeRoomsResult::WithNextPageToken(
        const TOptional<FString> NextPageToken
    )
    {
        this->NextPageTokenValue = NextPageToken;
        return SharedThis(this);
    }

    TSharedPtr<TArray<TSharedPtr<Model::FRoom>>> FDescribeRoomsResult::GetItems() const
    {
        if (!ItemsValue.IsValid())
        {
            return nullptr;
        }
        return ItemsValue;
    }

    TOptional<FString> FDescribeRoomsResult::GetNextPageToken() const
    {
        return NextPageTokenValue;
    }

    TSharedPtr<FDescribeRoomsResult> FDescribeRoomsResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FDescribeRoomsResult>()
            ->WithItems(Data->HasField("items") ? [Data]() -> TSharedPtr<TArray<Model::FRoomPtr>>
                 {
                    auto v = MakeShared<TArray<Model::FRoomPtr>>();
                    if (!Data->HasTypedField<EJson::Null>("items") && Data->HasTypedField<EJson::Array>("items"))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField("items"))
                        {
                            v->Add(Model::FRoom::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : nullptr)
            ->WithNextPageToken(Data->HasField("nextPageToken") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("nextPageToken", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FDescribeRoomsResult::ToJson() const
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
        return JsonRootObject;
    }
}