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

#include "EzGs2/Public/Enchant/Model/Gs2EnchantEzRarityParameterCountModel.h"

namespace Gs2::UE5::Enchant::Model
{

    TSharedPtr<FEzRarityParameterCountModel> FEzRarityParameterCountModel::WithCount(
        const TOptional<int32> Count
    )
    {
        this->CountValue = Count;
        return SharedThis(this);
    }

    TSharedPtr<FEzRarityParameterCountModel> FEzRarityParameterCountModel::WithWeight(
        const TOptional<int32> Weight
    )
    {
        this->WeightValue = Weight;
        return SharedThis(this);
    }
    TOptional<int32> FEzRarityParameterCountModel::GetCount() const
    {
        return CountValue;
    }

    FString FEzRarityParameterCountModel::GetCountString() const
    {
        if (!CountValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), CountValue.GetValue());
    }
    TOptional<int32> FEzRarityParameterCountModel::GetWeight() const
    {
        return WeightValue;
    }

    FString FEzRarityParameterCountModel::GetWeightString() const
    {
        if (!WeightValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), WeightValue.GetValue());
    }

    Gs2::Enchant::Model::FRarityParameterCountModelPtr FEzRarityParameterCountModel::ToModel() const
    {
        return MakeShared<Gs2::Enchant::Model::FRarityParameterCountModel>()
            ->WithCount(CountValue)
            ->WithWeight(WeightValue);
    }

    TSharedPtr<FEzRarityParameterCountModel> FEzRarityParameterCountModel::FromModel(const Gs2::Enchant::Model::FRarityParameterCountModelPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzRarityParameterCountModel>()
            ->WithCount(Model->GetCount())
            ->WithWeight(Model->GetWeight());
    }
}