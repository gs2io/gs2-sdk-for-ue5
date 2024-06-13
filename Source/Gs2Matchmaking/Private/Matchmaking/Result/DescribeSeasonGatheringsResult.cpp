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

#include "Matchmaking/Result/DescribeSeasonGatheringsResult.h"

namespace Gs2::Matchmaking::Result
{
    FDescribeSeasonGatheringsResult::FDescribeSeasonGatheringsResult():
        ItemsValue(nullptr),
        NextPageTokenValue(TOptional<FString>())
    {
    }

    FDescribeSeasonGatheringsResult::FDescribeSeasonGatheringsResult(
        const FDescribeSeasonGatheringsResult& From
    ):
        ItemsValue(From.ItemsValue),
        NextPageTokenValue(From.NextPageTokenValue)
    {
    }

    TSharedPtr<FDescribeSeasonGatheringsResult> FDescribeSeasonGatheringsResult::WithItems(
        const TSharedPtr<TArray<TSharedPtr<Model::FSeasonGathering>>> Items
    )
    {
        this->ItemsValue = Items;
        return SharedThis(this);
    }

    TSharedPtr<FDescribeSeasonGatheringsResult> FDescribeSeasonGatheringsResult::WithNextPageToken(
        const TOptional<FString> NextPageToken
    )
    {
        this->NextPageTokenValue = NextPageToken;
        return SharedThis(this);
    }

    TSharedPtr<TArray<TSharedPtr<Model::FSeasonGathering>>> FDescribeSeasonGatheringsResult::GetItems() const
    {
        if (!ItemsValue.IsValid())
        {
            return nullptr;
        }
        return ItemsValue;
    }

    TOptional<FString> FDescribeSeasonGatheringsResult::GetNextPageToken() const
    {
        return NextPageTokenValue;
    }

    TSharedPtr<FDescribeSeasonGatheringsResult> FDescribeSeasonGatheringsResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FDescribeSeasonGatheringsResult>()
            ->WithItems(Data->HasField(ANSI_TO_TCHAR("items")) ? [Data]() -> TSharedPtr<TArray<Model::FSeasonGatheringPtr>>
                 {
                    auto v = MakeShared<TArray<Model::FSeasonGatheringPtr>>();
                    if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("items")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("items")))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("items")))
                        {
                            v->Add(Model::FSeasonGathering::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<Model::FSeasonGatheringPtr>>())
            ->WithNextPageToken(Data->HasField(ANSI_TO_TCHAR("nextPageToken")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("nextPageToken"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FDescribeSeasonGatheringsResult::ToJson() const
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