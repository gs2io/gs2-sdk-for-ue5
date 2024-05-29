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

#include "Buff/Model/OverrideBuffRate.h"

namespace Gs2::Buff::Model
{
    FOverrideBuffRate::FOverrideBuffRate():
        NameValue(TOptional<FString>()),
        RateValue(TOptional<float>())
    {
    }

    FOverrideBuffRate::FOverrideBuffRate(
        const FOverrideBuffRate& From
    ):
        NameValue(From.NameValue),
        RateValue(From.RateValue)
    {
    }

    TSharedPtr<FOverrideBuffRate> FOverrideBuffRate::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FOverrideBuffRate> FOverrideBuffRate::WithRate(
        const TOptional<float> Rate
    )
    {
        this->RateValue = Rate;
        return SharedThis(this);
    }
    TOptional<FString> FOverrideBuffRate::GetName() const
    {
        return NameValue;
    }
    TOptional<float> FOverrideBuffRate::GetRate() const
    {
        return RateValue;
    }

    FString FOverrideBuffRate::GetRateString() const
    {
        if (!RateValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%f"), RateValue.GetValue());
    }

    TSharedPtr<FOverrideBuffRate> FOverrideBuffRate::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FOverrideBuffRate>()
            ->WithName(Data->HasField(ANSI_TO_TCHAR("name")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("name"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithRate(Data->HasField(ANSI_TO_TCHAR("rate")) ? [Data]() -> TOptional<float>
                {
                    float v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("rate"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<float>();
                }() : TOptional<float>());
    }

    TSharedPtr<FJsonObject> FOverrideBuffRate::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (NameValue.IsSet())
        {
            JsonRootObject->SetStringField("name", NameValue.GetValue());
        }
        if (RateValue.IsSet())
        {
            JsonRootObject->SetNumberField("rate", RateValue.GetValue());
        }
        return JsonRootObject;
    }

    FString FOverrideBuffRate::TypeName = "OverrideBuffRate";
}