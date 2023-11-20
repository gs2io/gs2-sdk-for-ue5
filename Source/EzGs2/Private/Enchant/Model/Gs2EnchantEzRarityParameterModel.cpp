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

#include "Enchant/Model/Gs2EnchantEzRarityParameterModel.h"

namespace Gs2::UE5::Enchant::Model
{

    TSharedPtr<FEzRarityParameterModel> FEzRarityParameterModel::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FEzRarityParameterModel> FEzRarityParameterModel::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FEzRarityParameterModel> FEzRarityParameterModel::WithMaximumParameterCount(
        const TOptional<int32> MaximumParameterCount
    )
    {
        this->MaximumParameterCountValue = MaximumParameterCount;
        return SharedThis(this);
    }

    TSharedPtr<FEzRarityParameterModel> FEzRarityParameterModel::WithParameterCounts(
        const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Enchant::Model::FEzRarityParameterCountModel>>> ParameterCounts
    )
    {
        this->ParameterCountsValue = ParameterCounts;
        return SharedThis(this);
    }

    TSharedPtr<FEzRarityParameterModel> FEzRarityParameterModel::WithParameters(
        const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Enchant::Model::FEzRarityParameterValueModel>>> Parameters
    )
    {
        this->ParametersValue = Parameters;
        return SharedThis(this);
    }
    TOptional<FString> FEzRarityParameterModel::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FEzRarityParameterModel::GetMetadata() const
    {
        return MetadataValue;
    }
    TOptional<int32> FEzRarityParameterModel::GetMaximumParameterCount() const
    {
        return MaximumParameterCountValue;
    }

    FString FEzRarityParameterModel::GetMaximumParameterCountString() const
    {
        if (!MaximumParameterCountValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), MaximumParameterCountValue.GetValue());
    }
    TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Enchant::Model::FEzRarityParameterCountModel>>> FEzRarityParameterModel::GetParameterCounts() const
    {
        return ParameterCountsValue;
    }
    TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Enchant::Model::FEzRarityParameterValueModel>>> FEzRarityParameterModel::GetParameters() const
    {
        return ParametersValue;
    }

    Gs2::Enchant::Model::FRarityParameterModelPtr FEzRarityParameterModel::ToModel() const
    {
        return MakeShared<Gs2::Enchant::Model::FRarityParameterModel>()
            ->WithName(NameValue)
            ->WithMetadata(MetadataValue)
            ->WithMaximumParameterCount(MaximumParameterCountValue)
            ->WithParameterCounts([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<Gs2::Enchant::Model::FRarityParameterCountModel>>>();
                    if (ParameterCountsValue == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *ParameterCountsValue)
                    {
                        v->Add(v2->ToModel());
                    }
                    return v;
                }()
            )
            ->WithParameters([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<Gs2::Enchant::Model::FRarityParameterValueModel>>>();
                    if (ParametersValue == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *ParametersValue)
                    {
                        v->Add(v2->ToModel());
                    }
                    return v;
                }()
            );
    }

    TSharedPtr<FEzRarityParameterModel> FEzRarityParameterModel::FromModel(const Gs2::Enchant::Model::FRarityParameterModelPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzRarityParameterModel>()
            ->WithName(Model->GetName())
            ->WithMetadata(Model->GetMetadata())
            ->WithMaximumParameterCount(Model->GetMaximumParameterCount())
            ->WithParameterCounts([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<FEzRarityParameterCountModel>>>();
                    if (Model->GetParameterCounts() == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *Model->GetParameterCounts())
                    {
                        v->Add(FEzRarityParameterCountModel::FromModel(v2));
                    }
                    return v;
                }()
            )
            ->WithParameters([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<FEzRarityParameterValueModel>>>();
                    if (Model->GetParameters() == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *Model->GetParameters())
                    {
                        v->Add(FEzRarityParameterValueModel::FromModel(v2));
                    }
                    return v;
                }()
            );
    }
}