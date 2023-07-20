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
#include "Enchant/Model/BalanceParameterModel.h"
#include "Gs2EnchantEzBalanceParameterValueModel.h"

namespace Gs2::UE5::Enchant::Model
{
	class EZGS2_API FEzBalanceParameterModel final : public TSharedFromThis<FEzBalanceParameterModel>
	{
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;
        TOptional<int64> TotalValueValue;
        TOptional<FString> InitialValueStrategyValue;
        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Enchant::Model::FEzBalanceParameterValueModel>>> ParametersValue;

	public:
        TSharedPtr<FEzBalanceParameterModel> WithName(const TOptional<FString> Name);
        TSharedPtr<FEzBalanceParameterModel> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FEzBalanceParameterModel> WithTotalValue(const TOptional<int64> TotalValue);
        TSharedPtr<FEzBalanceParameterModel> WithInitialValueStrategy(const TOptional<FString> InitialValueStrategy);
        TSharedPtr<FEzBalanceParameterModel> WithParameters(const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Enchant::Model::FEzBalanceParameterValueModel>>> Parameters);

        TOptional<FString> GetName() const;

        TOptional<FString> GetMetadata() const;

        TOptional<int64> GetTotalValue() const;
        FString GetTotalValueString() const;

        TOptional<FString> GetInitialValueStrategy() const;

        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Enchant::Model::FEzBalanceParameterValueModel>>> GetParameters() const;

        Gs2::Enchant::Model::FBalanceParameterModelPtr ToModel() const;
        static TSharedPtr<FEzBalanceParameterModel> FromModel(Gs2::Enchant::Model::FBalanceParameterModelPtr Model);
    };
    typedef TSharedPtr<FEzBalanceParameterModel> FEzBalanceParameterModelPtr;
}