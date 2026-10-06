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
#include "Enhance/Model/UnleashRecipe.h"
#include "Gs2EnhanceEzUnleashMaterial.h"

namespace Gs2::UE5::Enhance::Model
{
	class EZGS2_API FEzUnleashRecipe final : public TSharedFromThis<FEzUnleashRecipe>
	{
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;
        TSharedPtr<TArray<FString>> TargetGroupKeysValue;
        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Enhance::Model::FEzUnleashMaterial>>> MaterialsValue;

	public:
        TSharedPtr<FEzUnleashRecipe> WithName(const TOptional<FString> Name);
        TSharedPtr<FEzUnleashRecipe> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FEzUnleashRecipe> WithTargetGroupKeys(const TSharedPtr<TArray<FString>> TargetGroupKeys);
        TSharedPtr<FEzUnleashRecipe> WithMaterials(const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Enhance::Model::FEzUnleashMaterial>>> Materials);

        TOptional<FString> GetName() const;

        TOptional<FString> GetMetadata() const;

        TSharedPtr<TArray<FString>> GetTargetGroupKeys() const;

        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Enhance::Model::FEzUnleashMaterial>>> GetMaterials() const;

        Gs2::Enhance::Model::FUnleashRecipePtr ToModel() const;
        static TSharedPtr<FEzUnleashRecipe> FromModel(Gs2::Enhance::Model::FUnleashRecipePtr Model);
    };
    typedef TSharedPtr<FEzUnleashRecipe> FEzUnleashRecipePtr;
}