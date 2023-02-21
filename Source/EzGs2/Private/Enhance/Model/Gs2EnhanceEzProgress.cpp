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

#include "EzGs2/Public/Enhance/Model/Gs2EnhanceEzProgress.h"

namespace Gs2::UE5::Enhance::Model
{

    TSharedPtr<FEzProgress> FEzProgress::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FEzProgress> FEzProgress::WithRateName(
        const TOptional<FString> RateName
    )
    {
        this->RateNameValue = RateName;
        return SharedThis(this);
    }

    TSharedPtr<FEzProgress> FEzProgress::WithPropertyId(
        const TOptional<FString> PropertyId
    )
    {
        this->PropertyIdValue = PropertyId;
        return SharedThis(this);
    }

    TSharedPtr<FEzProgress> FEzProgress::WithExperienceValue(
        const TOptional<int32> ExperienceValue
    )
    {
        this->ExperienceValueValue = ExperienceValue;
        return SharedThis(this);
    }

    TSharedPtr<FEzProgress> FEzProgress::WithRate(
        const TOptional<float> Rate
    )
    {
        this->RateValue = Rate;
        return SharedThis(this);
    }
    TOptional<FString> FEzProgress::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FEzProgress::GetRateName() const
    {
        return RateNameValue;
    }
    TOptional<FString> FEzProgress::GetPropertyId() const
    {
        return PropertyIdValue;
    }
    TOptional<int32> FEzProgress::GetExperienceValue() const
    {
        return ExperienceValueValue;
    }

    FString FEzProgress::GetExperienceValueString() const
    {
        if (!ExperienceValueValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%ld"), ExperienceValueValue.GetValue());
    }
    TOptional<float> FEzProgress::GetRate() const
    {
        return RateValue;
    }

    FString FEzProgress::GetRateString() const
    {
        if (!RateValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%f"), RateValue.GetValue());
    }

    Gs2::Enhance::Model::FProgressPtr FEzProgress::ToModel() const
    {
        return MakeShared<Gs2::Enhance::Model::FProgress>()
            ->WithName(NameValue)
            ->WithRateName(RateNameValue)
            ->WithPropertyId(PropertyIdValue)
            ->WithExperienceValue(ExperienceValueValue)
            ->WithRate(RateValue);
    }

    TSharedPtr<FEzProgress> FEzProgress::FromModel(const Gs2::Enhance::Model::FProgressPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzProgress>()
            ->WithName(Model->GetName())
            ->WithRateName(Model->GetRateName())
            ->WithPropertyId(Model->GetPropertyId())
            ->WithExperienceValue(Model->GetExperienceValue())
            ->WithRate(Model->GetRate());
    }
}