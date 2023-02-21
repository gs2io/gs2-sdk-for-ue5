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

#include "Enhance/Model/BonusRate.h"

namespace Gs2::Enhance::Model
{
    FBonusRate::FBonusRate():
        RateValue(TOptional<float>()),
        WeightValue(TOptional<int32>())
    {
    }

    FBonusRate::FBonusRate(
        const FBonusRate& From
    ):
        RateValue(From.RateValue),
        WeightValue(From.WeightValue)
    {
    }

    TSharedPtr<FBonusRate> FBonusRate::WithRate(
        const TOptional<float> Rate
    )
    {
        this->RateValue = Rate;
        return SharedThis(this);
    }

    TSharedPtr<FBonusRate> FBonusRate::WithWeight(
        const TOptional<int32> Weight
    )
    {
        this->WeightValue = Weight;
        return SharedThis(this);
    }
    TOptional<float> FBonusRate::GetRate() const
    {
        return RateValue;
    }

    FString FBonusRate::GetRateString() const
    {
        if (!RateValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%f"), RateValue.GetValue());
    }
    TOptional<int32> FBonusRate::GetWeight() const
    {
        return WeightValue;
    }

    FString FBonusRate::GetWeightString() const
    {
        if (!WeightValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%ld"), WeightValue.GetValue());
    }

    TSharedPtr<FBonusRate> FBonusRate::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FBonusRate>()
            ->WithRate(Data->HasField("rate") ? [Data]() -> TOptional<float>
                {
                    float v;
                    if (Data->TryGetNumberField("rate", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<float>();
                }() : TOptional<float>())
            ->WithWeight(Data->HasField("weight") ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField("weight", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>());
    }

    TSharedPtr<FJsonObject> FBonusRate::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (RateValue.IsSet())
        {
            JsonRootObject->SetNumberField("rate", RateValue.GetValue());
        }
        if (WeightValue.IsSet())
        {
            JsonRootObject->SetNumberField("weight", WeightValue.GetValue());
        }
        return JsonRootObject;
    }

    FString FBonusRate::TypeName = "BonusRate";
}