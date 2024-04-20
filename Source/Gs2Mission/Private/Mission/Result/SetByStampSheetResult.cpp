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

#include "Mission/Result/SetByStampSheetResult.h"

namespace Gs2::Mission::Result
{
    FSetByStampSheetResult::FSetByStampSheetResult():
        ItemValue(nullptr),
        OldValue(nullptr),
        ChangedCompletesValue(nullptr)
    {
    }

    FSetByStampSheetResult::FSetByStampSheetResult(
        const FSetByStampSheetResult& From
    ):
        ItemValue(From.ItemValue),
        OldValue(From.OldValue),
        ChangedCompletesValue(From.ChangedCompletesValue)
    {
    }

    TSharedPtr<FSetByStampSheetResult> FSetByStampSheetResult::WithItem(
        const TSharedPtr<Model::FCounter> Item
    )
    {
        this->ItemValue = Item;
        return SharedThis(this);
    }

    TSharedPtr<FSetByStampSheetResult> FSetByStampSheetResult::WithOld(
        const TSharedPtr<Model::FCounter> Old
    )
    {
        this->OldValue = Old;
        return SharedThis(this);
    }

    TSharedPtr<FSetByStampSheetResult> FSetByStampSheetResult::WithChangedCompletes(
        const TSharedPtr<TArray<TSharedPtr<Model::FComplete>>> ChangedCompletes
    )
    {
        this->ChangedCompletesValue = ChangedCompletes;
        return SharedThis(this);
    }

    TSharedPtr<Model::FCounter> FSetByStampSheetResult::GetItem() const
    {
        if (!ItemValue.IsValid())
        {
            return nullptr;
        }
        return ItemValue;
    }

    TSharedPtr<Model::FCounter> FSetByStampSheetResult::GetOld() const
    {
        if (!OldValue.IsValid())
        {
            return nullptr;
        }
        return OldValue;
    }

    TSharedPtr<TArray<TSharedPtr<Model::FComplete>>> FSetByStampSheetResult::GetChangedCompletes() const
    {
        if (!ChangedCompletesValue.IsValid())
        {
            return nullptr;
        }
        return ChangedCompletesValue;
    }

    TSharedPtr<FSetByStampSheetResult> FSetByStampSheetResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FSetByStampSheetResult>()
            ->WithItem(Data->HasField("item") ? [Data]() -> Model::FCounterPtr
                 {
                    if (Data->HasTypedField<EJson::Null>("item"))
                    {
                        return nullptr;
                    }
                    return Model::FCounter::FromJson(Data->GetObjectField("item"));
                 }() : nullptr)
            ->WithOld(Data->HasField("old") ? [Data]() -> Model::FCounterPtr
                 {
                    if (Data->HasTypedField<EJson::Null>("old"))
                    {
                        return nullptr;
                    }
                    return Model::FCounter::FromJson(Data->GetObjectField("old"));
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

    TSharedPtr<FJsonObject> FSetByStampSheetResult::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ItemValue != nullptr && ItemValue.IsValid())
        {
            JsonRootObject->SetObjectField("item", ItemValue->ToJson());
        }
        if (OldValue != nullptr && OldValue.IsValid())
        {
            JsonRootObject->SetObjectField("old", OldValue->ToJson());
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