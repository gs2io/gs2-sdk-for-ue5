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
#include "Mission/Model/TargetCounterModel.h"

namespace Gs2::UE5::Mission::Model
{
	class EZGS2_API FEzTargetCounterModel final : public TSharedFromThis<FEzTargetCounterModel>
	{
        TOptional<FString> CounterNameValue;
        TOptional<FString> ScopeTypeValue;
        TOptional<FString> ResetTypeValue;
        TOptional<FString> ConditionNameValue;
        TOptional<int64> ValueValue;

	public:
        TSharedPtr<FEzTargetCounterModel> WithCounterName(const TOptional<FString> CounterName);
        TSharedPtr<FEzTargetCounterModel> WithScopeType(const TOptional<FString> ScopeType);
        TSharedPtr<FEzTargetCounterModel> WithResetType(const TOptional<FString> ResetType);
        TSharedPtr<FEzTargetCounterModel> WithConditionName(const TOptional<FString> ConditionName);
        TSharedPtr<FEzTargetCounterModel> WithValue(const TOptional<int64> Value);

        TOptional<FString> GetCounterName() const;

        TOptional<FString> GetScopeType() const;

        TOptional<FString> GetResetType() const;

        TOptional<FString> GetConditionName() const;

        TOptional<int64> GetValue() const;
        FString GetValueString() const;

        Gs2::Mission::Model::FTargetCounterModelPtr ToModel() const;
        static TSharedPtr<FEzTargetCounterModel> FromModel(Gs2::Mission::Model::FTargetCounterModelPtr Model);
    };
    typedef TSharedPtr<FEzTargetCounterModel> FEzTargetCounterModelPtr;
}