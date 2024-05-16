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

#include "Exchange/Result/DescribeIncrementalRateModelsResult.h"

namespace Gs2::Exchange::Result
{
    FDescribeIncrementalRateModelsResult::FDescribeIncrementalRateModelsResult():
        ItemsValue(nullptr)
    {
    }

    FDescribeIncrementalRateModelsResult::FDescribeIncrementalRateModelsResult(
        const FDescribeIncrementalRateModelsResult& From
    ):
        ItemsValue(From.ItemsValue)
    {
    }

    TSharedPtr<FDescribeIncrementalRateModelsResult> FDescribeIncrementalRateModelsResult::WithItems(
        const TSharedPtr<TArray<TSharedPtr<Model::FIncrementalRateModel>>> Items
    )
    {
        this->ItemsValue = Items;
        return SharedThis(this);
    }

    TSharedPtr<TArray<TSharedPtr<Model::FIncrementalRateModel>>> FDescribeIncrementalRateModelsResult::GetItems() const
    {
        if (!ItemsValue.IsValid())
        {
            return nullptr;
        }
        return ItemsValue;
    }

    TSharedPtr<FDescribeIncrementalRateModelsResult> FDescribeIncrementalRateModelsResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FDescribeIncrementalRateModelsResult>()
            ->WithItems(Data->HasField(ANSI_TO_TCHAR("items")) ? [Data]() -> TSharedPtr<TArray<Model::FIncrementalRateModelPtr>>
                 {
                    auto v = MakeShared<TArray<Model::FIncrementalRateModelPtr>>();
                    if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("items")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("items")))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("items")))
                        {
                            v->Add(Model::FIncrementalRateModel::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<Model::FIncrementalRateModelPtr>>());
    }

    TSharedPtr<FJsonObject> FDescribeIncrementalRateModelsResult::ToJson() const
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