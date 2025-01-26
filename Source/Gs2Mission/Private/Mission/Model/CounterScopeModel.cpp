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
        ScopeTypeValue(TOptional<FString>()),
        ResetTypeValue(TOptional<FString>()),
        ResetDayOfMonthValue(TOptional<int32>()),
        ResetDayOfWeekValue(TOptional<FString>()),
        ResetHourValue(TOptional<int32>()),
        ConditionNameValue(TOptional<FString>()),
        ConditionValue(nullptr),
        AnchorTimestampValue(TOptional<int64>()),
        DaysValue(TOptional<int32>())
    {
    }

    FCounterScopeModel::FCounterScopeModel(
        const FCounterScopeModel& From
    ):
        ScopeTypeValue(From.ScopeTypeValue),
        ResetTypeValue(From.ResetTypeValue),
        ResetDayOfMonthValue(From.ResetDayOfMonthValue),
        ResetDayOfWeekValue(From.ResetDayOfWeekValue),
        ResetHourValue(From.ResetHourValue),
        ConditionNameValue(From.ConditionNameValue),
        ConditionValue(From.ConditionValue),
        AnchorTimestampValue(From.AnchorTimestampValue),
        DaysValue(From.DaysValue)
    {
    }

    TSharedPtr<FCounterScopeModel> FCounterScopeModel::WithScopeType(
        const TOptional<FString> ScopeType
    )
    {
        this->ScopeTypeValue = ScopeType;
        return SharedThis(this);
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

    TSharedPtr<FCounterScopeModel> FCounterScopeModel::WithConditionName(
        const TOptional<FString> ConditionName
    )
    {
        this->ConditionNameValue = ConditionName;
        return SharedThis(this);
    }

    TSharedPtr<FCounterScopeModel> FCounterScopeModel::WithCondition(
        const TSharedPtr<FVerifyAction> Condition
    )
    {
        this->ConditionValue = Condition;
        return SharedThis(this);
    }

    TSharedPtr<FCounterScopeModel> FCounterScopeModel::WithAnchorTimestamp(
        const TOptional<int64> AnchorTimestamp
    )
    {
        this->AnchorTimestampValue = AnchorTimestamp;
        return SharedThis(this);
    }

    TSharedPtr<FCounterScopeModel> FCounterScopeModel::WithDays(
        const TOptional<int32> Days
    )
    {
        this->DaysValue = Days;
        return SharedThis(this);
    }
    TOptional<FString> FCounterScopeModel::GetScopeType() const
    {
        return ScopeTypeValue;
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
        return FString::Printf(TEXT("%d"), ResetDayOfMonthValue.GetValue());
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
        return FString::Printf(TEXT("%d"), ResetHourValue.GetValue());
    }
    TOptional<FString> FCounterScopeModel::GetConditionName() const
    {
        return ConditionNameValue;
    }
    TSharedPtr<FVerifyAction> FCounterScopeModel::GetCondition() const
    {
        return ConditionValue;
    }
    TOptional<int64> FCounterScopeModel::GetAnchorTimestamp() const
    {
        return AnchorTimestampValue;
    }

    FString FCounterScopeModel::GetAnchorTimestampString() const
    {
        if (!AnchorTimestampValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), AnchorTimestampValue.GetValue());
    }
    TOptional<int32> FCounterScopeModel::GetDays() const
    {
        return DaysValue;
    }

    FString FCounterScopeModel::GetDaysString() const
    {
        if (!DaysValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), DaysValue.GetValue());
    }

    TSharedPtr<FCounterScopeModel> FCounterScopeModel::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FCounterScopeModel>()
            ->WithScopeType(Data->HasField(ANSI_TO_TCHAR("scopeType")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("scopeType"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithResetType(Data->HasField(ANSI_TO_TCHAR("resetType")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("resetType"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithResetDayOfMonth(Data->HasField(ANSI_TO_TCHAR("resetDayOfMonth")) ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("resetDayOfMonth"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithResetDayOfWeek(Data->HasField(ANSI_TO_TCHAR("resetDayOfWeek")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("resetDayOfWeek"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithResetHour(Data->HasField(ANSI_TO_TCHAR("resetHour")) ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("resetHour"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithConditionName(Data->HasField(ANSI_TO_TCHAR("conditionName")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("conditionName"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithCondition(Data->HasField(ANSI_TO_TCHAR("condition")) ? [Data]() -> Model::FVerifyActionPtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("condition")))
                    {
                        return nullptr;
                    }
                    return Model::FVerifyAction::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("condition")));
                 }() : nullptr)
            ->WithAnchorTimestamp(Data->HasField(ANSI_TO_TCHAR("anchorTimestamp")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("anchorTimestamp"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithDays(Data->HasField(ANSI_TO_TCHAR("days")) ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("days"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>());
    }

    TSharedPtr<FJsonObject> FCounterScopeModel::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ScopeTypeValue.IsSet())
        {
            JsonRootObject->SetStringField("scopeType", ScopeTypeValue.GetValue());
        }
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
        if (ConditionNameValue.IsSet())
        {
            JsonRootObject->SetStringField("conditionName", ConditionNameValue.GetValue());
        }
        if (ConditionValue != nullptr && ConditionValue.IsValid())
        {
            JsonRootObject->SetObjectField("condition", ConditionValue->ToJson());
        }
        if (AnchorTimestampValue.IsSet())
        {
            JsonRootObject->SetStringField("anchorTimestamp", FString::Printf(TEXT("%lld"), AnchorTimestampValue.GetValue()));
        }
        if (DaysValue.IsSet())
        {
            JsonRootObject->SetNumberField("days", DaysValue.GetValue());
        }
        return JsonRootObject;
    }

    FString FCounterScopeModel::TypeName = "CounterScopeModel";
}