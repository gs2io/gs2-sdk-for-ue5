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

#include "MegaField/Result/DescribeAreaModelsResult.h"

namespace Gs2::MegaField::Result
{
    FDescribeAreaModelsResult::FDescribeAreaModelsResult():
        ItemsValue(nullptr)
    {
    }

    FDescribeAreaModelsResult::FDescribeAreaModelsResult(
        const FDescribeAreaModelsResult& From
    ):
        ItemsValue(From.ItemsValue)
    {
    }

    TSharedPtr<FDescribeAreaModelsResult> FDescribeAreaModelsResult::WithItems(
        const TSharedPtr<TArray<TSharedPtr<Model::FAreaModel>>> Items
    )
    {
        this->ItemsValue = Items;
        return SharedThis(this);
    }

    TSharedPtr<TArray<TSharedPtr<Model::FAreaModel>>> FDescribeAreaModelsResult::GetItems() const
    {
        if (!ItemsValue.IsValid())
        {
            return nullptr;
        }
        return ItemsValue;
    }

    TSharedPtr<FDescribeAreaModelsResult> FDescribeAreaModelsResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FDescribeAreaModelsResult>()
            ->WithItems(Data->HasField("items") ? [Data]() -> TSharedPtr<TArray<Model::FAreaModelPtr>>
                 {
                    auto v = MakeShared<TArray<Model::FAreaModelPtr>>();
                    if (!Data->HasTypedField<EJson::Null>("items") && Data->HasTypedField<EJson::Array>("items"))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField("items"))
                        {
                            v->Add(Model::FAreaModel::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<Model::FAreaModelPtr>>());
    }

    TSharedPtr<FJsonObject> FDescribeAreaModelsResult::ToJson() const
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