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

#include "Datastore/Result/DescribeDataObjectHistoriesByUserIdResult.h"

namespace Gs2::Datastore::Result
{
    FDescribeDataObjectHistoriesByUserIdResult::FDescribeDataObjectHistoriesByUserIdResult():
        ItemsValue(nullptr),
        NextPageTokenValue(TOptional<FString>())
    {
    }

    FDescribeDataObjectHistoriesByUserIdResult::FDescribeDataObjectHistoriesByUserIdResult(
        const FDescribeDataObjectHistoriesByUserIdResult& From
    ):
        ItemsValue(From.ItemsValue),
        NextPageTokenValue(From.NextPageTokenValue)
    {
    }

    TSharedPtr<FDescribeDataObjectHistoriesByUserIdResult> FDescribeDataObjectHistoriesByUserIdResult::WithItems(
        const TSharedPtr<TArray<TSharedPtr<Model::FDataObjectHistory>>> Items
    )
    {
        this->ItemsValue = Items;
        return SharedThis(this);
    }

    TSharedPtr<FDescribeDataObjectHistoriesByUserIdResult> FDescribeDataObjectHistoriesByUserIdResult::WithNextPageToken(
        const TOptional<FString> NextPageToken
    )
    {
        this->NextPageTokenValue = NextPageToken;
        return SharedThis(this);
    }

    TSharedPtr<TArray<TSharedPtr<Model::FDataObjectHistory>>> FDescribeDataObjectHistoriesByUserIdResult::GetItems() const
    {
        if (!ItemsValue.IsValid())
        {
            return nullptr;
        }
        return ItemsValue;
    }

    TOptional<FString> FDescribeDataObjectHistoriesByUserIdResult::GetNextPageToken() const
    {
        return NextPageTokenValue;
    }

    TSharedPtr<FDescribeDataObjectHistoriesByUserIdResult> FDescribeDataObjectHistoriesByUserIdResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FDescribeDataObjectHistoriesByUserIdResult>()
            ->WithItems(Data->HasField("items") ? [Data]() -> TSharedPtr<TArray<Model::FDataObjectHistoryPtr>>
                 {
                    auto v = MakeShared<TArray<Model::FDataObjectHistoryPtr>>();
                    if (!Data->HasTypedField<EJson::Null>("items") && Data->HasTypedField<EJson::Array>("items"))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField("items"))
                        {
                            v->Add(Model::FDataObjectHistory::FromJson(JsonObjectValue->AsObject()));
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

    TSharedPtr<FJsonObject> FDescribeDataObjectHistoriesByUserIdResult::ToJson() const
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