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

#include "Ranking/Result/DescribeSubscribesByCategoryNameAndUserIdResult.h"

namespace Gs2::Ranking::Result
{
    FDescribeSubscribesByCategoryNameAndUserIdResult::FDescribeSubscribesByCategoryNameAndUserIdResult():
        ItemsValue(nullptr)
    {
    }

    FDescribeSubscribesByCategoryNameAndUserIdResult::FDescribeSubscribesByCategoryNameAndUserIdResult(
        const FDescribeSubscribesByCategoryNameAndUserIdResult& From
    ):
        ItemsValue(From.ItemsValue)
    {
    }

    TSharedPtr<FDescribeSubscribesByCategoryNameAndUserIdResult> FDescribeSubscribesByCategoryNameAndUserIdResult::WithItems(
        const TSharedPtr<TArray<TSharedPtr<Model::FSubscribeUser>>> Items
    )
    {
        this->ItemsValue = Items;
        return SharedThis(this);
    }

    TSharedPtr<TArray<TSharedPtr<Model::FSubscribeUser>>> FDescribeSubscribesByCategoryNameAndUserIdResult::GetItems() const
    {
        if (!ItemsValue.IsValid())
        {
            return nullptr;
        }
        return ItemsValue;
    }

    TSharedPtr<FDescribeSubscribesByCategoryNameAndUserIdResult> FDescribeSubscribesByCategoryNameAndUserIdResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FDescribeSubscribesByCategoryNameAndUserIdResult>()
            ->WithItems(Data->HasField("items") ? [Data]() -> TSharedPtr<TArray<Model::FSubscribeUserPtr>>
                 {
                    auto v = MakeShared<TArray<Model::FSubscribeUserPtr>>();
                    if (!Data->HasTypedField<EJson::Null>("items") && Data->HasTypedField<EJson::Array>("items"))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField("items"))
                        {
                            v->Add(Model::FSubscribeUser::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<Model::FSubscribeUserPtr>>());
    }

    TSharedPtr<FJsonObject> FDescribeSubscribesByCategoryNameAndUserIdResult::ToJson() const
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
        return JsonRootObject;
    }
}