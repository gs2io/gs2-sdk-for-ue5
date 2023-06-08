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
        InScheduleValue(TOptional<bool>()),
        ScheduleStartAtValue(TOptional<int64>()),
        ScheduleEndAtValue(TOptional<int64>()),
        RepeatScheduleValue(nullptr)
    {
    }

    FGetEventByUserIdResult::FGetEventByUserIdResult(
        const FGetEventByUserIdResult& From
    ):
        ItemValue(From.ItemValue),
        InScheduleValue(From.InScheduleValue),
        ScheduleStartAtValue(From.ScheduleStartAtValue),
        ScheduleEndAtValue(From.ScheduleEndAtValue),
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

    TSharedPtr<FGetEventByUserIdResult> FGetEventByUserIdResult::WithInSchedule(
        const TOptional<bool> InSchedule
    )
    {
        this->InScheduleValue = InSchedule;
        return SharedThis(this);
    }

    TSharedPtr<FGetEventByUserIdResult> FGetEventByUserIdResult::WithScheduleStartAt(
        const TOptional<int64> ScheduleStartAt
    )
    {
        this->ScheduleStartAtValue = ScheduleStartAt;
        return SharedThis(this);
    }

    TSharedPtr<FGetEventByUserIdResult> FGetEventByUserIdResult::WithScheduleEndAt(
        const TOptional<int64> ScheduleEndAt
    )
    {
        this->ScheduleEndAtValue = ScheduleEndAt;
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

    TOptional<int64> FGetEventByUserIdResult::GetScheduleStartAt() const
    {
        return ScheduleStartAtValue;
    }

    FString FGetEventByUserIdResult::GetScheduleStartAtString() const
    {
        if (!ScheduleStartAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), ScheduleStartAtValue.GetValue());
    }

    TOptional<int64> FGetEventByUserIdResult::GetScheduleEndAt() const
    {
        return ScheduleEndAtValue;
    }

    FString FGetEventByUserIdResult::GetScheduleEndAtString() const
    {
        if (!ScheduleEndAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), ScheduleEndAtValue.GetValue());
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
            ->WithInSchedule(Data->HasField("inSchedule") ? [Data]() -> TOptional<bool>
                {
                    bool v;
                    if (Data->TryGetBoolField("inSchedule", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<bool>();
                }() : TOptional<bool>())
            ->WithScheduleStartAt(Data->HasField("scheduleStartAt") ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField("scheduleStartAt", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithScheduleEndAt(Data->HasField("scheduleEndAt") ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField("scheduleEndAt", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
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
        if (InScheduleValue.IsSet())
        {
            JsonRootObject->SetBoolField("inSchedule", InScheduleValue.GetValue());
        }
        if (ScheduleStartAtValue.IsSet())
        {
            JsonRootObject->SetStringField("scheduleStartAt", FString::Printf(TEXT("%lld"), ScheduleStartAtValue.GetValue()));
        }
        if (ScheduleEndAtValue.IsSet())
        {
            JsonRootObject->SetStringField("scheduleEndAt", FString::Printf(TEXT("%lld"), ScheduleEndAtValue.GetValue()));
        }
        if (RepeatScheduleValue != nullptr && RepeatScheduleValue.IsValid())
        {
            JsonRootObject->SetObjectField("repeatSchedule", RepeatScheduleValue->ToJson());
        }
        return JsonRootObject;
    }
}