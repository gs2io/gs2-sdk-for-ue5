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

#include "News/Result/DescribeNewsByUserIdResult.h"

namespace Gs2::News::Result
{
    FDescribeNewsByUserIdResult::FDescribeNewsByUserIdResult():
        ItemsValue(nullptr),
        ContentHashValue(TOptional<FString>()),
        TemplateHashValue(TOptional<FString>())
    {
    }

    FDescribeNewsByUserIdResult::FDescribeNewsByUserIdResult(
        const FDescribeNewsByUserIdResult& From
    ):
        ItemsValue(From.ItemsValue),
        ContentHashValue(From.ContentHashValue),
        TemplateHashValue(From.TemplateHashValue)
    {
    }

    TSharedPtr<FDescribeNewsByUserIdResult> FDescribeNewsByUserIdResult::WithItems(
        const TSharedPtr<TArray<TSharedPtr<Model::FNews>>> Items
    )
    {
        this->ItemsValue = Items;
        return SharedThis(this);
    }

    TSharedPtr<FDescribeNewsByUserIdResult> FDescribeNewsByUserIdResult::WithContentHash(
        const TOptional<FString> ContentHash
    )
    {
        this->ContentHashValue = ContentHash;
        return SharedThis(this);
    }

    TSharedPtr<FDescribeNewsByUserIdResult> FDescribeNewsByUserIdResult::WithTemplateHash(
        const TOptional<FString> TemplateHash
    )
    {
        this->TemplateHashValue = TemplateHash;
        return SharedThis(this);
    }

    TSharedPtr<TArray<TSharedPtr<Model::FNews>>> FDescribeNewsByUserIdResult::GetItems() const
    {
        if (!ItemsValue.IsValid())
        {
            return nullptr;
        }
        return ItemsValue;
    }

    TOptional<FString> FDescribeNewsByUserIdResult::GetContentHash() const
    {
        return ContentHashValue;
    }

    TOptional<FString> FDescribeNewsByUserIdResult::GetTemplateHash() const
    {
        return TemplateHashValue;
    }

    TSharedPtr<FDescribeNewsByUserIdResult> FDescribeNewsByUserIdResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FDescribeNewsByUserIdResult>()
            ->WithItems(Data->HasField("items") ? [Data]() -> TSharedPtr<TArray<Model::FNewsPtr>>
                 {
                    auto v = MakeShared<TArray<Model::FNewsPtr>>();
                    if (!Data->HasTypedField<EJson::Null>("items") && Data->HasTypedField<EJson::Array>("items"))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField("items"))
                        {
                            v->Add(Model::FNews::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : nullptr)
            ->WithContentHash(Data->HasField("contentHash") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("contentHash", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithTemplateHash(Data->HasField("templateHash") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("templateHash", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FDescribeNewsByUserIdResult::ToJson() const
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
        if (ContentHashValue.IsSet())
        {
            JsonRootObject->SetStringField("contentHash", ContentHashValue.GetValue());
        }
        if (TemplateHashValue.IsSet())
        {
            JsonRootObject->SetStringField("templateHash", TemplateHashValue.GetValue());
        }
        return JsonRootObject;
    }
}