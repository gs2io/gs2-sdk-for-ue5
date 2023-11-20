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

#include "Mission/Model/Gs2MissionEzCounterScopeModel.h"

namespace Gs2::UE5::Mission::Model
{

    TSharedPtr<FEzCounterScopeModel> FEzCounterScopeModel::WithResetType(
        const TOptional<FString> ResetType
    )
    {
        this->ResetTypeValue = ResetType;
        return SharedThis(this);
    }

    TSharedPtr<FEzCounterScopeModel> FEzCounterScopeModel::WithResetDayOfMonth(
        const TOptional<int32> ResetDayOfMonth
    )
    {
        this->ResetDayOfMonthValue = ResetDayOfMonth;
        return SharedThis(this);
    }

    TSharedPtr<FEzCounterScopeModel> FEzCounterScopeModel::WithResetDayOfWeek(
        const TOptional<FString> ResetDayOfWeek
    )
    {
        this->ResetDayOfWeekValue = ResetDayOfWeek;
        return SharedThis(this);
    }

    TSharedPtr<FEzCounterScopeModel> FEzCounterScopeModel::WithResetHour(
        const TOptional<int32> ResetHour
    )
    {
        this->ResetHourValue = ResetHour;
        return SharedThis(this);
    }
    TOptional<FString> FEzCounterScopeModel::GetResetType() const
    {
        return ResetTypeValue;
    }
    TOptional<int32> FEzCounterScopeModel::GetResetDayOfMonth() const
    {
        return ResetDayOfMonthValue;
    }

    FString FEzCounterScopeModel::GetResetDayOfMonthString() const
    {
        if (!ResetDayOfMonthValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), ResetDayOfMonthValue.GetValue());
    }
    TOptional<FString> FEzCounterScopeModel::GetResetDayOfWeek() const
    {
        return ResetDayOfWeekValue;
    }
    TOptional<int32> FEzCounterScopeModel::GetResetHour() const
    {
        return ResetHourValue;
    }

    FString FEzCounterScopeModel::GetResetHourString() const
    {
        if (!ResetHourValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), ResetHourValue.GetValue());
    }

    Gs2::Mission::Model::FCounterScopeModelPtr FEzCounterScopeModel::ToModel() const
    {
        return MakeShared<Gs2::Mission::Model::FCounterScopeModel>()
            ->WithResetType(ResetTypeValue)
            ->WithResetDayOfMonth(ResetDayOfMonthValue)
            ->WithResetDayOfWeek(ResetDayOfWeekValue)
            ->WithResetHour(ResetHourValue);
    }

    TSharedPtr<FEzCounterScopeModel> FEzCounterScopeModel::FromModel(const Gs2::Mission::Model::FCounterScopeModelPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzCounterScopeModel>()
            ->WithResetType(Model->GetResetType())
            ->WithResetDayOfMonth(Model->GetResetDayOfMonth())
            ->WithResetDayOfWeek(Model->GetResetDayOfWeek())
            ->WithResetHour(Model->GetResetHour());
    }
}