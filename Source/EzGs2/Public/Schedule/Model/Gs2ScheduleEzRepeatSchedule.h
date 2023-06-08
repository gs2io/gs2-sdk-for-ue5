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
#include "Schedule/Model/RepeatSchedule.h"

namespace Gs2::UE5::Schedule::Model
{
	class EZGS2_API FEzRepeatSchedule final : public TSharedFromThis<FEzRepeatSchedule>
	{
        TOptional<int32> RepeatCountValue;
        TOptional<int64> CurrentRepeatStartAtValue;
        TOptional<int64> CurrentRepeatEndAtValue;
        TOptional<int64> LastRepeatEndAtValue;
        TOptional<int64> NextRepeatStartAtValue;

	public:
        TSharedPtr<FEzRepeatSchedule> WithRepeatCount(const TOptional<int32> RepeatCount);
        TSharedPtr<FEzRepeatSchedule> WithCurrentRepeatStartAt(const TOptional<int64> CurrentRepeatStartAt);
        TSharedPtr<FEzRepeatSchedule> WithCurrentRepeatEndAt(const TOptional<int64> CurrentRepeatEndAt);
        TSharedPtr<FEzRepeatSchedule> WithLastRepeatEndAt(const TOptional<int64> LastRepeatEndAt);
        TSharedPtr<FEzRepeatSchedule> WithNextRepeatStartAt(const TOptional<int64> NextRepeatStartAt);

        TOptional<int32> GetRepeatCount() const;
        FString GetRepeatCountString() const;

        TOptional<int64> GetCurrentRepeatStartAt() const;
        FString GetCurrentRepeatStartAtString() const;

        TOptional<int64> GetCurrentRepeatEndAt() const;
        FString GetCurrentRepeatEndAtString() const;

        TOptional<int64> GetLastRepeatEndAt() const;
        FString GetLastRepeatEndAtString() const;

        TOptional<int64> GetNextRepeatStartAt() const;
        FString GetNextRepeatStartAtString() const;

        Gs2::Schedule::Model::FRepeatSchedulePtr ToModel() const;
        static TSharedPtr<FEzRepeatSchedule> FromModel(Gs2::Schedule::Model::FRepeatSchedulePtr Model);
    };
    typedef TSharedPtr<FEzRepeatSchedule> FEzRepeatSchedulePtr;
}