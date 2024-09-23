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
#include "Core/Gs2Object.h"
#include "VerifyAction.h"

namespace Gs2::Mission::Model
{
    class GS2MISSION_API FCounterScopeModel final : public Gs2Object, public TSharedFromThis<FCounterScopeModel>
    {
        TOptional<FString> ScopeTypeValue;
        TOptional<FString> ResetTypeValue;
        TOptional<int32> ResetDayOfMonthValue;
        TOptional<FString> ResetDayOfWeekValue;
        TOptional<int32> ResetHourValue;
        TOptional<FString> ConditionNameValue;
        TSharedPtr<FVerifyAction> ConditionValue;

    public:
        FCounterScopeModel();
        FCounterScopeModel(
            const FCounterScopeModel& From
        );
        virtual ~FCounterScopeModel() override = default;

        TSharedPtr<FCounterScopeModel> WithScopeType(const TOptional<FString> ScopeType);
        TSharedPtr<FCounterScopeModel> WithResetType(const TOptional<FString> ResetType);
        TSharedPtr<FCounterScopeModel> WithResetDayOfMonth(const TOptional<int32> ResetDayOfMonth);
        TSharedPtr<FCounterScopeModel> WithResetDayOfWeek(const TOptional<FString> ResetDayOfWeek);
        TSharedPtr<FCounterScopeModel> WithResetHour(const TOptional<int32> ResetHour);
        TSharedPtr<FCounterScopeModel> WithConditionName(const TOptional<FString> ConditionName);
        TSharedPtr<FCounterScopeModel> WithCondition(const TSharedPtr<FVerifyAction> Condition);

        TOptional<FString> GetScopeType() const;
        TOptional<FString> GetResetType() const;
        TOptional<int32> GetResetDayOfMonth() const;
        FString GetResetDayOfMonthString() const;
        TOptional<FString> GetResetDayOfWeek() const;
        TOptional<int32> GetResetHour() const;
        FString GetResetHourString() const;
        TOptional<FString> GetConditionName() const;
        TSharedPtr<FVerifyAction> GetCondition() const;


        static TSharedPtr<FCounterScopeModel> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FCounterScopeModel, ESPMode::ThreadSafe> FCounterScopeModelPtr;
}