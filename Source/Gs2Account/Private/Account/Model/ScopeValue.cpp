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

#include "Account/Model/ScopeValue.h"

namespace Gs2::Account::Model
{
    FScopeValue::FScopeValue():
        KeyValue(TOptional<FString>()),
        ValueValue(TOptional<FString>())
    {
    }

    FScopeValue::FScopeValue(
        const FScopeValue& From
    ):
        KeyValue(From.KeyValue),
        ValueValue(From.ValueValue)
    {
    }

    TSharedPtr<FScopeValue> FScopeValue::WithKey(
        const TOptional<FString> Key
    )
    {
        this->KeyValue = Key;
        return SharedThis(this);
    }

    TSharedPtr<FScopeValue> FScopeValue::WithValue(
        const TOptional<FString> Value
    )
    {
        this->ValueValue = Value;
        return SharedThis(this);
    }
    TOptional<FString> FScopeValue::GetKey() const
    {
        return KeyValue;
    }
    TOptional<FString> FScopeValue::GetValue() const
    {
        return ValueValue;
    }

    TSharedPtr<FScopeValue> FScopeValue::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FScopeValue>()
            ->WithKey(Data->HasField(ANSI_TO_TCHAR("key")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("key"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithValue(Data->HasField(ANSI_TO_TCHAR("value")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("value"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FScopeValue::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (KeyValue.IsSet())
        {
            JsonRootObject->SetStringField("key", KeyValue.GetValue());
        }
        if (ValueValue.IsSet())
        {
            JsonRootObject->SetStringField("value", ValueValue.GetValue());
        }
        return JsonRootObject;
    }

    FString FScopeValue::TypeName = "ScopeValue";
}