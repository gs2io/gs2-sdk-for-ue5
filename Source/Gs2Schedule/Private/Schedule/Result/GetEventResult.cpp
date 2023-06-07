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

#include "Schedule/Result/GetEventResult.h"

namespace Gs2::Schedule::Result
{
    FGetEventResult::FGetEventResult():
        ItemValue(nullptr),
        RepeatCountValue(TOptional<int32>())
    {
    }

    FGetEventResult::FGetEventResult(
        const FGetEventResult& From
    ):
        ItemValue(From.ItemValue),
        RepeatCountValue(From.RepeatCountValue)
    {
    }

    TSharedPtr<FGetEventResult> FGetEventResult::WithItem(
        const TSharedPtr<Model::FEvent> Item
    )
    {
        this->ItemValue = Item;
        return SharedThis(this);
    }

    TSharedPtr<FGetEventResult> FGetEventResult::WithRepeatCount(
        const TOptional<int32> RepeatCount
    )
    {
        this->RepeatCountValue = RepeatCount;
        return SharedThis(this);
    }

    TSharedPtr<Model::FEvent> FGetEventResult::GetItem() const
    {
        if (!ItemValue.IsValid())
        {
            return nullptr;
        }
        return ItemValue;
    }

    TOptional<int32> FGetEventResult::GetRepeatCount() const
    {
        return RepeatCountValue;
    }

    FString FGetEventResult::GetRepeatCountString() const
    {
        if (!RepeatCountValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), RepeatCountValue.GetValue());
    }

    TSharedPtr<FGetEventResult> FGetEventResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FGetEventResult>()
            ->WithItem(Data->HasField("item") ? [Data]() -> Model::FEventPtr
                 {
                    if (Data->HasTypedField<EJson::Null>("item"))
                    {
                        return nullptr;
                    }
                    return Model::FEvent::FromJson(Data->GetObjectField("item"));
                 }() : nullptr)
            ->WithRepeatCount(Data->HasField("repeatCount") ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField("repeatCount", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>());
    }

    TSharedPtr<FJsonObject> FGetEventResult::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ItemValue != nullptr && ItemValue.IsValid())
        {
            JsonRootObject->SetObjectField("item", ItemValue->ToJson());
        }
        if (RepeatCountValue.IsSet())
        {
            JsonRootObject->SetNumberField("repeatCount", RepeatCountValue.GetValue());
        }
        return JsonRootObject;
    }
}