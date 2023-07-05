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
#include "Exchange/Model/IncrementalRateModel.h"
#include "Gs2ExchangeEzConsumeAction.h"
#include "Gs2ExchangeEzAcquireAction.h"

namespace Gs2::UE5::Exchange::Model
{
	class EZGS2_API FEzIncrementalRateModel final : public TSharedFromThis<FEzIncrementalRateModel>
	{
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;
        TOptional<FString> CalculateTypeValue;
        TSharedPtr<Gs2::UE5::Exchange::Model::FEzConsumeAction> ConsumeActionValue;
        TOptional<int64> BaseValueValue;
        TOptional<int64> CoefficientValueValue;
        TOptional<FString> ExchangeCountIdValue;
        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Exchange::Model::FEzAcquireAction>>> AcquireActionsValue;

	public:
        TSharedPtr<FEzIncrementalRateModel> WithName(const TOptional<FString> Name);
        TSharedPtr<FEzIncrementalRateModel> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FEzIncrementalRateModel> WithCalculateType(const TOptional<FString> CalculateType);
        TSharedPtr<FEzIncrementalRateModel> WithConsumeAction(const TSharedPtr<Gs2::UE5::Exchange::Model::FEzConsumeAction> ConsumeAction);
        TSharedPtr<FEzIncrementalRateModel> WithBaseValue(const TOptional<int64> BaseValue);
        TSharedPtr<FEzIncrementalRateModel> WithCoefficientValue(const TOptional<int64> CoefficientValue);
        TSharedPtr<FEzIncrementalRateModel> WithExchangeCountId(const TOptional<FString> ExchangeCountId);
        TSharedPtr<FEzIncrementalRateModel> WithAcquireActions(const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Exchange::Model::FEzAcquireAction>>> AcquireActions);

        TOptional<FString> GetName() const;

        TOptional<FString> GetMetadata() const;

        TOptional<FString> GetCalculateType() const;

        TSharedPtr<Gs2::UE5::Exchange::Model::FEzConsumeAction> GetConsumeAction() const;

        TOptional<int64> GetBaseValue() const;
        FString GetBaseValueString() const;

        TOptional<int64> GetCoefficientValue() const;
        FString GetCoefficientValueString() const;

        TOptional<FString> GetExchangeCountId() const;

        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Exchange::Model::FEzAcquireAction>>> GetAcquireActions() const;

        Gs2::Exchange::Model::FIncrementalRateModelPtr ToModel() const;
        static TSharedPtr<FEzIncrementalRateModel> FromModel(Gs2::Exchange::Model::FIncrementalRateModelPtr Model);
    };
    typedef TSharedPtr<FEzIncrementalRateModel> FEzIncrementalRateModelPtr;
}