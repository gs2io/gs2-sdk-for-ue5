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

#include "Schedule/Model/Gs2ScheduleEzRepeatSchedule.h"

namespace Gs2::UE5::Schedule::Model
{

    TSharedPtr<FEzRepeatSchedule> FEzRepeatSchedule::WithRepeatCount(
        const TOptional<int32> RepeatCount
    )
    {
        this->RepeatCountValue = RepeatCount;
        return SharedThis(this);
    }

    TSharedPtr<FEzRepeatSchedule> FEzRepeatSchedule::WithCurrentRepeatStartAt(
        const TOptional<int64> CurrentRepeatStartAt
    )
    {
        this->CurrentRepeatStartAtValue = CurrentRepeatStartAt;
        return SharedThis(this);
    }

    TSharedPtr<FEzRepeatSchedule> FEzRepeatSchedule::WithCurrentRepeatEndAt(
        const TOptional<int64> CurrentRepeatEndAt
    )
    {
        this->CurrentRepeatEndAtValue = CurrentRepeatEndAt;
        return SharedThis(this);
    }

    TSharedPtr<FEzRepeatSchedule> FEzRepeatSchedule::WithLastRepeatEndAt(
        const TOptional<int64> LastRepeatEndAt
    )
    {
        this->LastRepeatEndAtValue = LastRepeatEndAt;
        return SharedThis(this);
    }

    TSharedPtr<FEzRepeatSchedule> FEzRepeatSchedule::WithNextRepeatStartAt(
        const TOptional<int64> NextRepeatStartAt
    )
    {
        this->NextRepeatStartAtValue = NextRepeatStartAt;
        return SharedThis(this);
    }
    TOptional<int32> FEzRepeatSchedule::GetRepeatCount() const
    {
        return RepeatCountValue;
    }

    FString FEzRepeatSchedule::GetRepeatCountString() const
    {
        if (!RepeatCountValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), RepeatCountValue.GetValue());
    }
    TOptional<int64> FEzRepeatSchedule::GetCurrentRepeatStartAt() const
    {
        return CurrentRepeatStartAtValue;
    }

    FString FEzRepeatSchedule::GetCurrentRepeatStartAtString() const
    {
        if (!CurrentRepeatStartAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CurrentRepeatStartAtValue.GetValue());
    }
    TOptional<int64> FEzRepeatSchedule::GetCurrentRepeatEndAt() const
    {
        return CurrentRepeatEndAtValue;
    }

    FString FEzRepeatSchedule::GetCurrentRepeatEndAtString() const
    {
        if (!CurrentRepeatEndAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CurrentRepeatEndAtValue.GetValue());
    }
    TOptional<int64> FEzRepeatSchedule::GetLastRepeatEndAt() const
    {
        return LastRepeatEndAtValue;
    }

    FString FEzRepeatSchedule::GetLastRepeatEndAtString() const
    {
        if (!LastRepeatEndAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), LastRepeatEndAtValue.GetValue());
    }
    TOptional<int64> FEzRepeatSchedule::GetNextRepeatStartAt() const
    {
        return NextRepeatStartAtValue;
    }

    FString FEzRepeatSchedule::GetNextRepeatStartAtString() const
    {
        if (!NextRepeatStartAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), NextRepeatStartAtValue.GetValue());
    }

    Gs2::Schedule::Model::FRepeatSchedulePtr FEzRepeatSchedule::ToModel() const
    {
        return MakeShared<Gs2::Schedule::Model::FRepeatSchedule>()
            ->WithRepeatCount(RepeatCountValue)
            ->WithCurrentRepeatStartAt(CurrentRepeatStartAtValue)
            ->WithCurrentRepeatEndAt(CurrentRepeatEndAtValue)
            ->WithLastRepeatEndAt(LastRepeatEndAtValue)
            ->WithNextRepeatStartAt(NextRepeatStartAtValue);
    }

    TSharedPtr<FEzRepeatSchedule> FEzRepeatSchedule::FromModel(const Gs2::Schedule::Model::FRepeatSchedulePtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzRepeatSchedule>()
            ->WithRepeatCount(Model->GetRepeatCount())
            ->WithCurrentRepeatStartAt(Model->GetCurrentRepeatStartAt())
            ->WithCurrentRepeatEndAt(Model->GetCurrentRepeatEndAt())
            ->WithLastRepeatEndAt(Model->GetLastRepeatEndAt())
            ->WithNextRepeatStartAt(Model->GetNextRepeatStartAt());
    }
}