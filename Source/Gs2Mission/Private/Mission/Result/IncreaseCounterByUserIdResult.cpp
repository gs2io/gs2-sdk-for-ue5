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

#include "Mission/Result/IncreaseCounterByUserIdResult.h"

namespace Gs2::Mission::Result
{
    FIncreaseCounterByUserIdResult::FIncreaseCounterByUserIdResult():
        ItemValue(nullptr),
        ChangedCompletesValue(nullptr)
    {
    }

    FIncreaseCounterByUserIdResult::FIncreaseCounterByUserIdResult(
        const FIncreaseCounterByUserIdResult& From
    ):
        ItemValue(From.ItemValue),
        ChangedCompletesValue(From.ChangedCompletesValue)
    {
    }

    TSharedPtr<FIncreaseCounterByUserIdResult> FIncreaseCounterByUserIdResult::WithItem(
        const TSharedPtr<Model::FCounter> Item
    )
    {
        this->ItemValue = Item;
        return SharedThis(this);
    }

    TSharedPtr<FIncreaseCounterByUserIdResult> FIncreaseCounterByUserIdResult::WithChangedCompletes(
        const TSharedPtr<TArray<TSharedPtr<Model::FComplete>>> ChangedCompletes
    )
    {
        this->ChangedCompletesValue = ChangedCompletes;
        return SharedThis(this);
    }

    TSharedPtr<Model::FCounter> FIncreaseCounterByUserIdResult::GetItem() const
    {
        if (!ItemValue.IsValid())
        {
            return nullptr;
        }
        return ItemValue;
    }

    TSharedPtr<TArray<TSharedPtr<Model::FComplete>>> FIncreaseCounterByUserIdResult::GetChangedCompletes() const
    {
        if (!ChangedCompletesValue.IsValid())
        {
            return nullptr;
        }
        return ChangedCompletesValue;
    }

    TSharedPtr<FIncreaseCounterByUserIdResult> FIncreaseCounterByUserIdResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FIncreaseCounterByUserIdResult>()
            ->WithItem(Data->HasField("item") ? [Data]() -> Model::FCounterPtr
                 {
                    if (Data->HasTypedField<EJson::Null>("item"))
                    {
                        return nullptr;
                    }
                    return Model::FCounter::FromJson(Data->GetObjectField("item"));
                 }() : nullptr)
            ->WithChangedCompletes(Data->HasField("changedCompletes") ? [Data]() -> TSharedPtr<TArray<Model::FCompletePtr>>
                 {
                    auto v = MakeShared<TArray<Model::FCompletePtr>>();
                    if (!Data->HasTypedField<EJson::Null>("changedCompletes") && Data->HasTypedField<EJson::Array>("changedCompletes"))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField("changedCompletes"))
                        {
                            v->Add(Model::FComplete::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<Model::FCompletePtr>>());
    }

    TSharedPtr<FJsonObject> FIncreaseCounterByUserIdResult::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ItemValue != nullptr && ItemValue.IsValid())
        {
            JsonRootObject->SetObjectField("item", ItemValue->ToJson());
        }
        if (ChangedCompletesValue != nullptr && ChangedCompletesValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *ChangedCompletesValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("changedCompletes", v);
        }
        return JsonRootObject;
    }
}