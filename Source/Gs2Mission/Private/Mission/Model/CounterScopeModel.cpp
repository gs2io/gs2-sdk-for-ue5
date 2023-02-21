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

#include "Mission/Model/CounterScopeModel.h"

namespace Gs2::Mission::Model
{
    FCounterScopeModel::FCounterScopeModel():
        ResetTypeValue(TOptional<FString>()),
        ResetDayOfMonthValue(TOptional<int32>()),
        ResetDayOfWeekValue(TOptional<FString>()),
        ResetHourValue(TOptional<int32>())
    {
    }

    FCounterScopeModel::FCounterScopeModel(
        const FCounterScopeModel& From
    ):
        ResetTypeValue(From.ResetTypeValue),
        ResetDayOfMonthValue(From.ResetDayOfMonthValue),
        ResetDayOfWeekValue(From.ResetDayOfWeekValue),
        ResetHourValue(From.ResetHourValue)
    {
    }

    TSharedPtr<FCounterScopeModel> FCounterScopeModel::WithResetType(
        const TOptional<FString> ResetType
    )
    {
        this->ResetTypeValue = ResetType;
        return SharedThis(this);
    }

    TSharedPtr<FCounterScopeModel> FCounterScopeModel::WithResetDayOfMonth(
        const TOptional<int32> ResetDayOfMonth
    )
    {
        this->ResetDayOfMonthValue = ResetDayOfMonth;
        return SharedThis(this);
    }

    TSharedPtr<FCounterScopeModel> FCounterScopeModel::WithResetDayOfWeek(
        const TOptional<FString> ResetDayOfWeek
    )
    {
        this->ResetDayOfWeekValue = ResetDayOfWeek;
        return SharedThis(this);
    }

    TSharedPtr<FCounterScopeModel> FCounterScopeModel::WithResetHour(
        const TOptional<int32> ResetHour
    )
    {
        this->ResetHourValue = ResetHour;
        return SharedThis(this);
    }
    TOptional<FString> FCounterScopeModel::GetResetType() const
    {
        return ResetTypeValue;
    }
    TOptional<int32> FCounterScopeModel::GetResetDayOfMonth() const
    {
        return ResetDayOfMonthValue;
    }

    FString FCounterScopeModel::GetResetDayOfMonthString() const
    {
        if (!ResetDayOfMonthValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%ld"), ResetDayOfMonthValue.GetValue());
    }
    TOptional<FString> FCounterScopeModel::GetResetDayOfWeek() const
    {
        return ResetDayOfWeekValue;
    }
    TOptional<int32> FCounterScopeModel::GetResetHour() const
    {
        return ResetHourValue;
    }

    FString FCounterScopeModel::GetResetHourString() const
    {
        if (!ResetHourValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%ld"), ResetHourValue.GetValue());
    }

    TSharedPtr<FCounterScopeModel> FCounterScopeModel::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FCounterScopeModel>()
            ->WithResetType(Data->HasField("resetType") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("resetType", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithResetDayOfMonth(Data->HasField("resetDayOfMonth") ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField("resetDayOfMonth", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithResetDayOfWeek(Data->HasField("resetDayOfWeek") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("resetDayOfWeek", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithResetHour(Data->HasField("resetHour") ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField("resetHour", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>());
    }

    TSharedPtr<FJsonObject> FCounterScopeModel::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ResetTypeValue.IsSet())
        {
            JsonRootObject->SetStringField("resetType", ResetTypeValue.GetValue());
        }
        if (ResetDayOfMonthValue.IsSet())
        {
            JsonRootObject->SetNumberField("resetDayOfMonth", ResetDayOfMonthValue.GetValue());
        }
        if (ResetDayOfWeekValue.IsSet())
        {
            JsonRootObject->SetStringField("resetDayOfWeek", ResetDayOfWeekValue.GetValue());
        }
        if (ResetHourValue.IsSet())
        {
            JsonRootObject->SetNumberField("resetHour", ResetHourValue.GetValue());
        }
        return JsonRootObject;
    }

    FString FCounterScopeModel::TypeName = "CounterScopeModel";
}