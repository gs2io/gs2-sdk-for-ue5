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
#include "Exchange/Model/RateModel.h"
#include "Gs2ExchangeEzVerifyAction.h"
#include "Gs2ExchangeEzConsumeAction.h"
#include "Gs2ExchangeEzAcquireAction.h"

namespace Gs2::UE5::Exchange::Model
{
	class EZGS2_API FEzRateModel final : public TSharedFromThis<FEzRateModel>
	{
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;
        TOptional<FString> TimingTypeValue;
        TOptional<int32> LockTimeValue;
        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Exchange::Model::FEzVerifyAction>>> VerifyActionsValue;
        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Exchange::Model::FEzConsumeAction>>> ConsumeActionsValue;
        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Exchange::Model::FEzAcquireAction>>> AcquireActionsValue;

	public:
        TSharedPtr<FEzRateModel> WithName(const TOptional<FString> Name);
        TSharedPtr<FEzRateModel> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FEzRateModel> WithTimingType(const TOptional<FString> TimingType);
        TSharedPtr<FEzRateModel> WithLockTime(const TOptional<int32> LockTime);
        TSharedPtr<FEzRateModel> WithVerifyActions(const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Exchange::Model::FEzVerifyAction>>> VerifyActions);
        TSharedPtr<FEzRateModel> WithConsumeActions(const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Exchange::Model::FEzConsumeAction>>> ConsumeActions);
        TSharedPtr<FEzRateModel> WithAcquireActions(const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Exchange::Model::FEzAcquireAction>>> AcquireActions);

        TOptional<FString> GetName() const;

        TOptional<FString> GetMetadata() const;

        TOptional<FString> GetTimingType() const;

        TOptional<int32> GetLockTime() const;
        FString GetLockTimeString() const;

        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Exchange::Model::FEzVerifyAction>>> GetVerifyActions() const;

        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Exchange::Model::FEzConsumeAction>>> GetConsumeActions() const;

        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Exchange::Model::FEzAcquireAction>>> GetAcquireActions() const;

        Gs2::Exchange::Model::FRateModelPtr ToModel() const;
        static TSharedPtr<FEzRateModel> FromModel(Gs2::Exchange::Model::FRateModelPtr Model);
    };
    typedef TSharedPtr<FEzRateModel> FEzRateModelPtr;
}