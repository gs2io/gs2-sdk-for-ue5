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
#include "Enchant/Model/RarityParameterValue.h"

namespace Gs2::UE5::Enchant::Model
{
	class EZGS2_API FEzRarityParameterValue final : public TSharedFromThis<FEzRarityParameterValue>
	{
        TOptional<FString> NameValue;
        TOptional<FString> ResourceNameValue;
        TOptional<int64> ResourceValueValue;

	public:
        TSharedPtr<FEzRarityParameterValue> WithName(const TOptional<FString> Name);
        TSharedPtr<FEzRarityParameterValue> WithResourceName(const TOptional<FString> ResourceName);
        TSharedPtr<FEzRarityParameterValue> WithResourceValue(const TOptional<int64> ResourceValue);

        TOptional<FString> GetName() const;

        TOptional<FString> GetResourceName() const;

        TOptional<int64> GetResourceValue() const;
        FString GetResourceValueString() const;

        Gs2::Enchant::Model::FRarityParameterValuePtr ToModel() const;
        static TSharedPtr<FEzRarityParameterValue> FromModel(Gs2::Enchant::Model::FRarityParameterValuePtr Model);
    };
    typedef TSharedPtr<FEzRarityParameterValue> FEzRarityParameterValuePtr;
}