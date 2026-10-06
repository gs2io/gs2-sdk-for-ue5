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

#include "Enhance/Model/Gs2EnhanceEzUnleashRecipe.h"
#include "Enhance/Model/Gs2EnhanceUnleashMaterial.h"
#include "Gs2EnhanceUnleashRecipe.generated.h"

USTRUCT(BlueprintType)
struct FGs2EnhanceUnleashRecipe
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString Name = "";
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString Metadata = "";
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    TArray<FString> TargetGroupKeys = TArray<FString>();
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    TArray<FGs2EnhanceUnleashMaterial> Materials = TArray<FGs2EnhanceUnleashMaterial>();
};

inline FGs2EnhanceUnleashRecipe EzUnleashRecipeToFGs2EnhanceUnleashRecipe(
    const Gs2::UE5::Enhance::Model::FEzUnleashRecipePtr Model
)
{
    FGs2EnhanceUnleashRecipe Value;
    Value.Name = Model->GetName() ? *Model->GetName() : "";
    Value.Metadata = Model->GetMetadata() ? *Model->GetMetadata() : "";
    Value.TargetGroupKeys = Model->GetTargetGroupKeys() ? [&]
    {
        TArray<FString> r;
        for (auto v : *Model->GetTargetGroupKeys())
        {
            r.Add(v);
        }
        return r;
    }() : TArray<FString>();
    Value.Materials = Model->GetMaterials() ? [&]
    {
        TArray<FGs2EnhanceUnleashMaterial> r;
        for (auto v : *Model->GetMaterials())
        {r.Add(EzUnleashMaterialToFGs2EnhanceUnleashMaterial(v));
        }
        return r;
    }() : TArray<FGs2EnhanceUnleashMaterial>();
    return Value;
}

inline Gs2::UE5::Enhance::Model::FEzUnleashRecipePtr FGs2EnhanceUnleashRecipeToEzUnleashRecipe(
    const FGs2EnhanceUnleashRecipe Model
)
{
    return MakeShared<Gs2::UE5::Enhance::Model::FEzUnleashRecipe>()
        ->WithName(Model.Name)
        ->WithMetadata(Model.Metadata)
        ->WithTargetGroupKeys([&]{
            auto r = MakeShared<TArray<FString>>();
            for (auto v : Model.TargetGroupKeys) {
                r->Add(v);
            }
            return r;
        }())
        ->WithMaterials([&]{
            auto r = MakeShared<TArray<Gs2::UE5::Enhance::Model::FEzUnleashMaterialPtr>>();
            for (auto v : Model.Materials) {
                r->Add(FGs2EnhanceUnleashMaterialToEzUnleashMaterial(v));
            }
            return r;
        }());
}