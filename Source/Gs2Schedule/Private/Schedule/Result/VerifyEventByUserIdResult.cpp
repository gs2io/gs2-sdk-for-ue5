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

#include "Schedule/Result/VerifyEventByUserIdResult.h"

namespace Gs2::Schedule::Result
{
    FVerifyEventByUserIdResult::FVerifyEventByUserIdResult():
        ItemValue(nullptr),
        InScheduleValue(TOptional<bool>()),
        ScheduleStartAtValue(TOptional<int64>()),
        ScheduleEndAtValue(TOptional<int64>()),
        RepeatScheduleValue(nullptr),
        IsGlobalScheduleValue(TOptional<bool>())
    {
    }

    FVerifyEventByUserIdResult::FVerifyEventByUserIdResult(
        const FVerifyEventByUserIdResult& From
    ):
        ItemValue(From.ItemValue),
        InScheduleValue(From.InScheduleValue),
        ScheduleStartAtValue(From.ScheduleStartAtValue),
        ScheduleEndAtValue(From.ScheduleEndAtValue),
        RepeatScheduleValue(From.RepeatScheduleValue),
        IsGlobalScheduleValue(From.IsGlobalScheduleValue)
    {
    }

    TSharedPtr<FVerifyEventByUserIdResult> FVerifyEventByUserIdResult::WithItem(
        const TSharedPtr<Model::FEvent> Item
    )
    {
        this->ItemValue = Item;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyEventByUserIdResult> FVerifyEventByUserIdResult::WithInSchedule(
        const TOptional<bool> InSchedule
    )
    {
        this->InScheduleValue = InSchedule;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyEventByUserIdResult> FVerifyEventByUserIdResult::WithScheduleStartAt(
        const TOptional<int64> ScheduleStartAt
    )
    {
        this->ScheduleStartAtValue = ScheduleStartAt;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyEventByUserIdResult> FVerifyEventByUserIdResult::WithScheduleEndAt(
        const TOptional<int64> ScheduleEndAt
    )
    {
        this->ScheduleEndAtValue = ScheduleEndAt;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyEventByUserIdResult> FVerifyEventByUserIdResult::WithRepeatSchedule(
        const TSharedPtr<Model::FRepeatSchedule> RepeatSchedule
    )
    {
        this->RepeatScheduleValue = RepeatSchedule;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyEventByUserIdResult> FVerifyEventByUserIdResult::WithIsGlobalSchedule(
        const TOptional<bool> IsGlobalSchedule
    )
    {
        this->IsGlobalScheduleValue = IsGlobalSchedule;
        return SharedThis(this);
    }

    TSharedPtr<Model::FEvent> FVerifyEventByUserIdResult::GetItem() const
    {
        if (!ItemValue.IsValid())
        {
            return nullptr;
        }
        return ItemValue;
    }

    TOptional<bool> FVerifyEventByUserIdResult::GetInSchedule() const
    {
        return InScheduleValue;
    }

    FString FVerifyEventByUserIdResult::GetInScheduleString() const
    {
        if (!InScheduleValue.IsSet())
        {
            return FString("null");
        }
        return FString(InScheduleValue.GetValue() ? "true" : "false");
    }

    TOptional<int64> FVerifyEventByUserIdResult::GetScheduleStartAt() const
    {
        return ScheduleStartAtValue;
    }

    FString FVerifyEventByUserIdResult::GetScheduleStartAtString() const
    {
        if (!ScheduleStartAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), ScheduleStartAtValue.GetValue());
    }

    TOptional<int64> FVerifyEventByUserIdResult::GetScheduleEndAt() const
    {
        return ScheduleEndAtValue;
    }

    FString FVerifyEventByUserIdResult::GetScheduleEndAtString() const
    {
        if (!ScheduleEndAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), ScheduleEndAtValue.GetValue());
    }

    TSharedPtr<Model::FRepeatSchedule> FVerifyEventByUserIdResult::GetRepeatSchedule() const
    {
        if (!RepeatScheduleValue.IsValid())
        {
            return nullptr;
        }
        return RepeatScheduleValue;
    }

    TOptional<bool> FVerifyEventByUserIdResult::GetIsGlobalSchedule() const
    {
        return IsGlobalScheduleValue;
    }

    FString FVerifyEventByUserIdResult::GetIsGlobalScheduleString() const
    {
        if (!IsGlobalScheduleValue.IsSet())
        {
            return FString("null");
        }
        return FString(IsGlobalScheduleValue.GetValue() ? "true" : "false");
    }

    TSharedPtr<FVerifyEventByUserIdResult> FVerifyEventByUserIdResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FVerifyEventByUserIdResult>()
            ->WithItem(Data->HasField(ANSI_TO_TCHAR("item")) ? [Data]() -> Model::FEventPtr
                 {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("item")))
                    {
                        return nullptr;
                    }
                    return Model::FEvent::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("item")));
                 }() : nullptr)
            ->WithInSchedule(Data->HasField(ANSI_TO_TCHAR("inSchedule")) ? [Data]() -> TOptional<bool>
                {
                    bool v;
                    if (Data->TryGetBoolField(ANSI_TO_TCHAR("inSchedule"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<bool>();
                }() : TOptional<bool>())
            ->WithScheduleStartAt(Data->HasField(ANSI_TO_TCHAR("scheduleStartAt")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("scheduleStartAt"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithScheduleEndAt(Data->HasField(ANSI_TO_TCHAR("scheduleEndAt")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("scheduleEndAt"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithRepeatSchedule(Data->HasField(ANSI_TO_TCHAR("repeatSchedule")) ? [Data]() -> Model::FRepeatSchedulePtr
                 {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("repeatSchedule")))
                    {
                        return nullptr;
                    }
                    return Model::FRepeatSchedule::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("repeatSchedule")));
                 }() : nullptr)
            ->WithIsGlobalSchedule(Data->HasField(ANSI_TO_TCHAR("isGlobalSchedule")) ? [Data]() -> TOptional<bool>
                {
                    bool v;
                    if (Data->TryGetBoolField(ANSI_TO_TCHAR("isGlobalSchedule"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<bool>();
                }() : TOptional<bool>());
    }

    TSharedPtr<FJsonObject> FVerifyEventByUserIdResult::ToJson() const
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
        if (IsGlobalScheduleValue.IsSet())
        {
            JsonRootObject->SetBoolField("isGlobalSchedule", IsGlobalScheduleValue.GetValue());
        }
        return JsonRootObject;
    }
}