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

#include "Mission/Result/DecreaseCounterResult.h"

namespace Gs2::Mission::Result
{
    FDecreaseCounterResult::FDecreaseCounterResult():
        ItemValue(nullptr),
        ChangedCompletesValue(nullptr)
    {
    }

    FDecreaseCounterResult::FDecreaseCounterResult(
        const FDecreaseCounterResult& From
    ):
        ItemValue(From.ItemValue),
        ChangedCompletesValue(From.ChangedCompletesValue)
    {
    }

    TSharedPtr<FDecreaseCounterResult> FDecreaseCounterResult::WithItem(
        const TSharedPtr<Model::FCounter> Item
    )
    {
        this->ItemValue = Item;
        return SharedThis(this);
    }

    TSharedPtr<FDecreaseCounterResult> FDecreaseCounterResult::WithChangedCompletes(
        const TSharedPtr<TArray<TSharedPtr<Model::FComplete>>> ChangedCompletes
    )
    {
        this->ChangedCompletesValue = ChangedCompletes;
        return SharedThis(this);
    }

    TSharedPtr<Model::FCounter> FDecreaseCounterResult::GetItem() const
    {
        if (!ItemValue.IsValid())
        {
            return nullptr;
        }
        return ItemValue;
    }

    TSharedPtr<TArray<TSharedPtr<Model::FComplete>>> FDecreaseCounterResult::GetChangedCompletes() const
    {
        if (!ChangedCompletesValue.IsValid())
        {
            return nullptr;
        }
        return ChangedCompletesValue;
    }

    TSharedPtr<FDecreaseCounterResult> FDecreaseCounterResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FDecreaseCounterResult>()
            ->WithItem(Data->HasField(ANSI_TO_TCHAR("item")) ? [Data]() -> Model::FCounterPtr
                 {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("item")))
                    {
                        return nullptr;
                    }
                    return Model::FCounter::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("item")));
                 }() : nullptr)
            ->WithChangedCompletes(Data->HasField(ANSI_TO_TCHAR("changedCompletes")) ? [Data]() -> TSharedPtr<TArray<Model::FCompletePtr>>
                 {
                    auto v = MakeShared<TArray<Model::FCompletePtr>>();
                    if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("changedCompletes")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("changedCompletes")))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("changedCompletes")))
                        {
                            v->Add(Model::FComplete::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<Model::FCompletePtr>>());
    }

    TSharedPtr<FJsonObject> FDecreaseCounterResult::ToJson() const
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