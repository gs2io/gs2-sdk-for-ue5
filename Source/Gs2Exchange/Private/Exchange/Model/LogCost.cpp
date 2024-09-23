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

#include "Exchange/Model/LogCost.h"

namespace Gs2::Exchange::Model
{
    FLogCost::FLogCost():
        BaseValue(TOptional<double>()),
        AddsValue(nullptr),
        SubsValue(nullptr)
    {
    }

    FLogCost::FLogCost(
        const FLogCost& From
    ):
        BaseValue(From.BaseValue),
        AddsValue(From.AddsValue),
        SubsValue(From.SubsValue)
    {
    }

    TSharedPtr<FLogCost> FLogCost::WithBase(
        const TOptional<double> Base
    )
    {
        this->BaseValue = Base;
        return SharedThis(this);
    }

    TSharedPtr<FLogCost> FLogCost::WithAdds(
        const TSharedPtr<TArray<double>> Adds
    )
    {
        this->AddsValue = Adds;
        return SharedThis(this);
    }

    TSharedPtr<FLogCost> FLogCost::WithSubs(
        const TSharedPtr<TArray<double>> Subs
    )
    {
        this->SubsValue = Subs;
        return SharedThis(this);
    }
    TOptional<double> FLogCost::GetBase() const
    {
        return BaseValue;
    }

    FString FLogCost::GetBaseString() const
    {
        if (!BaseValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%f"), BaseValue.GetValue());
    }
    TSharedPtr<TArray<double>> FLogCost::GetAdds() const
    {
        return AddsValue;
    }
    TSharedPtr<TArray<double>> FLogCost::GetSubs() const
    {
        return SubsValue;
    }

    TSharedPtr<FLogCost> FLogCost::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FLogCost>()
            ->WithBase(Data->HasField(ANSI_TO_TCHAR("base")) ? [Data]() -> TOptional<double>
                {
                    double v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("base"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<double>();
                }() : TOptional<double>())
            ->WithAdds(Data->HasField(ANSI_TO_TCHAR("adds")) ? [Data]() -> TSharedPtr<TArray<double>>
                {
                    auto v = MakeShared<TArray<double>>();
                    if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("adds")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("adds")))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("adds")))
                        {
                            v->Add(JsonObjectValue->AsNumber());
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<double>>())
            ->WithSubs(Data->HasField(ANSI_TO_TCHAR("subs")) ? [Data]() -> TSharedPtr<TArray<double>>
                {
                    auto v = MakeShared<TArray<double>>();
                    if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("subs")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("subs")))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("subs")))
                        {
                            v->Add(JsonObjectValue->AsNumber());
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<double>>());
    }

    TSharedPtr<FJsonObject> FLogCost::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (BaseValue.IsSet())
        {
            JsonRootObject->SetNumberField("base", BaseValue.GetValue());
        }
        if (AddsValue != nullptr && AddsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *AddsValue)
            {
                v.Add(MakeShared<FJsonValueNumber>(JsonObjectValue));
            }
            JsonRootObject->SetArrayField("adds", v);
        }
        if (SubsValue != nullptr && SubsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *SubsValue)
            {
                v.Add(MakeShared<FJsonValueNumber>(JsonObjectValue));
            }
            JsonRootObject->SetArrayField("subs", v);
        }
        return JsonRootObject;
    }

    FString FLogCost::TypeName = "LogCost";
}