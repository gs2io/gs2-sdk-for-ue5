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

#include "Enhance/Model/Gs2EnhanceEzUnleashRateEntryModel.h"

namespace Gs2::UE5::Enhance::Model
{

    TSharedPtr<FEzUnleashRateEntryModel> FEzUnleashRateEntryModel::WithGradeValue(
        const TOptional<int64> GradeValue
    )
    {
        this->GradeValueValue = GradeValue;
        return SharedThis(this);
    }

    TSharedPtr<FEzUnleashRateEntryModel> FEzUnleashRateEntryModel::WithType(
        const TOptional<FString> Type
    )
    {
        this->TypeValue = Type;
        return SharedThis(this);
    }

    TSharedPtr<FEzUnleashRateEntryModel> FEzUnleashRateEntryModel::WithNeedCount(
        const TOptional<int32> NeedCount
    )
    {
        this->NeedCountValue = NeedCount;
        return SharedThis(this);
    }

    TSharedPtr<FEzUnleashRateEntryModel> FEzUnleashRateEntryModel::WithRecipes(
        const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Enhance::Model::FEzUnleashRecipe>>> Recipes
    )
    {
        this->RecipesValue = Recipes;
        return SharedThis(this);
    }
    TOptional<int64> FEzUnleashRateEntryModel::GetGradeValue() const
    {
        return GradeValueValue;
    }

    FString FEzUnleashRateEntryModel::GetGradeValueString() const
    {
        if (!GradeValueValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), GradeValueValue.GetValue());
    }
    TOptional<FString> FEzUnleashRateEntryModel::GetType() const
    {
        return TypeValue;
    }
    TOptional<int32> FEzUnleashRateEntryModel::GetNeedCount() const
    {
        return NeedCountValue;
    }

    FString FEzUnleashRateEntryModel::GetNeedCountString() const
    {
        if (!NeedCountValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), NeedCountValue.GetValue());
    }
    TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Enhance::Model::FEzUnleashRecipe>>> FEzUnleashRateEntryModel::GetRecipes() const
    {
        return RecipesValue;
    }

    Gs2::Enhance::Model::FUnleashRateEntryModelPtr FEzUnleashRateEntryModel::ToModel() const
    {
        return MakeShared<Gs2::Enhance::Model::FUnleashRateEntryModel>()
            ->WithGradeValue(GradeValueValue)
            ->WithType(TypeValue)
            ->WithNeedCount(NeedCountValue)
            ->WithRecipes([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<Gs2::Enhance::Model::FUnleashRecipe>>>();
                    if (RecipesValue == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *RecipesValue)
                    {
                        v->Add(v2->ToModel());
                    }
                    return v;
                }()
            );
    }

    TSharedPtr<FEzUnleashRateEntryModel> FEzUnleashRateEntryModel::FromModel(const Gs2::Enhance::Model::FUnleashRateEntryModelPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzUnleashRateEntryModel>()
            ->WithGradeValue(Model->GetGradeValue())
            ->WithType(Model->GetType())
            ->WithNeedCount(Model->GetNeedCount())
            ->WithRecipes([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<FEzUnleashRecipe>>>();
                    if (Model->GetRecipes() == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *Model->GetRecipes())
                    {
                        v->Add(FEzUnleashRecipe::FromModel(v2));
                    }
                    return v;
                }()
            );
    }
}