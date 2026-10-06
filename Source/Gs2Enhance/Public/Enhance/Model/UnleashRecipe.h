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
#include "Core/Gs2Object.h"
#include "UnleashMaterial.h"

namespace Gs2::Enhance::Model
{
    class GS2ENHANCE_API FUnleashRecipe final : public FGs2Object, public TSharedFromThis<FUnleashRecipe>
    {
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;
        TSharedPtr<TArray<FString>> TargetGroupKeysValue;
        TSharedPtr<TArray<TSharedPtr<FUnleashMaterial>>> MaterialsValue;

    public:
        FUnleashRecipe();
        FUnleashRecipe(
            const FUnleashRecipe& From
        );
        virtual ~FUnleashRecipe() override = default;

        TSharedPtr<FUnleashRecipe> WithName(const TOptional<FString> Name);
        TSharedPtr<FUnleashRecipe> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FUnleashRecipe> WithTargetGroupKeys(const TSharedPtr<TArray<FString>> TargetGroupKeys);
        TSharedPtr<FUnleashRecipe> WithMaterials(const TSharedPtr<TArray<TSharedPtr<FUnleashMaterial>>> Materials);

        TOptional<FString> GetName() const;
        TOptional<FString> GetMetadata() const;
        TSharedPtr<TArray<FString>> GetTargetGroupKeys() const;
        TSharedPtr<TArray<TSharedPtr<FUnleashMaterial>>> GetMaterials() const;


        static TSharedPtr<FUnleashRecipe> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FUnleashRecipe, ESPMode::ThreadSafe> FUnleashRecipePtr;
}