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

#include "Enhance/Model/Gs2EnhanceEzUnleashRateEntryModel.h"
#include "Enhance/Model/Gs2EnhanceUnleashRecipe.h"
#include "Gs2EnhanceUnleashRateEntryModel.generated.h"

USTRUCT(BlueprintType)
struct FGs2EnhanceUnleashRateEntryModel
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    int64 GradeValue = 0;
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString Type = "";
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    int32 NeedCount = 0;
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    TArray<FGs2EnhanceUnleashRecipe> Recipes = TArray<FGs2EnhanceUnleashRecipe>();
};

inline FGs2EnhanceUnleashRateEntryModel EzUnleashRateEntryModelToFGs2EnhanceUnleashRateEntryModel(
    const Gs2::UE5::Enhance::Model::FEzUnleashRateEntryModelPtr Model
)
{
    FGs2EnhanceUnleashRateEntryModel Value;
    Value.GradeValue = Model->GetGradeValue() ? *Model->GetGradeValue() : 0;
    Value.Type = Model->GetType() ? *Model->GetType() : "";
    Value.NeedCount = Model->GetNeedCount() ? *Model->GetNeedCount() : 0;
    Value.Recipes = Model->GetRecipes() ? [&]
    {
        TArray<FGs2EnhanceUnleashRecipe> r;
        for (auto v : *Model->GetRecipes())
        {r.Add(EzUnleashRecipeToFGs2EnhanceUnleashRecipe(v));
        }
        return r;
    }() : TArray<FGs2EnhanceUnleashRecipe>();
    return Value;
}

inline Gs2::UE5::Enhance::Model::FEzUnleashRateEntryModelPtr FGs2EnhanceUnleashRateEntryModelToEzUnleashRateEntryModel(
    const FGs2EnhanceUnleashRateEntryModel Model
)
{
    return MakeShared<Gs2::UE5::Enhance::Model::FEzUnleashRateEntryModel>()
        ->WithGradeValue(Model.GradeValue)
        ->WithType(Model.Type)
        ->WithNeedCount(Model.NeedCount)
        ->WithRecipes([&]{
            auto r = MakeShared<TArray<Gs2::UE5::Enhance::Model::FEzUnleashRecipePtr>>();
            for (auto v : Model.Recipes) {
                r->Add(FGs2EnhanceUnleashRecipeToEzUnleashRecipe(v));
            }
            return r;
        }());
}