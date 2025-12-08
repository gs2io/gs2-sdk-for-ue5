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

#pragma once

#include "CoreMinimal.h"
#include "Mission/Model/CounterScopeModel.h"
#include "Gs2MissionEzVerifyAction.h"

namespace Gs2::UE5::Mission::Model
{
	class EZGS2_API FEzCounterScopeModel final : public TSharedFromThis<FEzCounterScopeModel>
	{
        TOptional<FString> ScopeTypeValue;
        TOptional<FString> ResetTypeValue;
        TOptional<int32> ResetDayOfMonthValue;
        TOptional<FString> ResetDayOfWeekValue;
        TOptional<int32> ResetHourValue;
        TOptional<FString> ConditionNameValue;
        TSharedPtr<Gs2::UE5::Mission::Model::FEzVerifyAction> ConditionValue;
        TOptional<int64> AnchorTimestampValue;
        TOptional<int32> DaysValue;

	public:
        TSharedPtr<FEzCounterScopeModel> WithScopeType(const TOptional<FString> ScopeType);
        TSharedPtr<FEzCounterScopeModel> WithResetType(const TOptional<FString> ResetType);
        TSharedPtr<FEzCounterScopeModel> WithResetDayOfMonth(const TOptional<int32> ResetDayOfMonth);
        TSharedPtr<FEzCounterScopeModel> WithResetDayOfWeek(const TOptional<FString> ResetDayOfWeek);
        TSharedPtr<FEzCounterScopeModel> WithResetHour(const TOptional<int32> ResetHour);
        TSharedPtr<FEzCounterScopeModel> WithConditionName(const TOptional<FString> ConditionName);
        TSharedPtr<FEzCounterScopeModel> WithCondition(const TSharedPtr<Gs2::UE5::Mission::Model::FEzVerifyAction> Condition);
        TSharedPtr<FEzCounterScopeModel> WithAnchorTimestamp(const TOptional<int64> AnchorTimestamp);
        TSharedPtr<FEzCounterScopeModel> WithDays(const TOptional<int32> Days);

        TOptional<FString> GetScopeType() const;

        TOptional<FString> GetResetType() const;

        TOptional<int32> GetResetDayOfMonth() const;
        FString GetResetDayOfMonthString() const;

        TOptional<FString> GetResetDayOfWeek() const;

        TOptional<int32> GetResetHour() const;
        FString GetResetHourString() const;

        TOptional<FString> GetConditionName() const;

        TSharedPtr<Gs2::UE5::Mission::Model::FEzVerifyAction> GetCondition() const;

        TOptional<int64> GetAnchorTimestamp() const;
        FString GetAnchorTimestampString() const;

        TOptional<int32> GetDays() const;
        FString GetDaysString() const;

        Gs2::Mission::Model::FCounterScopeModelPtr ToModel() const;
        static TSharedPtr<FEzCounterScopeModel> FromModel(Gs2::Mission::Model::FCounterScopeModelPtr Model);
    };
    typedef TSharedPtr<FEzCounterScopeModel> FEzCounterScopeModelPtr;
}