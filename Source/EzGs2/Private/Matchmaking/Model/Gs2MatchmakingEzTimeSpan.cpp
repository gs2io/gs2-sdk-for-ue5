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

#include "Matchmaking/Model/Gs2MatchmakingEzTimeSpan.h"

namespace Gs2::UE5::Matchmaking::Model
{

    TSharedPtr<FEzTimeSpan> FEzTimeSpan::WithDays(
        const TOptional<int32> Days
    )
    {
        this->DaysValue = Days;
        return SharedThis(this);
    }

    TSharedPtr<FEzTimeSpan> FEzTimeSpan::WithHours(
        const TOptional<int32> Hours
    )
    {
        this->HoursValue = Hours;
        return SharedThis(this);
    }

    TSharedPtr<FEzTimeSpan> FEzTimeSpan::WithMinutes(
        const TOptional<int32> Minutes
    )
    {
        this->MinutesValue = Minutes;
        return SharedThis(this);
    }
    TOptional<int32> FEzTimeSpan::GetDays() const
    {
        return DaysValue;
    }

    FString FEzTimeSpan::GetDaysString() const
    {
        if (!DaysValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), DaysValue.GetValue());
    }
    TOptional<int32> FEzTimeSpan::GetHours() const
    {
        return HoursValue;
    }

    FString FEzTimeSpan::GetHoursString() const
    {
        if (!HoursValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), HoursValue.GetValue());
    }
    TOptional<int32> FEzTimeSpan::GetMinutes() const
    {
        return MinutesValue;
    }

    FString FEzTimeSpan::GetMinutesString() const
    {
        if (!MinutesValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), MinutesValue.GetValue());
    }

    Gs2::Matchmaking::Model::FTimeSpanPtr FEzTimeSpan::ToModel() const
    {
        return MakeShared<Gs2::Matchmaking::Model::FTimeSpan>()
            ->WithDays(DaysValue)
            ->WithHours(HoursValue)
            ->WithMinutes(MinutesValue);
    }

    TSharedPtr<FEzTimeSpan> FEzTimeSpan::FromModel(const Gs2::Matchmaking::Model::FTimeSpanPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzTimeSpan>()
            ->WithDays(Model->GetDays())
            ->WithHours(Model->GetHours())
            ->WithMinutes(Model->GetMinutes());
    }
}