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

#include "Enchant/Model/BalanceParameterValue.h"

namespace Gs2::Enchant::Model
{
    FBalanceParameterValue::FBalanceParameterValue():
        NameValue(TOptional<FString>()),
        ValueValue(TOptional<int64>())
    {
    }

    FBalanceParameterValue::FBalanceParameterValue(
        const FBalanceParameterValue& From
    ):
        NameValue(From.NameValue),
        ValueValue(From.ValueValue)
    {
    }

    TSharedPtr<FBalanceParameterValue> FBalanceParameterValue::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FBalanceParameterValue> FBalanceParameterValue::WithValue(
        const TOptional<int64> Value
    )
    {
        this->ValueValue = Value;
        return SharedThis(this);
    }
    TOptional<FString> FBalanceParameterValue::GetName() const
    {
        return NameValue;
    }
    TOptional<int64> FBalanceParameterValue::GetValue() const
    {
        return ValueValue;
    }

    FString FBalanceParameterValue::GetValueString() const
    {
        if (!ValueValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), ValueValue.GetValue());
    }

    TSharedPtr<FBalanceParameterValue> FBalanceParameterValue::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FBalanceParameterValue>()
            ->WithName(Data->HasField("name") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("name", v))
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
                }() : TOptional<int64>());
    }

    TSharedPtr<FJsonObject> FBalanceParameterValue::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (NameValue.IsSet())
        {
            JsonRootObject->SetStringField("name", NameValue.GetValue());
        }
        if (ValueValue.IsSet())
        {
            JsonRootObject->SetStringField("value", FString::Printf(TEXT("%lld"), ValueValue.GetValue()));
        }
        return JsonRootObject;
    }

    FString FBalanceParameterValue::TypeName = "BalanceParameterValue";
}