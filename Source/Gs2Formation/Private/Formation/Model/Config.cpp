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

#include "Formation/Model/Config.h"

namespace Gs2::Formation::Model
{
    FConfig::FConfig():
        KeyValue(TOptional<FString>()),
        ValueValue(TOptional<FString>())
    {
    }

    FConfig::FConfig(
        const FConfig& From
    ):
        KeyValue(From.KeyValue),
        ValueValue(From.ValueValue)
    {
    }

    TSharedPtr<FConfig> FConfig::WithKey(
        const TOptional<FString> Key
    )
    {
        this->KeyValue = Key;
        return SharedThis(this);
    }

    TSharedPtr<FConfig> FConfig::WithValue(
        const TOptional<FString> Value
    )
    {
        this->ValueValue = Value;
        return SharedThis(this);
    }
    TOptional<FString> FConfig::GetKey() const
    {
        return KeyValue;
    }
    TOptional<FString> FConfig::GetValue() const
    {
        return ValueValue;
    }

    TSharedPtr<FConfig> FConfig::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FConfig>()
            ->WithKey(Data->HasField("key") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("key", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithValue(Data->HasField("value") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("value", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FConfig::ToJson() const
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

    FString FConfig::TypeName = "Config";
}