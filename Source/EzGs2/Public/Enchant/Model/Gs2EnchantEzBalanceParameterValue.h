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
#include "Enchant/Model/BalanceParameterValue.h"

namespace Gs2::UE5::Enchant::Model
{
	class EZGS2_API FEzBalanceParameterValue final : public TSharedFromThis<FEzBalanceParameterValue>
	{
        TOptional<FString> NameValue;
        TOptional<int64> ValueValue;

	public:
        TSharedPtr<FEzBalanceParameterValue> WithName(const TOptional<FString> Name);
        TSharedPtr<FEzBalanceParameterValue> WithValue(const TOptional<int64> Value);

        TOptional<FString> GetName() const;

        TOptional<int64> GetValue() const;
        FString GetValueString() const;

        Gs2::Enchant::Model::FBalanceParameterValuePtr ToModel() const;
        static TSharedPtr<FEzBalanceParameterValue> FromModel(Gs2::Enchant::Model::FBalanceParameterValuePtr Model);
    };
    typedef TSharedPtr<FEzBalanceParameterValue> FEzBalanceParameterValuePtr;
}