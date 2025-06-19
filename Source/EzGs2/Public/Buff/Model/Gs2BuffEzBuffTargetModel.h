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
 *
 * deny overwrite
 */

#pragma once

#include "CoreMinimal.h"
#include "Gs2BuffEzBuffTargetGrn.h"
#include "Buff/Model/BuffTargetModel.h"

namespace Gs2::UE5::Buff::Model
{
	class EZGS2_API FEzBuffTargetModel final : public TSharedFromThis<FEzBuffTargetModel>
	{
        TOptional<FString> TargetModelNameValue;
        TOptional<FString> TargetFieldNameValue;
        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Buff::Model::FEzBuffTargetGrn>>> ConditionGrnsValue;
        TOptional<float> RateValue;

	public:
        TSharedPtr<FEzBuffTargetModel> WithTargetModelName(const TOptional<FString> TargetModelName);
        TSharedPtr<FEzBuffTargetModel> WithTargetFieldName(const TOptional<FString> TargetFieldName);
        TSharedPtr<FEzBuffTargetModel> WithConditionGrns(const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Buff::Model::FEzBuffTargetGrn>>> ConditionGrns);
        TSharedPtr<FEzBuffTargetModel> WithRate(const TOptional<float> Rate);

        TOptional<FString> GetTargetModelName() const;

        TOptional<FString> GetTargetFieldName() const;

        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Buff::Model::FEzBuffTargetGrn>>> GetConditionGrns() const;

        TOptional<float> GetRate() const;
        FString GetRateString() const;

        Gs2::Buff::Model::FBuffTargetModelPtr ToModel() const;
        static TSharedPtr<FEzBuffTargetModel> FromModel(Gs2::Buff::Model::FBuffTargetModelPtr Model);
    };
    typedef TSharedPtr<FEzBuffTargetModel> FEzBuffTargetModelPtr;
}