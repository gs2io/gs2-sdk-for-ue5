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

#include "Enhance/Model/UnleashRateEntryModel.h"

namespace Gs2::Enhance::Model
{
    FUnleashRateEntryModel::FUnleashRateEntryModel():
        GradeValueValue(TOptional<int64>()),
        TypeValue(TOptional<FString>()),
        NeedCountValue(TOptional<int32>()),
        RecipesValue(nullptr)
    {
    }

    FUnleashRateEntryModel::FUnleashRateEntryModel(
        const FUnleashRateEntryModel& From
    ):
        GradeValueValue(From.GradeValueValue),
        TypeValue(From.TypeValue),
        NeedCountValue(From.NeedCountValue),
        RecipesValue(From.RecipesValue)
    {
    }

    TSharedPtr<FUnleashRateEntryModel> FUnleashRateEntryModel::WithGradeValue(
        const TOptional<int64> GradeValue
    )
    {
        this->GradeValueValue = GradeValue;
        return SharedThis(this);
    }

    TSharedPtr<FUnleashRateEntryModel> FUnleashRateEntryModel::WithType(
        const TOptional<FString> Type
    )
    {
        this->TypeValue = Type;
        return SharedThis(this);
    }

    TSharedPtr<FUnleashRateEntryModel> FUnleashRateEntryModel::WithNeedCount(
        const TOptional<int32> NeedCount
    )
    {
        this->NeedCountValue = NeedCount;
        return SharedThis(this);
    }

    TSharedPtr<FUnleashRateEntryModel> FUnleashRateEntryModel::WithRecipes(
        const TSharedPtr<TArray<TSharedPtr<Model::FUnleashRecipe>>> Recipes
    )
    {
        this->RecipesValue = Recipes;
        return SharedThis(this);
    }
    TOptional<int64> FUnleashRateEntryModel::GetGradeValue() const
    {
        return GradeValueValue;
    }

    FString FUnleashRateEntryModel::GetGradeValueString() const
    {
        if (!GradeValueValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), GradeValueValue.GetValue());
    }
    TOptional<FString> FUnleashRateEntryModel::GetType() const
    {
        return TypeValue;
    }
    TOptional<int32> FUnleashRateEntryModel::GetNeedCount() const
    {
        return NeedCountValue;
    }

    FString FUnleashRateEntryModel::GetNeedCountString() const
    {
        if (!NeedCountValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), NeedCountValue.GetValue());
    }
    TSharedPtr<TArray<TSharedPtr<Model::FUnleashRecipe>>> FUnleashRateEntryModel::GetRecipes() const
    {
        return RecipesValue;
    }

    TSharedPtr<FUnleashRateEntryModel> FUnleashRateEntryModel::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FUnleashRateEntryModel>()
            ->WithGradeValue(Data->HasField(ANSI_TO_TCHAR("gradeValue")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("gradeValue"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithType(Data->HasField(ANSI_TO_TCHAR("type")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("type"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithNeedCount(Data->HasField(ANSI_TO_TCHAR("needCount")) ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("needCount"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithRecipes(Data->HasField(ANSI_TO_TCHAR("recipes")) ? [Data]() -> TSharedPtr<TArray<Model::FUnleashRecipePtr>>
                {
                    if (!Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("recipes")))
                    {
                        return nullptr;
                    }
                    auto v = MakeShared<TArray<Model::FUnleashRecipePtr>>();
                    for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("recipes")))
                    {
                        v->Add(Model::FUnleashRecipe::FromJson(JsonObjectValue->AsObject()));
                    }
                    return v;
                 }() : nullptr);
    }

    TSharedPtr<FJsonObject> FUnleashRateEntryModel::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (GradeValueValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("gradeValue"), FString::Printf(TEXT("%lld"), GradeValueValue.GetValue()));
        }
        if (TypeValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("type"), TypeValue.GetValue());
        }
        if (NeedCountValue.IsSet())
        {
            JsonRootObject->SetNumberField(TEXT("needCount"), NeedCountValue.GetValue());
        }
        if (RecipesValue != nullptr && RecipesValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *RecipesValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField(TEXT("recipes"), v);
        }
        return JsonRootObject;
    }

    FString FUnleashRateEntryModel::TypeName = "UnleashRateEntryModel";
}