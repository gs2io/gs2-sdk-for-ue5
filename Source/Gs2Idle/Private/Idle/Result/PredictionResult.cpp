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

#include "Idle/Result/PredictionResult.h"

namespace Gs2::Idle::Result
{
    FPredictionResult::FPredictionResult():
        ItemsValue(nullptr),
        StatusValue(nullptr)
    {
    }

    FPredictionResult::FPredictionResult(
        const FPredictionResult& From
    ):
        ItemsValue(From.ItemsValue),
        StatusValue(From.StatusValue)
    {
    }

    TSharedPtr<FPredictionResult> FPredictionResult::WithItems(
        const TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> Items
    )
    {
        this->ItemsValue = Items;
        return SharedThis(this);
    }

    TSharedPtr<FPredictionResult> FPredictionResult::WithStatus(
        const TSharedPtr<Model::FStatus> Status
    )
    {
        this->StatusValue = Status;
        return SharedThis(this);
    }

    TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> FPredictionResult::GetItems() const
    {
        if (!ItemsValue.IsValid())
        {
            return nullptr;
        }
        return ItemsValue;
    }

    TSharedPtr<Model::FStatus> FPredictionResult::GetStatus() const
    {
        if (!StatusValue.IsValid())
        {
            return nullptr;
        }
        return StatusValue;
    }

    TSharedPtr<FPredictionResult> FPredictionResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FPredictionResult>()
            ->WithItems(Data->HasField(ANSI_TO_TCHAR("items")) ? [Data]() -> TSharedPtr<TArray<Model::FAcquireActionPtr>>
                 {
                    auto v = MakeShared<TArray<Model::FAcquireActionPtr>>();
                    if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("items")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("items")))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("items")))
                        {
                            v->Add(Model::FAcquireAction::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<Model::FAcquireActionPtr>>())
            ->WithStatus(Data->HasField(ANSI_TO_TCHAR("status")) ? [Data]() -> Model::FStatusPtr
                 {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("status")))
                    {
                        return nullptr;
                    }
                    return Model::FStatus::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("status")));
                 }() : nullptr);
    }

    TSharedPtr<FJsonObject> FPredictionResult::ToJson() const
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
        if (StatusValue != nullptr && StatusValue.IsValid())
        {
            JsonRootObject->SetObjectField("status", StatusValue->ToJson());
        }
        return JsonRootObject;
    }
}