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
#include "Enchant/Model/BalanceParameterStatus.h"
#include "Gs2EnchantEzBalanceParameterValue.h"

namespace Gs2::UE5::Enchant::Model
{
	class EZGS2_API FEzBalanceParameterStatus final : public TSharedFromThis<FEzBalanceParameterStatus>
	{
        TOptional<FString> ParameterNameValue;
        TOptional<FString> PropertyIdValue;
        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Enchant::Model::FEzBalanceParameterValue>>> ParameterValuesValue;

	public:
        TSharedPtr<FEzBalanceParameterStatus> WithParameterName(const TOptional<FString> ParameterName);
        TSharedPtr<FEzBalanceParameterStatus> WithPropertyId(const TOptional<FString> PropertyId);
        TSharedPtr<FEzBalanceParameterStatus> WithParameterValues(const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Enchant::Model::FEzBalanceParameterValue>>> ParameterValues);

        TOptional<FString> GetParameterName() const;

        TOptional<FString> GetPropertyId() const;

        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Enchant::Model::FEzBalanceParameterValue>>> GetParameterValues() const;

        Gs2::Enchant::Model::FBalanceParameterStatusPtr ToModel() const;
        static TSharedPtr<FEzBalanceParameterStatus> FromModel(Gs2::Enchant::Model::FBalanceParameterStatusPtr Model);
    };
    typedef TSharedPtr<FEzBalanceParameterStatus> FEzBalanceParameterStatusPtr;
}