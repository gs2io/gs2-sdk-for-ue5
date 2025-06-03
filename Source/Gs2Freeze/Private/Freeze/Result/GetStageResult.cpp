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

#include "Freeze/Result/GetStageResult.h"

namespace Gs2::Freeze::Result
{
    FGetStageResult::FGetStageResult():
        ItemValue(nullptr),
        SourceValue(nullptr),
        CurrentValue(nullptr)
    {
    }

    FGetStageResult::FGetStageResult(
        const FGetStageResult& From
    ):
        ItemValue(From.ItemValue),
        SourceValue(From.SourceValue),
        CurrentValue(From.CurrentValue)
    {
    }

    TSharedPtr<FGetStageResult> FGetStageResult::WithItem(
        const TSharedPtr<Model::FStage> Item
    )
    {
        this->ItemValue = Item;
        return SharedThis(this);
    }

    TSharedPtr<FGetStageResult> FGetStageResult::WithSource(
        const TSharedPtr<TArray<TSharedPtr<Model::FMicroservice>>> Source
    )
    {
        this->SourceValue = Source;
        return SharedThis(this);
    }

    TSharedPtr<FGetStageResult> FGetStageResult::WithCurrent(
        const TSharedPtr<TArray<TSharedPtr<Model::FMicroservice>>> Current
    )
    {
        this->CurrentValue = Current;
        return SharedThis(this);
    }

    TSharedPtr<Model::FStage> FGetStageResult::GetItem() const
    {
        if (!ItemValue.IsValid())
        {
            return nullptr;
        }
        return ItemValue;
    }

    TSharedPtr<TArray<TSharedPtr<Model::FMicroservice>>> FGetStageResult::GetSource() const
    {
        if (!SourceValue.IsValid())
        {
            return nullptr;
        }
        return SourceValue;
    }

    TSharedPtr<TArray<TSharedPtr<Model::FMicroservice>>> FGetStageResult::GetCurrent() const
    {
        if (!CurrentValue.IsValid())
        {
            return nullptr;
        }
        return CurrentValue;
    }

    TSharedPtr<FGetStageResult> FGetStageResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FGetStageResult>()
            ->WithItem(Data->HasField(ANSI_TO_TCHAR("item")) ? [Data]() -> Model::FStagePtr
                 {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("item")))
                    {
                        return nullptr;
                    }
                    return Model::FStage::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("item")));
                 }() : nullptr)
            ->WithSource(Data->HasField(ANSI_TO_TCHAR("source")) ? [Data]() -> TSharedPtr<TArray<Model::FMicroservicePtr>>
                 {
                    auto v = MakeShared<TArray<Model::FMicroservicePtr>>();
                    if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("source")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("source")))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("source")))
                        {
                            v->Add(Model::FMicroservice::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<Model::FMicroservicePtr>>())
            ->WithCurrent(Data->HasField(ANSI_TO_TCHAR("current")) ? [Data]() -> TSharedPtr<TArray<Model::FMicroservicePtr>>
                 {
                    auto v = MakeShared<TArray<Model::FMicroservicePtr>>();
                    if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("current")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("current")))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("current")))
                        {
                            v->Add(Model::FMicroservice::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<Model::FMicroservicePtr>>());
    }

    TSharedPtr<FJsonObject> FGetStageResult::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ItemValue != nullptr && ItemValue.IsValid())
        {
            JsonRootObject->SetObjectField("item", ItemValue->ToJson());
        }
        if (SourceValue != nullptr && SourceValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *SourceValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("source", v);
        }
        if (CurrentValue != nullptr && CurrentValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *CurrentValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("current", v);
        }
        return JsonRootObject;
    }
}