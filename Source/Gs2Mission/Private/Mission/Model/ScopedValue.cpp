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
        ResetTypeValue(TOptional<FString>()),
        ValueValue(TOptional<int64>()),
        NextResetAtValue(TOptional<int64>()),
        UpdatedAtValue(TOptional<int64>())
    {
    }

    FScopedValue::FScopedValue(
        const FScopedValue& From
    ):
        ResetTypeValue(From.ResetTypeValue),
        ValueValue(From.ValueValue),
        NextResetAtValue(From.NextResetAtValue),
        UpdatedAtValue(From.UpdatedAtValue)
    {
    }

    TSharedPtr<FScopedValue> FScopedValue::WithResetType(
        const TOptional<FString> ResetType
    )
    {
        this->ResetTypeValue = ResetType;
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
    TOptional<FString> FScopedValue::GetResetType() const
    {
        return ResetTypeValue;
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
            ->WithResetType(Data->HasField("resetType") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("resetType", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithValue(Data->HasField("value") ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField("value", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithNextResetAt(Data->HasField("nextResetAt") ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField("nextResetAt", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithUpdatedAt(Data->HasField("updatedAt") ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField("updatedAt", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>());
    }

    TSharedPtr<FJsonObject> FScopedValue::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ResetTypeValue.IsSet())
        {
            JsonRootObject->SetStringField("resetType", ResetTypeValue.GetValue());
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