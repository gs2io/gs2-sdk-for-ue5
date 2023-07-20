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
#include "Enchant/Model/RarityParameterCountModel.h"

namespace Gs2::UE5::Enchant::Model
{
	class EZGS2_API FEzRarityParameterCountModel final : public TSharedFromThis<FEzRarityParameterCountModel>
	{
        TOptional<int32> CountValue;
        TOptional<int32> WeightValue;

	public:
        TSharedPtr<FEzRarityParameterCountModel> WithCount(const TOptional<int32> Count);
        TSharedPtr<FEzRarityParameterCountModel> WithWeight(const TOptional<int32> Weight);

        TOptional<int32> GetCount() const;
        FString GetCountString() const;

        TOptional<int32> GetWeight() const;
        FString GetWeightString() const;

        Gs2::Enchant::Model::FRarityParameterCountModelPtr ToModel() const;
        static TSharedPtr<FEzRarityParameterCountModel> FromModel(Gs2::Enchant::Model::FRarityParameterCountModelPtr Model);
    };
    typedef TSharedPtr<FEzRarityParameterCountModel> FEzRarityParameterCountModelPtr;
}