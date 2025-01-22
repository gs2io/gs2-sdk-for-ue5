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

#include "Exchange/Model/LogRate.h"

namespace Gs2::Exchange::Model
{
    FLogRate::FLogRate():
        BaseValue(TOptional<double>()),
        LogsValue(nullptr)
    {
    }

    FLogRate::FLogRate(
        const FLogRate& From
    ):
        BaseValue(From.BaseValue),
        LogsValue(From.LogsValue)
    {
    }

    TSharedPtr<FLogRate> FLogRate::WithBase(
        const TOptional<double> Base
    )
    {
        this->BaseValue = Base;
        return SharedThis(this);
    }

    TSharedPtr<FLogRate> FLogRate::WithLogs(
        const TSharedPtr<TArray<double>> Logs
    )
    {
        this->LogsValue = Logs;
        return SharedThis(this);
    }
    TOptional<double> FLogRate::GetBase() const
    {
        return BaseValue;
    }

    FString FLogRate::GetBaseString() const
    {
        if (!BaseValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%f"), BaseValue.GetValue());
    }
    TSharedPtr<TArray<double>> FLogRate::GetLogs() const
    {
        return LogsValue;
    }

    TSharedPtr<FLogRate> FLogRate::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FLogRate>()
            ->WithBase(Data->HasField(ANSI_TO_TCHAR("base")) ? [Data]() -> TOptional<double>
                {
                    double v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("base"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<double>();
                }() : TOptional<double>())
            ->WithLogs(Data->HasField(ANSI_TO_TCHAR("logs")) ? [Data]() -> TSharedPtr<TArray<double>>
                {
                    auto v = MakeShared<TArray<double>>();
                    if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("logs")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("logs")))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("logs")))
                        {
                            v->Add(JsonObjectValue->AsNumber());
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<double>>());
    }

    TSharedPtr<FJsonObject> FLogRate::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (BaseValue.IsSet())
        {
            JsonRootObject->SetNumberField("base", BaseValue.GetValue());
        }
        if (LogsValue != nullptr && LogsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *LogsValue)
            {
                v.Add(MakeShared<FJsonValueNumber>(JsonObjectValue));
            }
            JsonRootObject->SetArrayField("logs", v);
        }
        return JsonRootObject;
    }

    FString FLogRate::TypeName = "LogRate";
}