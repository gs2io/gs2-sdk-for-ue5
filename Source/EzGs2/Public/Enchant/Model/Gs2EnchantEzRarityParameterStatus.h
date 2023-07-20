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
#include "Enchant/Model/RarityParameterStatus.h"
#include "Gs2EnchantEzRarityParameterValue.h"

namespace Gs2::UE5::Enchant::Model
{
	class EZGS2_API FEzRarityParameterStatus final : public TSharedFromThis<FEzRarityParameterStatus>
	{
        TOptional<FString> ParameterNameValue;
        TOptional<FString> PropertyIdValue;
        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Enchant::Model::FEzRarityParameterValue>>> ParameterValuesValue;

	public:
        TSharedPtr<FEzRarityParameterStatus> WithParameterName(const TOptional<FString> ParameterName);
        TSharedPtr<FEzRarityParameterStatus> WithPropertyId(const TOptional<FString> PropertyId);
        TSharedPtr<FEzRarityParameterStatus> WithParameterValues(const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Enchant::Model::FEzRarityParameterValue>>> ParameterValues);

        TOptional<FString> GetParameterName() const;

        TOptional<FString> GetPropertyId() const;

        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Enchant::Model::FEzRarityParameterValue>>> GetParameterValues() const;

        Gs2::Enchant::Model::FRarityParameterStatusPtr ToModel() const;
        static TSharedPtr<FEzRarityParameterStatus> FromModel(Gs2::Enchant::Model::FRarityParameterStatusPtr Model);
    };
    typedef TSharedPtr<FEzRarityParameterStatus> FEzRarityParameterStatusPtr;
}