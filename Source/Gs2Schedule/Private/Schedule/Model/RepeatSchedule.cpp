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

#include "Schedule/Model/RepeatSchedule.h"

namespace Gs2::Schedule::Model
{
    FRepeatSchedule::FRepeatSchedule():
        RepeatCountValue(TOptional<int32>()),
        CurrentRepeatStartAtValue(TOptional<int64>()),
        CurrentRepeatEndAtValue(TOptional<int64>()),
        LastRepeatEndAtValue(TOptional<int64>()),
        NextRepeatStartAtValue(TOptional<int64>())
    {
    }

    FRepeatSchedule::FRepeatSchedule(
        const FRepeatSchedule& From
    ):
        RepeatCountValue(From.RepeatCountValue),
        CurrentRepeatStartAtValue(From.CurrentRepeatStartAtValue),
        CurrentRepeatEndAtValue(From.CurrentRepeatEndAtValue),
        LastRepeatEndAtValue(From.LastRepeatEndAtValue),
        NextRepeatStartAtValue(From.NextRepeatStartAtValue)
    {
    }

    TSharedPtr<FRepeatSchedule> FRepeatSchedule::WithRepeatCount(
        const TOptional<int32> RepeatCount
    )
    {
        this->RepeatCountValue = RepeatCount;
        return SharedThis(this);
    }

    TSharedPtr<FRepeatSchedule> FRepeatSchedule::WithCurrentRepeatStartAt(
        const TOptional<int64> CurrentRepeatStartAt
    )
    {
        this->CurrentRepeatStartAtValue = CurrentRepeatStartAt;
        return SharedThis(this);
    }

    TSharedPtr<FRepeatSchedule> FRepeatSchedule::WithCurrentRepeatEndAt(
        const TOptional<int64> CurrentRepeatEndAt
    )
    {
        this->CurrentRepeatEndAtValue = CurrentRepeatEndAt;
        return SharedThis(this);
    }

    TSharedPtr<FRepeatSchedule> FRepeatSchedule::WithLastRepeatEndAt(
        const TOptional<int64> LastRepeatEndAt
    )
    {
        this->LastRepeatEndAtValue = LastRepeatEndAt;
        return SharedThis(this);
    }

    TSharedPtr<FRepeatSchedule> FRepeatSchedule::WithNextRepeatStartAt(
        const TOptional<int64> NextRepeatStartAt
    )
    {
        this->NextRepeatStartAtValue = NextRepeatStartAt;
        return SharedThis(this);
    }
    TOptional<int32> FRepeatSchedule::GetRepeatCount() const
    {
        return RepeatCountValue;
    }

    FString FRepeatSchedule::GetRepeatCountString() const
    {
        if (!RepeatCountValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), RepeatCountValue.GetValue());
    }
    TOptional<int64> FRepeatSchedule::GetCurrentRepeatStartAt() const
    {
        return CurrentRepeatStartAtValue;
    }

    FString FRepeatSchedule::GetCurrentRepeatStartAtString() const
    {
        if (!CurrentRepeatStartAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CurrentRepeatStartAtValue.GetValue());
    }
    TOptional<int64> FRepeatSchedule::GetCurrentRepeatEndAt() const
    {
        return CurrentRepeatEndAtValue;
    }

    FString FRepeatSchedule::GetCurrentRepeatEndAtString() const
    {
        if (!CurrentRepeatEndAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CurrentRepeatEndAtValue.GetValue());
    }
    TOptional<int64> FRepeatSchedule::GetLastRepeatEndAt() const
    {
        return LastRepeatEndAtValue;
    }

    FString FRepeatSchedule::GetLastRepeatEndAtString() const
    {
        if (!LastRepeatEndAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), LastRepeatEndAtValue.GetValue());
    }
    TOptional<int64> FRepeatSchedule::GetNextRepeatStartAt() const
    {
        return NextRepeatStartAtValue;
    }

    FString FRepeatSchedule::GetNextRepeatStartAtString() const
    {
        if (!NextRepeatStartAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), NextRepeatStartAtValue.GetValue());
    }

    TSharedPtr<FRepeatSchedule> FRepeatSchedule::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FRepeatSchedule>()
            ->WithRepeatCount(Data->HasField("repeatCount") ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField("repeatCount", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithCurrentRepeatStartAt(Data->HasField("currentRepeatStartAt") ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField("currentRepeatStartAt", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithCurrentRepeatEndAt(Data->HasField("currentRepeatEndAt") ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField("currentRepeatEndAt", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithLastRepeatEndAt(Data->HasField("lastRepeatEndAt") ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField("lastRepeatEndAt", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithNextRepeatStartAt(Data->HasField("nextRepeatStartAt") ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField("nextRepeatStartAt", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>());
    }

    TSharedPtr<FJsonObject> FRepeatSchedule::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (RepeatCountValue.IsSet())
        {
            JsonRootObject->SetNumberField("repeatCount", RepeatCountValue.GetValue());
        }
        if (CurrentRepeatStartAtValue.IsSet())
        {
            JsonRootObject->SetStringField("currentRepeatStartAt", FString::Printf(TEXT("%lld"), CurrentRepeatStartAtValue.GetValue()));
        }
        if (CurrentRepeatEndAtValue.IsSet())
        {
            JsonRootObject->SetStringField("currentRepeatEndAt", FString::Printf(TEXT("%lld"), CurrentRepeatEndAtValue.GetValue()));
        }
        if (LastRepeatEndAtValue.IsSet())
        {
            JsonRootObject->SetStringField("lastRepeatEndAt", FString::Printf(TEXT("%lld"), LastRepeatEndAtValue.GetValue()));
        }
        if (NextRepeatStartAtValue.IsSet())
        {
            JsonRootObject->SetStringField("nextRepeatStartAt", FString::Printf(TEXT("%lld"), NextRepeatStartAtValue.GetValue()));
        }
        return JsonRootObject;
    }

    FString FRepeatSchedule::TypeName = "RepeatSchedule";
}