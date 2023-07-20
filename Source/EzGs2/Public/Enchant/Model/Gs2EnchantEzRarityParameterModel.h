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
#include "Enchant/Model/RarityParameterModel.h"
#include "Gs2EnchantEzRarityParameterCountModel.h"
#include "Gs2EnchantEzRarityParameterValueModel.h"

namespace Gs2::UE5::Enchant::Model
{
	class EZGS2_API FEzRarityParameterModel final : public TSharedFromThis<FEzRarityParameterModel>
	{
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;
        TOptional<int32> MaximumParameterCountValue;
        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Enchant::Model::FEzRarityParameterCountModel>>> ParameterCountsValue;
        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Enchant::Model::FEzRarityParameterValueModel>>> ParametersValue;

	public:
        TSharedPtr<FEzRarityParameterModel> WithName(const TOptional<FString> Name);
        TSharedPtr<FEzRarityParameterModel> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FEzRarityParameterModel> WithMaximumParameterCount(const TOptional<int32> MaximumParameterCount);
        TSharedPtr<FEzRarityParameterModel> WithParameterCounts(const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Enchant::Model::FEzRarityParameterCountModel>>> ParameterCounts);
        TSharedPtr<FEzRarityParameterModel> WithParameters(const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Enchant::Model::FEzRarityParameterValueModel>>> Parameters);

        TOptional<FString> GetName() const;

        TOptional<FString> GetMetadata() const;

        TOptional<int32> GetMaximumParameterCount() const;
        FString GetMaximumParameterCountString() const;

        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Enchant::Model::FEzRarityParameterCountModel>>> GetParameterCounts() const;

        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Enchant::Model::FEzRarityParameterValueModel>>> GetParameters() const;

        Gs2::Enchant::Model::FRarityParameterModelPtr ToModel() const;
        static TSharedPtr<FEzRarityParameterModel> FromModel(Gs2::Enchant::Model::FRarityParameterModelPtr Model);
    };
    typedef TSharedPtr<FEzRarityParameterModel> FEzRarityParameterModelPtr;
}