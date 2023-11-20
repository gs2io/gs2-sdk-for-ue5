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

#include "Enchant/Model/Gs2EnchantEzBalanceParameterModel.h"

namespace Gs2::UE5::Enchant::Model
{

    TSharedPtr<FEzBalanceParameterModel> FEzBalanceParameterModel::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FEzBalanceParameterModel> FEzBalanceParameterModel::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FEzBalanceParameterModel> FEzBalanceParameterModel::WithTotalValue(
        const TOptional<int64> TotalValue
    )
    {
        this->TotalValueValue = TotalValue;
        return SharedThis(this);
    }

    TSharedPtr<FEzBalanceParameterModel> FEzBalanceParameterModel::WithInitialValueStrategy(
        const TOptional<FString> InitialValueStrategy
    )
    {
        this->InitialValueStrategyValue = InitialValueStrategy;
        return SharedThis(this);
    }

    TSharedPtr<FEzBalanceParameterModel> FEzBalanceParameterModel::WithParameters(
        const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Enchant::Model::FEzBalanceParameterValueModel>>> Parameters
    )
    {
        this->ParametersValue = Parameters;
        return SharedThis(this);
    }
    TOptional<FString> FEzBalanceParameterModel::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FEzBalanceParameterModel::GetMetadata() const
    {
        return MetadataValue;
    }
    TOptional<int64> FEzBalanceParameterModel::GetTotalValue() const
    {
        return TotalValueValue;
    }

    FString FEzBalanceParameterModel::GetTotalValueString() const
    {
        if (!TotalValueValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), TotalValueValue.GetValue());
    }
    TOptional<FString> FEzBalanceParameterModel::GetInitialValueStrategy() const
    {
        return InitialValueStrategyValue;
    }
    TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Enchant::Model::FEzBalanceParameterValueModel>>> FEzBalanceParameterModel::GetParameters() const
    {
        return ParametersValue;
    }

    Gs2::Enchant::Model::FBalanceParameterModelPtr FEzBalanceParameterModel::ToModel() const
    {
        return MakeShared<Gs2::Enchant::Model::FBalanceParameterModel>()
            ->WithName(NameValue)
            ->WithMetadata(MetadataValue)
            ->WithTotalValue(TotalValueValue)
            ->WithInitialValueStrategy(InitialValueStrategyValue)
            ->WithParameters([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<Gs2::Enchant::Model::FBalanceParameterValueModel>>>();
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

    TSharedPtr<FEzBalanceParameterModel> FEzBalanceParameterModel::FromModel(const Gs2::Enchant::Model::FBalanceParameterModelPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzBalanceParameterModel>()
            ->WithName(Model->GetName())
            ->WithMetadata(Model->GetMetadata())
            ->WithTotalValue(Model->GetTotalValue())
            ->WithInitialValueStrategy(Model->GetInitialValueStrategy())
            ->WithParameters([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<FEzBalanceParameterValueModel>>>();
                    if (Model->GetParameters() == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *Model->GetParameters())
                    {
                        v->Add(FEzBalanceParameterValueModel::FromModel(v2));
                    }
                    return v;
                }()
            );
    }
}