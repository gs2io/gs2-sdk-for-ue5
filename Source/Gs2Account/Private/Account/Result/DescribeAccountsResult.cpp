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

#include "Account/Result/DescribeAccountsResult.h"

namespace Gs2::Account::Result
{
    FDescribeAccountsResult::FDescribeAccountsResult():
        ItemsValue(nullptr),
        NextPageTokenValue(TOptional<FString>())
    {
    }

    FDescribeAccountsResult::FDescribeAccountsResult(
        const FDescribeAccountsResult& From
    ):
        ItemsValue(From.ItemsValue),
        NextPageTokenValue(From.NextPageTokenValue)
    {
    }

    TSharedPtr<FDescribeAccountsResult> FDescribeAccountsResult::WithItems(
        const TSharedPtr<TArray<TSharedPtr<Model::FAccount>>> Items
    )
    {
        this->ItemsValue = Items;
        return SharedThis(this);
    }

    TSharedPtr<FDescribeAccountsResult> FDescribeAccountsResult::WithNextPageToken(
        const TOptional<FString> NextPageToken
    )
    {
        this->NextPageTokenValue = NextPageToken;
        return SharedThis(this);
    }

    TSharedPtr<TArray<TSharedPtr<Model::FAccount>>> FDescribeAccountsResult::GetItems() const
    {
        if (!ItemsValue.IsValid())
        {
            return nullptr;
        }
        return ItemsValue;
    }

    TOptional<FString> FDescribeAccountsResult::GetNextPageToken() const
    {
        return NextPageTokenValue;
    }

    TSharedPtr<FDescribeAccountsResult> FDescribeAccountsResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FDescribeAccountsResult>()
            ->WithItems(Data->HasField(ANSI_TO_TCHAR("items")) ? [Data]() -> TSharedPtr<TArray<Model::FAccountPtr>>
                 {
                    auto v = MakeShared<TArray<Model::FAccountPtr>>();
                    if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("items")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("items")))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("items")))
                        {
                            v->Add(Model::FAccount::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<Model::FAccountPtr>>())
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

    TSharedPtr<FJsonObject> FDescribeAccountsResult::ToJson() const
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