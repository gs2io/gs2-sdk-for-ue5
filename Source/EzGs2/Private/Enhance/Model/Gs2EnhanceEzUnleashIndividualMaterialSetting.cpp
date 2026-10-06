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

#include "Enhance/Model/Gs2EnhanceEzUnleashIndividualMaterialSetting.h"

namespace Gs2::UE5::Enhance::Model
{

    TSharedPtr<FEzUnleashIndividualMaterialSetting> FEzUnleashIndividualMaterialSetting::WithMatchType(
        const TOptional<FString> MatchType
    )
    {
        this->MatchTypeValue = MatchType;
        return SharedThis(this);
    }

    TSharedPtr<FEzUnleashIndividualMaterialSetting> FEzUnleashIndividualMaterialSetting::WithGradeCondition(
        const TOptional<FString> GradeCondition
    )
    {
        this->GradeConditionValue = GradeCondition;
        return SharedThis(this);
    }

    TSharedPtr<FEzUnleashIndividualMaterialSetting> FEzUnleashIndividualMaterialSetting::WithGradeValue(
        const TOptional<int64> GradeValue
    )
    {
        this->GradeValueValue = GradeValue;
        return SharedThis(this);
    }

    TSharedPtr<FEzUnleashIndividualMaterialSetting> FEzUnleashIndividualMaterialSetting::WithCount(
        const TOptional<int32> Count
    )
    {
        this->CountValue = Count;
        return SharedThis(this);
    }
    TOptional<FString> FEzUnleashIndividualMaterialSetting::GetMatchType() const
    {
        return MatchTypeValue;
    }
    TOptional<FString> FEzUnleashIndividualMaterialSetting::GetGradeCondition() const
    {
        return GradeConditionValue;
    }
    TOptional<int64> FEzUnleashIndividualMaterialSetting::GetGradeValue() const
    {
        return GradeValueValue;
    }

    FString FEzUnleashIndividualMaterialSetting::GetGradeValueString() const
    {
        if (!GradeValueValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), GradeValueValue.GetValue());
    }
    TOptional<int32> FEzUnleashIndividualMaterialSetting::GetCount() const
    {
        return CountValue;
    }

    FString FEzUnleashIndividualMaterialSetting::GetCountString() const
    {
        if (!CountValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), CountValue.GetValue());
    }

    Gs2::Enhance::Model::FUnleashIndividualMaterialSettingPtr FEzUnleashIndividualMaterialSetting::ToModel() const
    {
        return MakeShared<Gs2::Enhance::Model::FUnleashIndividualMaterialSetting>()
            ->WithMatchType(MatchTypeValue)
            ->WithGradeCondition(GradeConditionValue)
            ->WithGradeValue(GradeValueValue)
            ->WithCount(CountValue);
    }

    TSharedPtr<FEzUnleashIndividualMaterialSetting> FEzUnleashIndividualMaterialSetting::FromModel(const Gs2::Enhance::Model::FUnleashIndividualMaterialSettingPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzUnleashIndividualMaterialSetting>()
            ->WithMatchType(Model->GetMatchType())
            ->WithGradeCondition(Model->GetGradeCondition())
            ->WithGradeValue(Model->GetGradeValue())
            ->WithCount(Model->GetCount());
    }
}