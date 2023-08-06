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

#include "EzGs2/Public/Experience/Model/Gs2ExperienceEzStatus.h"

namespace Gs2::UE5::Experience::Model
{

    TSharedPtr<FEzStatus> FEzStatus::WithExperienceName(
        const TOptional<FString> ExperienceName
    )
    {
        this->ExperienceNameValue = ExperienceName;
        return SharedThis(this);
    }

    TSharedPtr<FEzStatus> FEzStatus::WithPropertyId(
        const TOptional<FString> PropertyId
    )
    {
        this->PropertyIdValue = PropertyId;
        return SharedThis(this);
    }

    TSharedPtr<FEzStatus> FEzStatus::WithExperienceValue(
        const TOptional<int64> ExperienceValue
    )
    {
        this->ExperienceValueValue = ExperienceValue;
        return SharedThis(this);
    }

    TSharedPtr<FEzStatus> FEzStatus::WithRankValue(
        const TOptional<int64> RankValue
    )
    {
        this->RankValueValue = RankValue;
        return SharedThis(this);
    }

    TSharedPtr<FEzStatus> FEzStatus::WithRankCapValue(
        const TOptional<int64> RankCapValue
    )
    {
        this->RankCapValueValue = RankCapValue;
        return SharedThis(this);
    }

    TSharedPtr<FEzStatus> FEzStatus::WithNextRankUpExperienceValue(
        const TOptional<int64> NextRankUpExperienceValue
    )
    {
        this->NextRankUpExperienceValueValue = NextRankUpExperienceValue;
        return SharedThis(this);
    }
    TOptional<FString> FEzStatus::GetExperienceName() const
    {
        return ExperienceNameValue;
    }
    TOptional<FString> FEzStatus::GetPropertyId() const
    {
        return PropertyIdValue;
    }
    TOptional<int64> FEzStatus::GetExperienceValue() const
    {
        return ExperienceValueValue;
    }

    FString FEzStatus::GetExperienceValueString() const
    {
        if (!ExperienceValueValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), ExperienceValueValue.GetValue());
    }
    TOptional<int64> FEzStatus::GetRankValue() const
    {
        return RankValueValue;
    }

    FString FEzStatus::GetRankValueString() const
    {
        if (!RankValueValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), RankValueValue.GetValue());
    }
    TOptional<int64> FEzStatus::GetRankCapValue() const
    {
        return RankCapValueValue;
    }

    FString FEzStatus::GetRankCapValueString() const
    {
        if (!RankCapValueValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), RankCapValueValue.GetValue());
    }
    TOptional<int64> FEzStatus::GetNextRankUpExperienceValue() const
    {
        return NextRankUpExperienceValueValue;
    }

    FString FEzStatus::GetNextRankUpExperienceValueString() const
    {
        if (!NextRankUpExperienceValueValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), NextRankUpExperienceValueValue.GetValue());
    }

    Gs2::Experience::Model::FStatusPtr FEzStatus::ToModel() const
    {
        return MakeShared<Gs2::Experience::Model::FStatus>()
            ->WithExperienceName(ExperienceNameValue)
            ->WithPropertyId(PropertyIdValue)
            ->WithExperienceValue(ExperienceValueValue)
            ->WithRankValue(RankValueValue)
            ->WithRankCapValue(RankCapValueValue)
            ->WithNextRankUpExperienceValue(NextRankUpExperienceValueValue);
    }

    TSharedPtr<FEzStatus> FEzStatus::FromModel(const Gs2::Experience::Model::FStatusPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzStatus>()
            ->WithExperienceName(Model->GetExperienceName())
            ->WithPropertyId(Model->GetPropertyId())
            ->WithExperienceValue(Model->GetExperienceValue())
            ->WithRankValue(Model->GetRankValue())
            ->WithRankCapValue(Model->GetRankCapValue())
            ->WithNextRankUpExperienceValue(Model->GetNextRankUpExperienceValue());
    }
}