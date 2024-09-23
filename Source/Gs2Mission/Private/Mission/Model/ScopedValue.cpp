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

#include "Mission/Model/ScopedValue.h"

namespace Gs2::Mission::Model
{
    FScopedValue::FScopedValue():
        ScopeTypeValue(TOptional<FString>()),
        ResetTypeValue(TOptional<FString>()),
        ConditionNameValue(TOptional<FString>()),
        ValueValue(TOptional<int64>()),
        NextResetAtValue(TOptional<int64>()),
        UpdatedAtValue(TOptional<int64>())
    {
    }

    FScopedValue::FScopedValue(
        const FScopedValue& From
    ):
        ScopeTypeValue(From.ScopeTypeValue),
        ResetTypeValue(From.ResetTypeValue),
        ConditionNameValue(From.ConditionNameValue),
        ValueValue(From.ValueValue),
        NextResetAtValue(From.NextResetAtValue),
        UpdatedAtValue(From.UpdatedAtValue)
    {
    }

    TSharedPtr<FScopedValue> FScopedValue::WithScopeType(
        const TOptional<FString> ScopeType
    )
    {
        this->ScopeTypeValue = ScopeType;
        return SharedThis(this);
    }

    TSharedPtr<FScopedValue> FScopedValue::WithResetType(
        const TOptional<FString> ResetType
    )
    {
        this->ResetTypeValue = ResetType;
        return SharedThis(this);
    }

    TSharedPtr<FScopedValue> FScopedValue::WithConditionName(
        const TOptional<FString> ConditionName
    )
    {
        this->ConditionNameValue = ConditionName;
        return SharedThis(this);
    }

    TSharedPtr<FScopedValue> FScopedValue::WithValue(
        const TOptional<int64> Value
    )
    {
        this->ValueValue = Value;
        return SharedThis(this);
    }

    TSharedPtr<FScopedValue> FScopedValue::WithNextResetAt(
        const TOptional<int64> NextResetAt
    )
    {
        this->NextResetAtValue = NextResetAt;
        return SharedThis(this);
    }

    TSharedPtr<FScopedValue> FScopedValue::WithUpdatedAt(
        const TOptional<int64> UpdatedAt
    )
    {
        this->UpdatedAtValue = UpdatedAt;
        return SharedThis(this);
    }
    TOptional<FString> FScopedValue::GetScopeType() const
    {
        return ScopeTypeValue;
    }
    TOptional<FString> FScopedValue::GetResetType() const
    {
        return ResetTypeValue;
    }
    TOptional<FString> FScopedValue::GetConditionName() const
    {
        return ConditionNameValue;
    }
    TOptional<int64> FScopedValue::GetValue() const
    {
        return ValueValue;
    }

    FString FScopedValue::GetValueString() const
    {
        if (!ValueValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), ValueValue.GetValue());
    }
    TOptional<int64> FScopedValue::GetNextResetAt() const
    {
        return NextResetAtValue;
    }

    FString FScopedValue::GetNextResetAtString() const
    {
        if (!NextResetAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), NextResetAtValue.GetValue());
    }
    TOptional<int64> FScopedValue::GetUpdatedAt() const
    {
        return UpdatedAtValue;
    }

    FString FScopedValue::GetUpdatedAtString() const
    {
        if (!UpdatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), UpdatedAtValue.GetValue());
    }

    TSharedPtr<FScopedValue> FScopedValue::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FScopedValue>()
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
                }() : TOptional<int64>())
            ->WithNextResetAt(Data->HasField(ANSI_TO_TCHAR("nextResetAt")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("nextResetAt"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithUpdatedAt(Data->HasField(ANSI_TO_TCHAR("updatedAt")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("updatedAt"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>());
    }

    TSharedPtr<FJsonObject> FScopedValue::ToJson() const
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
        if (ConditionNameValue.IsSet())
        {
            JsonRootObject->SetStringField("conditionName", ConditionNameValue.GetValue());
        }
        if (ValueValue.IsSet())
        {
            JsonRootObject->SetStringField("value", FString::Printf(TEXT("%lld"), ValueValue.GetValue()));
        }
        if (NextResetAtValue.IsSet())
        {
            JsonRootObject->SetStringField("nextResetAt", FString::Printf(TEXT("%lld"), NextResetAtValue.GetValue()));
        }
        if (UpdatedAtValue.IsSet())
        {
            JsonRootObject->SetStringField("updatedAt", FString::Printf(TEXT("%lld"), UpdatedAtValue.GetValue()));
        }
        return JsonRootObject;
    }

    FString FScopedValue::TypeName = "ScopedValue";
}