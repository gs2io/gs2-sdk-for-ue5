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

#include "Formation/Model/AcquireActionConfig.h"

namespace Gs2::Formation::Model
{
    FAcquireActionConfig::FAcquireActionConfig():
        NameValue(TOptional<FString>()),
        ConfigValue(nullptr)
    {
    }

    FAcquireActionConfig::FAcquireActionConfig(
        const FAcquireActionConfig& From
    ):
        NameValue(From.NameValue),
        ConfigValue(From.ConfigValue)
    {
    }

    TSharedPtr<FAcquireActionConfig> FAcquireActionConfig::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FAcquireActionConfig> FAcquireActionConfig::WithConfig(
        const TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> Config
    )
    {
        this->ConfigValue = Config;
        return SharedThis(this);
    }
    TOptional<FString> FAcquireActionConfig::GetName() const
    {
        return NameValue;
    }
    TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> FAcquireActionConfig::GetConfig() const
    {
        return ConfigValue;
    }

    TSharedPtr<FAcquireActionConfig> FAcquireActionConfig::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FAcquireActionConfig>()
            ->WithName(Data->HasField(ANSI_TO_TCHAR("name")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("name"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithConfig(Data->HasField(ANSI_TO_TCHAR("config")) ? [Data]() -> TSharedPtr<TArray<Model::FConfigPtr>>
                {
                    auto v = MakeShared<TArray<Model::FConfigPtr>>();
                    if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("config")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("config")))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("config")))
                        {
                            v->Add(Model::FConfig::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<Model::FConfigPtr>>());
    }

    TSharedPtr<FJsonObject> FAcquireActionConfig::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (NameValue.IsSet())
        {
            JsonRootObject->SetStringField("name", NameValue.GetValue());
        }
        if (ConfigValue != nullptr && ConfigValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *ConfigValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("config", v);
        }
        return JsonRootObject;
    }

    FString FAcquireActionConfig::TypeName = "AcquireActionConfig";
}