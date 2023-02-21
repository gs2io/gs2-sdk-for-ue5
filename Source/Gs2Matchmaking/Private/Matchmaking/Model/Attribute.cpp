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

#include "Matchmaking/Model/Attribute.h"

namespace Gs2::Matchmaking::Model
{
    FAttribute::FAttribute():
        NameValue(TOptional<FString>()),
        ValueValue(TOptional<int32>())
    {
    }

    FAttribute::FAttribute(
        const FAttribute& From
    ):
        NameValue(From.NameValue),
        ValueValue(From.ValueValue)
    {
    }

    TSharedPtr<FAttribute> FAttribute::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FAttribute> FAttribute::WithValue(
        const TOptional<int32> Value
    )
    {
        this->ValueValue = Value;
        return SharedThis(this);
    }
    TOptional<FString> FAttribute::GetName() const
    {
        return NameValue;
    }
    TOptional<int32> FAttribute::GetValue() const
    {
        return ValueValue;
    }

    FString FAttribute::GetValueString() const
    {
        if (!ValueValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%ld"), ValueValue.GetValue());
    }

    TSharedPtr<FAttribute> FAttribute::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FAttribute>()
            ->WithName(Data->HasField("name") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("name", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithValue(Data->HasField("value") ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField("value", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>());
    }

    TSharedPtr<FJsonObject> FAttribute::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (NameValue.IsSet())
        {
            JsonRootObject->SetStringField("name", NameValue.GetValue());
        }
        if (ValueValue.IsSet())
        {
            JsonRootObject->SetNumberField("value", ValueValue.GetValue());
        }
        return JsonRootObject;
    }

    FString FAttribute::TypeName = "Attribute";
}