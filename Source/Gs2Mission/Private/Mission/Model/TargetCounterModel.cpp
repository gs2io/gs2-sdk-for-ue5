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

#include "Mission/Model/TargetCounterModel.h"

namespace Gs2::Mission::Model
{
    FTargetCounterModel::FTargetCounterModel():
        CounterNameValue(TOptional<FString>()),
        ScopeTypeValue(TOptional<FString>()),
        ResetTypeValue(TOptional<FString>()),
        ConditionNameValue(TOptional<FString>()),
        ValueValue(TOptional<int64>())
    {
    }

    FTargetCounterModel::FTargetCounterModel(
        const FTargetCounterModel& From
    ):
        CounterNameValue(From.CounterNameValue),
        ScopeTypeValue(From.ScopeTypeValue),
        ResetTypeValue(From.ResetTypeValue),
        ConditionNameValue(From.ConditionNameValue),
        ValueValue(From.ValueValue)
    {
    }

    TSharedPtr<FTargetCounterModel> FTargetCounterModel::WithCounterName(
        const TOptional<FString> CounterName
    )
    {
        this->CounterNameValue = CounterName;
        return SharedThis(this);
    }

    TSharedPtr<FTargetCounterModel> FTargetCounterModel::WithScopeType(
        const TOptional<FString> ScopeType
    )
    {
        this->ScopeTypeValue = ScopeType;
        return SharedThis(this);
    }

    TSharedPtr<FTargetCounterModel> FTargetCounterModel::WithResetType(
        const TOptional<FString> ResetType
    )
    {
        this->ResetTypeValue = ResetType;
        return SharedThis(this);
    }

    TSharedPtr<FTargetCounterModel> FTargetCounterModel::WithConditionName(
        const TOptional<FString> ConditionName
    )
    {
        this->ConditionNameValue = ConditionName;
        return SharedThis(this);
    }

    TSharedPtr<FTargetCounterModel> FTargetCounterModel::WithValue(
        const TOptional<int64> Value
    )
    {
        this->ValueValue = Value;
        return SharedThis(this);
    }
    TOptional<FString> FTargetCounterModel::GetCounterName() const
    {
        return CounterNameValue;
    }
    TOptional<FString> FTargetCounterModel::GetScopeType() const
    {
        return ScopeTypeValue;
    }
    TOptional<FString> FTargetCounterModel::GetResetType() const
    {
        return ResetTypeValue;
    }
    TOptional<FString> FTargetCounterModel::GetConditionName() const
    {
        return ConditionNameValue;
    }
    TOptional<int64> FTargetCounterModel::GetValue() const
    {
        return ValueValue;
    }

    FString FTargetCounterModel::GetValueString() const
    {
        if (!ValueValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), ValueValue.GetValue());
    }

    TSharedPtr<FTargetCounterModel> FTargetCounterModel::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FTargetCounterModel>()
            ->WithCounterName(Data->HasField(ANSI_TO_TCHAR("counterName")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("counterName"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
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
            ->WithConditionName(Data->HasField(ANSI_TO_TCHAR("conditionName")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("conditionName"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithValue(Data->HasField(ANSI_TO_TCHAR("value")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("value"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>());
    }

    TSharedPtr<FJsonObject> FTargetCounterModel::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (CounterNameValue.IsSet())
        {
            JsonRootObject->SetStringField("counterName", CounterNameValue.GetValue());
        }
        if (ScopeTypeValue.IsSet())
        {
            JsonRootObject->SetStringField("scopeType", ScopeTypeValue.GetValue());
        }
        if (ResetTypeValue.IsSet())
        {
            JsonRootObject->SetStringField("resetType", ResetTypeValue.GetValue());
        }
        if (ConditionNameValue.IsSet())
        {
            JsonRootObject->SetStringField("conditionName", ConditionNameValue.GetValue());
        }
        if (ValueValue.IsSet())
        {
            JsonRootObject->SetStringField("value", FString::Printf(TEXT("%lld"), ValueValue.GetValue()));
        }
        return JsonRootObject;
    }

    FString FTargetCounterModel::TypeName = "TargetCounterModel";
}