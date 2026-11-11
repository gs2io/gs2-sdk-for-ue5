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
#include "Enhance/Model/UnleashMaterialSelection.h"

namespace Gs2::UE5::Enhance::Model
{
	class EZGS2_API FEzUnleashMaterialSelection final : public TSharedFromThis<FEzUnleashMaterialSelection>
	{
        TOptional<FString> NameValue;
        TSharedPtr<TArray<FString>> ItemSetIdsValue;

	public:
        TSharedPtr<FEzUnleashMaterialSelection> WithName(const TOptional<FString> Name);
        TSharedPtr<FEzUnleashMaterialSelection> WithItemSetIds(const TSharedPtr<TArray<FString>> ItemSetIds);

        TOptional<FString> GetName() const;

        TSharedPtr<TArray<FString>> GetItemSetIds() const;

        Gs2::Enhance::Model::FUnleashMaterialSelectionPtr ToModel() const;
        static TSharedPtr<FEzUnleashMaterialSelection> FromModel(Gs2::Enhance::Model::FUnleashMaterialSelectionPtr Model);
    };
    typedef TSharedPtr<FEzUnleashMaterialSelection> FEzUnleashMaterialSelectionPtr;
}