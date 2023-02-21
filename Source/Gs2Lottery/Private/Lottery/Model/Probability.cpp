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

#include "Lottery/Model/Probability.h"

namespace Gs2::Lottery::Model
{
    FProbability::FProbability():
        PrizeValue(nullptr),
        RateValue(TOptional<float>())
    {
    }

    FProbability::FProbability(
        const FProbability& From
    ):
        PrizeValue(From.PrizeValue),
        RateValue(From.RateValue)
    {
    }

    TSharedPtr<FProbability> FProbability::WithPrize(
        const TSharedPtr<FDrawnPrize> Prize
    )
    {
        this->PrizeValue = Prize;
        return SharedThis(this);
    }

    TSharedPtr<FProbability> FProbability::WithRate(
        const TOptional<float> Rate
    )
    {
        this->RateValue = Rate;
        return SharedThis(this);
    }
    TSharedPtr<FDrawnPrize> FProbability::GetPrize() const
    {
        return PrizeValue;
    }
    TOptional<float> FProbability::GetRate() const
    {
        return RateValue;
    }

    FString FProbability::GetRateString() const
    {
        if (!RateValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%f"), RateValue.GetValue());
    }

    TSharedPtr<FProbability> FProbability::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FProbability>()
            ->WithPrize(Data->HasField("prize") ? [Data]() -> Model::FDrawnPrizePtr
                {
                    if (Data->HasTypedField<EJson::Null>("prize"))
                    {
                        return nullptr;
                    }
                    return Model::FDrawnPrize::FromJson(Data->GetObjectField("prize"));
                 }() : nullptr)
            ->WithRate(Data->HasField("rate") ? [Data]() -> TOptional<float>
                {
                    float v;
                    if (Data->TryGetNumberField("rate", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<float>();
                }() : TOptional<float>());
    }

    TSharedPtr<FJsonObject> FProbability::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (PrizeValue != nullptr && PrizeValue.IsValid())
        {
            JsonRootObject->SetObjectField("prize", PrizeValue->ToJson());
        }
        if (RateValue.IsSet())
        {
            JsonRootObject->SetNumberField("rate", RateValue.GetValue());
        }
        return JsonRootObject;
    }

    FString FProbability::TypeName = "Probability";
}