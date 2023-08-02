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

#include "Experience/Model/AcquireActionRate.h"

namespace Gs2::Experience::Model
{
    FAcquireActionRate::FAcquireActionRate():
        NameValue(TOptional<FString>()),
        RatesValue(nullptr)
    {
    }

    FAcquireActionRate::FAcquireActionRate(
        const FAcquireActionRate& From
    ):
        NameValue(From.NameValue),
        RatesValue(From.RatesValue)
    {
    }

    TSharedPtr<FAcquireActionRate> FAcquireActionRate::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FAcquireActionRate> FAcquireActionRate::WithRates(
        const TSharedPtr<TArray<double>> Rates
    )
    {
        this->RatesValue = Rates;
        return SharedThis(this);
    }
    TOptional<FString> FAcquireActionRate::GetName() const
    {
        return NameValue;
    }
    TSharedPtr<TArray<double>> FAcquireActionRate::GetRates() const
    {
        return RatesValue;
    }

    TSharedPtr<FAcquireActionRate> FAcquireActionRate::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FAcquireActionRate>()
            ->WithName(Data->HasField("name") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("name", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithRates(Data->HasField("rates") ? [Data]() -> TSharedPtr<TArray<double>>
                {
                    auto v = MakeShared<TArray<double>>();
                    if (!Data->HasTypedField<EJson::Null>("rates") && Data->HasTypedField<EJson::Array>("rates"))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField("rates"))
                        {
                            v->Add(JsonObjectValue->AsNumber());
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<double>>());
    }

    TSharedPtr<FJsonObject> FAcquireActionRate::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (NameValue.IsSet())
        {
            JsonRootObject->SetStringField("name", NameValue.GetValue());
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
        return JsonRootObject;
    }

    FString FAcquireActionRate::TypeName = "AcquireActionRate";
}