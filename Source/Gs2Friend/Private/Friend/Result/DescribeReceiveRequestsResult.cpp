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

#include "Friend/Result/DescribeReceiveRequestsResult.h"

namespace Gs2::Friend::Result
{
    FDescribeReceiveRequestsResult::FDescribeReceiveRequestsResult():
        ItemsValue(nullptr),
        NextPageTokenValue(TOptional<FString>())
    {
    }

    FDescribeReceiveRequestsResult::FDescribeReceiveRequestsResult(
        const FDescribeReceiveRequestsResult& From
    ):
        ItemsValue(From.ItemsValue),
        NextPageTokenValue(From.NextPageTokenValue)
    {
    }

    TSharedPtr<FDescribeReceiveRequestsResult> FDescribeReceiveRequestsResult::WithItems(
        const TSharedPtr<TArray<TSharedPtr<Model::FFriendRequest>>> Items
    )
    {
        this->ItemsValue = Items;
        return SharedThis(this);
    }

    TSharedPtr<FDescribeReceiveRequestsResult> FDescribeReceiveRequestsResult::WithNextPageToken(
        const TOptional<FString> NextPageToken
    )
    {
        this->NextPageTokenValue = NextPageToken;
        return SharedThis(this);
    }

    TSharedPtr<TArray<TSharedPtr<Model::FFriendRequest>>> FDescribeReceiveRequestsResult::GetItems() const
    {
        if (!ItemsValue.IsValid())
        {
            return nullptr;
        }
        return ItemsValue;
    }

    TOptional<FString> FDescribeReceiveRequestsResult::GetNextPageToken() const
    {
        return NextPageTokenValue;
    }

    TSharedPtr<FDescribeReceiveRequestsResult> FDescribeReceiveRequestsResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FDescribeReceiveRequestsResult>()
            ->WithItems(Data->HasField("items") ? [Data]() -> TSharedPtr<TArray<Model::FFriendRequestPtr>>
                 {
                    auto v = MakeShared<TArray<Model::FFriendRequestPtr>>();
                    if (!Data->HasTypedField<EJson::Null>("items") && Data->HasTypedField<EJson::Array>("items"))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField("items"))
                        {
                            v->Add(Model::FFriendRequest::FromJson(JsonObjectValue->AsObject()));
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

    TSharedPtr<FJsonObject> FDescribeReceiveRequestsResult::ToJson() const
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