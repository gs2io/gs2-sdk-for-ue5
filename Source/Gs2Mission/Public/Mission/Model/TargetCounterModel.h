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

namespace Gs2::Mission::Model
{
    class GS2MISSION_API FTargetCounterModel final : public FGs2Object, public TSharedFromThis<FTargetCounterModel>
    {
        TOptional<FString> CounterNameValue;
        TOptional<FString> ScopeTypeValue;
        TOptional<FString> ResetTypeValue;
        TOptional<FString> ConditionNameValue;
        TOptional<int64> ValueValue;

    public:
        FTargetCounterModel();
        FTargetCounterModel(
            const FTargetCounterModel& From
        );
        virtual ~FTargetCounterModel() override = default;

        TSharedPtr<FTargetCounterModel> WithCounterName(const TOptional<FString> CounterName);
        TSharedPtr<FTargetCounterModel> WithScopeType(const TOptional<FString> ScopeType);
        TSharedPtr<FTargetCounterModel> WithResetType(const TOptional<FString> ResetType);
        TSharedPtr<FTargetCounterModel> WithConditionName(const TOptional<FString> ConditionName);
        TSharedPtr<FTargetCounterModel> WithValue(const TOptional<int64> Value);

        TOptional<FString> GetCounterName() const;
        TOptional<FString> GetScopeType() const;
        TOptional<FString> GetResetType() const;
        TOptional<FString> GetConditionName() const;
        TOptional<int64> GetValue() const;
        FString GetValueString() const;


        static TSharedPtr<FTargetCounterModel> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FTargetCounterModel, ESPMode::ThreadSafe> FTargetCounterModelPtr;
}