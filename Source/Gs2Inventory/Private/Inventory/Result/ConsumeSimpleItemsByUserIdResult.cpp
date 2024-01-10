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

#include "Inventory/Result/ConsumeSimpleItemsByUserIdResult.h"

namespace Gs2::Inventory::Result
{
    FConsumeSimpleItemsByUserIdResult::FConsumeSimpleItemsByUserIdResult():
        ItemsValue(nullptr)
    {
    }

    FConsumeSimpleItemsByUserIdResult::FConsumeSimpleItemsByUserIdResult(
        const FConsumeSimpleItemsByUserIdResult& From
    ):
        ItemsValue(From.ItemsValue)
    {
    }

    TSharedPtr<FConsumeSimpleItemsByUserIdResult> FConsumeSimpleItemsByUserIdResult::WithItems(
        const TSharedPtr<TArray<TSharedPtr<Model::FSimpleItem>>> Items
    )
    {
        this->ItemsValue = Items;
        return SharedThis(this);
    }

    TSharedPtr<TArray<TSharedPtr<Model::FSimpleItem>>> FConsumeSimpleItemsByUserIdResult::GetItems() const
    {
        if (!ItemsValue.IsValid())
        {
            return nullptr;
        }
        return ItemsValue;
    }

    TSharedPtr<FConsumeSimpleItemsByUserIdResult> FConsumeSimpleItemsByUserIdResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FConsumeSimpleItemsByUserIdResult>()
            ->WithItems(Data->HasField("items") ? [Data]() -> TSharedPtr<TArray<Model::FSimpleItemPtr>>
                 {
                    auto v = MakeShared<TArray<Model::FSimpleItemPtr>>();
                    if (!Data->HasTypedField<EJson::Null>("items") && Data->HasTypedField<EJson::Array>("items"))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField("items"))
                        {
                            v->Add(Model::FSimpleItem::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<Model::FSimpleItemPtr>>());
    }

    TSharedPtr<FJsonObject> FConsumeSimpleItemsByUserIdResult::ToJson() const
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