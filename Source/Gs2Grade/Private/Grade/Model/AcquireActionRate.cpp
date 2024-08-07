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

#include "Grade/Model/AcquireActionRate.h"

namespace Gs2::Grade::Model
{
    FAcquireActionRate::FAcquireActionRate():
        NameValue(TOptional<FString>()),
        ModeValue(TOptional<FString>()),
        RatesValue(nullptr),
        BigRatesValue(nullptr)
    {
    }

    FAcquireActionRate::FAcquireActionRate(
        const FAcquireActionRate& From
    ):
        NameValue(From.NameValue),
        ModeValue(From.ModeValue),
        RatesValue(From.RatesValue),
        BigRatesValue(From.BigRatesValue)
    {
    }

    TSharedPtr<FAcquireActionRate> FAcquireActionRate::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FAcquireActionRate> FAcquireActionRate::WithMode(
        const TOptional<FString> Mode
    )
    {
        this->ModeValue = Mode;
        return SharedThis(this);
    }

    TSharedPtr<FAcquireActionRate> FAcquireActionRate::WithRates(
        const TSharedPtr<TArray<double>> Rates
    )
    {
        this->RatesValue = Rates;
        return SharedThis(this);
    }

    TSharedPtr<FAcquireActionRate> FAcquireActionRate::WithBigRates(
        const TSharedPtr<TArray<FString>> BigRates
    )
    {
        this->BigRatesValue = BigRates;
        return SharedThis(this);
    }
    TOptional<FString> FAcquireActionRate::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FAcquireActionRate::GetMode() const
    {
        return ModeValue;
    }
    TSharedPtr<TArray<double>> FAcquireActionRate::GetRates() const
    {
        return RatesValue;
    }
    TSharedPtr<TArray<FString>> FAcquireActionRate::GetBigRates() const
    {
        return BigRatesValue;
    }

    TSharedPtr<FAcquireActionRate> FAcquireActionRate::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FAcquireActionRate>()
            ->WithName(Data->HasField(ANSI_TO_TCHAR("name")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("name"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithMode(Data->HasField(ANSI_TO_TCHAR("mode")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("mode"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithRates(Data->HasField(ANSI_TO_TCHAR("rates")) ? [Data]() -> TSharedPtr<TArray<double>>
                {
                    auto v = MakeShared<TArray<double>>();
                    if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("rates")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("rates")))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("rates")))
                        {
                            v->Add(JsonObjectValue->AsNumber());
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<double>>())
            ->WithBigRates(Data->HasField(ANSI_TO_TCHAR("bigRates")) ? [Data]() -> TSharedPtr<TArray<FString>>
                {
                    auto v = MakeShared<TArray<FString>>();
                    if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("bigRates")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("bigRates")))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("bigRates")))
                        {
                            v->Add(JsonObjectValue->AsString());
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<FString>>());
    }

    TSharedPtr<FJsonObject> FAcquireActionRate::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (NameValue.IsSet())
        {
            JsonRootObject->SetStringField("name", NameValue.GetValue());
        }
        if (ModeValue.IsSet())
        {
            JsonRootObject->SetStringField("mode", ModeValue.GetValue());
        }
        if (RatesValue != nullptr && RatesValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *RatesValue)
            {
                v.Add(MakeShared<FJsonValueNumber>(JsonObjectValue));
            }
            JsonRootObject->SetArrayField("rates", v);
        }
        if (BigRatesValue != nullptr && BigRatesValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *BigRatesValue)
            {
                v.Add(MakeShared<FJsonValueString>(JsonObjectValue));
            }
            JsonRootObject->SetArrayField("bigRates", v);
        }
        return JsonRootObject;
    }

    FString FAcquireActionRate::TypeName = "AcquireActionRate";
}