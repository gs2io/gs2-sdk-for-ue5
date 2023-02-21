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

namespace Gs2::UE5::Mission::Model
{
	class EZGS2_API FEzCounterScopeModel final : public TSharedFromThis<FEzCounterScopeModel>
	{
        TOptional<FString> ResetTypeValue;
        TOptional<int32> ResetDayOfMonthValue;
        TOptional<FString> ResetDayOfWeekValue;
        TOptional<int32> ResetHourValue;

	public:
        TSharedPtr<FEzCounterScopeModel> WithResetType(const TOptional<FString> ResetType);
        TSharedPtr<FEzCounterScopeModel> WithResetDayOfMonth(const TOptional<int32> ResetDayOfMonth);
        TSharedPtr<FEzCounterScopeModel> WithResetDayOfWeek(const TOptional<FString> ResetDayOfWeek);
        TSharedPtr<FEzCounterScopeModel> WithResetHour(const TOptional<int32> ResetHour);

        TOptional<FString> GetResetType() const;

        TOptional<int32> GetResetDayOfMonth() const;
        FString GetResetDayOfMonthString() const;

        TOptional<FString> GetResetDayOfWeek() const;

        TOptional<int32> GetResetHour() const;
        FString GetResetHourString() const;

        Gs2::Mission::Model::FCounterScopeModelPtr ToModel() const;
        static TSharedPtr<FEzCounterScopeModel> FromModel(Gs2::Mission::Model::FCounterScopeModelPtr Model);
    };
    typedef TSharedPtr<FEzCounterScopeModel> FEzCounterScopeModelPtr;
}