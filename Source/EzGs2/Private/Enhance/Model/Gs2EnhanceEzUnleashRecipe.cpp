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

#include "Enhance/Model/Gs2EnhanceEzUnleashRecipe.h"

namespace Gs2::UE5::Enhance::Model
{

    TSharedPtr<FEzUnleashRecipe> FEzUnleashRecipe::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FEzUnleashRecipe> FEzUnleashRecipe::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FEzUnleashRecipe> FEzUnleashRecipe::WithTargetGroupKeys(
        const TSharedPtr<TArray<FString>> TargetGroupKeys
    )
    {
        this->TargetGroupKeysValue = TargetGroupKeys;
        return SharedThis(this);
    }

    TSharedPtr<FEzUnleashRecipe> FEzUnleashRecipe::WithMaterials(
        const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Enhance::Model::FEzUnleashMaterial>>> Materials
    )
    {
        this->MaterialsValue = Materials;
        return SharedThis(this);
    }
    TOptional<FString> FEzUnleashRecipe::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FEzUnleashRecipe::GetMetadata() const
    {
        return MetadataValue;
    }
    TSharedPtr<TArray<FString>> FEzUnleashRecipe::GetTargetGroupKeys() const
    {
        return TargetGroupKeysValue;
    }
    TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Enhance::Model::FEzUnleashMaterial>>> FEzUnleashRecipe::GetMaterials() const
    {
        return MaterialsValue;
    }

    Gs2::Enhance::Model::FUnleashRecipePtr FEzUnleashRecipe::ToModel() const
    {
        return MakeShared<Gs2::Enhance::Model::FUnleashRecipe>()
            ->WithName(NameValue)
            ->WithMetadata(MetadataValue)
            ->WithTargetGroupKeys(TargetGroupKeysValue)
            ->WithMaterials([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<Gs2::Enhance::Model::FUnleashMaterial>>>();
                    if (MaterialsValue == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *MaterialsValue)
                    {
                        v->Add(v2->ToModel());
                    }
                    return v;
                }()
            );
    }

    TSharedPtr<FEzUnleashRecipe> FEzUnleashRecipe::FromModel(const Gs2::Enhance::Model::FUnleashRecipePtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzUnleashRecipe>()
            ->WithName(Model->GetName())
            ->WithMetadata(Model->GetMetadata())
            ->WithTargetGroupKeys(Model->GetTargetGroupKeys())
            ->WithMaterials([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<FEzUnleashMaterial>>>();
                    if (Model->GetMaterials() == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *Model->GetMaterials())
                    {
                        v->Add(FEzUnleashMaterial::FromModel(v2));
                    }
                    return v;
                }()
            );
    }
}