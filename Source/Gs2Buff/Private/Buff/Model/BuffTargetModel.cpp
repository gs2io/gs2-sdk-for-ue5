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

#include "Buff/Model/BuffTargetModel.h"

namespace Gs2::Buff::Model
{
    FBuffTargetModel::FBuffTargetModel():
        TargetModelNameValue(TOptional<FString>()),
        TargetFieldNameValue(TOptional<FString>()),
        ConditionGrnsValue(nullptr),
        RateValue(TOptional<float>())
    {
    }

    FBuffTargetModel::FBuffTargetModel(
        const FBuffTargetModel& From
    ):
        TargetModelNameValue(From.TargetModelNameValue),
        TargetFieldNameValue(From.TargetFieldNameValue),
        ConditionGrnsValue(From.ConditionGrnsValue),
        RateValue(From.RateValue)
    {
    }

    TSharedPtr<FBuffTargetModel> FBuffTargetModel::WithTargetModelName(
        const TOptional<FString> TargetModelName
    )
    {
        this->TargetModelNameValue = TargetModelName;
        return SharedThis(this);
    }

    TSharedPtr<FBuffTargetModel> FBuffTargetModel::WithTargetFieldName(
        const TOptional<FString> TargetFieldName
    )
    {
        this->TargetFieldNameValue = TargetFieldName;
        return SharedThis(this);
    }

    TSharedPtr<FBuffTargetModel> FBuffTargetModel::WithConditionGrns(
        const TSharedPtr<TArray<TSharedPtr<Model::FBuffTargetGrn>>> ConditionGrns
    )
    {
        this->ConditionGrnsValue = ConditionGrns;
        return SharedThis(this);
    }

    TSharedPtr<FBuffTargetModel> FBuffTargetModel::WithRate(
        const TOptional<float> Rate
    )
    {
        this->RateValue = Rate;
        return SharedThis(this);
    }
    TOptional<FString> FBuffTargetModel::GetTargetModelName() const
    {
        return TargetModelNameValue;
    }
    TOptional<FString> FBuffTargetModel::GetTargetFieldName() const
    {
        return TargetFieldNameValue;
    }
    TSharedPtr<TArray<TSharedPtr<Model::FBuffTargetGrn>>> FBuffTargetModel::GetConditionGrns() const
    {
        return ConditionGrnsValue;
    }
    TOptional<float> FBuffTargetModel::GetRate() const
    {
        return RateValue;
    }

    FString FBuffTargetModel::GetRateString() const
    {
        if (!RateValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%f"), RateValue.GetValue());
    }

    TSharedPtr<FBuffTargetModel> FBuffTargetModel::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FBuffTargetModel>()
            ->WithTargetModelName(Data->HasField(ANSI_TO_TCHAR("targetModelName")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("targetModelName"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithTargetFieldName(Data->HasField(ANSI_TO_TCHAR("targetFieldName")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("targetFieldName"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithConditionGrns(Data->HasField(ANSI_TO_TCHAR("conditionGrns")) ? [Data]() -> TSharedPtr<TArray<Model::FBuffTargetGrnPtr>>
                {
                    auto v = MakeShared<TArray<Model::FBuffTargetGrnPtr>>();
                    if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("conditionGrns")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("conditionGrns")))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("conditionGrns")))
                        {
                            v->Add(Model::FBuffTargetGrn::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<Model::FBuffTargetGrnPtr>>())
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

    TSharedPtr<FJsonObject> FBuffTargetModel::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (TargetModelNameValue.IsSet())
        {
            JsonRootObject->SetStringField("targetModelName", TargetModelNameValue.GetValue());
        }
        if (TargetFieldNameValue.IsSet())
        {
            JsonRootObject->SetStringField("targetFieldName", TargetFieldNameValue.GetValue());
        }
        if (ConditionGrnsValue != nullptr && ConditionGrnsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *ConditionGrnsValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("conditionGrns", v);
        }
        if (RateValue.IsSet())
        {
            JsonRootObject->SetNumberField("rate", RateValue.GetValue());
        }
        return JsonRootObject;
    }

    FString FBuffTargetModel::TypeName = "BuffTargetModel";
}