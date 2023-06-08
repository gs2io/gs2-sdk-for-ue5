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

#include "Schedule/Result/GetEventByUserIdResult.h"

namespace Gs2::Schedule::Result
{
    FGetEventByUserIdResult::FGetEventByUserIdResult():
        ItemValue(nullptr),
        RepeatCountValue(TOptional<int32>()),
        InScheduleValue(TOptional<bool>()),
        RepeatScheduleValue(nullptr)
    {
    }

    FGetEventByUserIdResult::FGetEventByUserIdResult(
        const FGetEventByUserIdResult& From
    ):
        ItemValue(From.ItemValue),
        RepeatCountValue(From.RepeatCountValue),
        InScheduleValue(From.InScheduleValue),
        RepeatScheduleValue(From.RepeatScheduleValue)
    {
    }

    TSharedPtr<FGetEventByUserIdResult> FGetEventByUserIdResult::WithItem(
        const TSharedPtr<Model::FEvent> Item
    )
    {
        this->ItemValue = Item;
        return SharedThis(this);
    }

    TSharedPtr<FGetEventByUserIdResult> FGetEventByUserIdResult::WithRepeatCount(
        const TOptional<int32> RepeatCount
    )
    {
        this->RepeatCountValue = RepeatCount;
        return SharedThis(this);
    }

    TSharedPtr<FGetEventByUserIdResult> FGetEventByUserIdResult::WithInSchedule(
        const TOptional<bool> InSchedule
    )
    {
        this->InScheduleValue = InSchedule;
        return SharedThis(this);
    }

    TSharedPtr<FGetEventByUserIdResult> FGetEventByUserIdResult::WithRepeatSchedule(
        const TSharedPtr<Model::FRepeatSchedule> RepeatSchedule
    )
    {
        this->RepeatScheduleValue = RepeatSchedule;
        return SharedThis(this);
    }

    TSharedPtr<Model::FEvent> FGetEventByUserIdResult::GetItem() const
    {
        if (!ItemValue.IsValid())
        {
            return nullptr;
        }
        return ItemValue;
    }

    TOptional<int32> FGetEventByUserIdResult::GetRepeatCount() const
    {
        return RepeatCountValue;
    }

    FString FGetEventByUserIdResult::GetRepeatCountString() const
    {
        if (!RepeatCountValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), RepeatCountValue.GetValue());
    }

    TOptional<bool> FGetEventByUserIdResult::GetInSchedule() const
    {
        return InScheduleValue;
    }

    FString FGetEventByUserIdResult::GetInScheduleString() const
    {
        if (!InScheduleValue.IsSet())
        {
            return FString("null");
        }
        return FString(InScheduleValue.GetValue() ? "true" : "false");
    }

    TSharedPtr<Model::FRepeatSchedule> FGetEventByUserIdResult::GetRepeatSchedule() const
    {
        if (!RepeatScheduleValue.IsValid())
        {
            return nullptr;
        }
        return RepeatScheduleValue;
    }

    TSharedPtr<FGetEventByUserIdResult> FGetEventByUserIdResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FGetEventByUserIdResult>()
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
                }() : TOptional<int32>())
            ->WithInSchedule(Data->HasField("inSchedule") ? [Data]() -> TOptional<bool>
                {
                    bool v;
                    if (Data->TryGetBoolField("inSchedule", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<bool>();
                }() : TOptional<bool>())
            ->WithRepeatSchedule(Data->HasField("repeatSchedule") ? [Data]() -> Model::FRepeatSchedulePtr
                 {
                    if (Data->HasTypedField<EJson::Null>("repeatSchedule"))
                    {
                        return nullptr;
                    }
                    return Model::FRepeatSchedule::FromJson(Data->GetObjectField("repeatSchedule"));
                 }() : nullptr);
    }

    TSharedPtr<FJsonObject> FGetEventByUserIdResult::ToJson() const
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
        if (InScheduleValue.IsSet())
        {
            JsonRootObject->SetBoolField("inSchedule", InScheduleValue.GetValue());
        }
        if (RepeatScheduleValue != nullptr && RepeatScheduleValue.IsValid())
        {
            JsonRootObject->SetObjectField("repeatSchedule", RepeatScheduleValue->ToJson());
        }
        return JsonRootObject;
    }
}