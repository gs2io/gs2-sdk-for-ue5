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

#include "Dictionary/Result/AddEntriesByUserIdResult.h"

namespace Gs2::Dictionary::Result
{
    FAddEntriesByUserIdResult::FAddEntriesByUserIdResult():
        ItemsValue(nullptr)
    {
    }

    FAddEntriesByUserIdResult::FAddEntriesByUserIdResult(
        const FAddEntriesByUserIdResult& From
    ):
        ItemsValue(From.ItemsValue)
    {
    }

    TSharedPtr<FAddEntriesByUserIdResult> FAddEntriesByUserIdResult::WithItems(
        const TSharedPtr<TArray<TSharedPtr<Model::FEntry>>> Items
    )
    {
        this->ItemsValue = Items;
        return SharedThis(this);
    }

    TSharedPtr<TArray<TSharedPtr<Model::FEntry>>> FAddEntriesByUserIdResult::GetItems() const
    {
        if (!ItemsValue.IsValid())
        {
            return nullptr;
        }
        return ItemsValue;
    }

    TSharedPtr<FAddEntriesByUserIdResult> FAddEntriesByUserIdResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FAddEntriesByUserIdResult>()
            ->WithItems(Data->HasField("items") ? [Data]() -> TSharedPtr<TArray<Model::FEntryPtr>>
                 {
                    auto v = MakeShared<TArray<Model::FEntryPtr>>();
                    if (!Data->HasTypedField<EJson::Null>("items") && Data->HasTypedField<EJson::Array>("items"))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField("items"))
                        {
                            v->Add(Model::FEntry::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : nullptr);
    }

    TSharedPtr<FJsonObject> FAddEntriesByUserIdResult::ToJson() const
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