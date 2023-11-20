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

#include "Enchant/Model/Gs2EnchantEzBalanceParameterStatus.h"

namespace Gs2::UE5::Enchant::Model
{

    TSharedPtr<FEzBalanceParameterStatus> FEzBalanceParameterStatus::WithParameterName(
        const TOptional<FString> ParameterName
    )
    {
        this->ParameterNameValue = ParameterName;
        return SharedThis(this);
    }

    TSharedPtr<FEzBalanceParameterStatus> FEzBalanceParameterStatus::WithPropertyId(
        const TOptional<FString> PropertyId
    )
    {
        this->PropertyIdValue = PropertyId;
        return SharedThis(this);
    }

    TSharedPtr<FEzBalanceParameterStatus> FEzBalanceParameterStatus::WithParameterValues(
        const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Enchant::Model::FEzBalanceParameterValue>>> ParameterValues
    )
    {
        this->ParameterValuesValue = ParameterValues;
        return SharedThis(this);
    }
    TOptional<FString> FEzBalanceParameterStatus::GetParameterName() const
    {
        return ParameterNameValue;
    }
    TOptional<FString> FEzBalanceParameterStatus::GetPropertyId() const
    {
        return PropertyIdValue;
    }
    TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Enchant::Model::FEzBalanceParameterValue>>> FEzBalanceParameterStatus::GetParameterValues() const
    {
        return ParameterValuesValue;
    }

    Gs2::Enchant::Model::FBalanceParameterStatusPtr FEzBalanceParameterStatus::ToModel() const
    {
        return MakeShared<Gs2::Enchant::Model::FBalanceParameterStatus>()
            ->WithParameterName(ParameterNameValue)
            ->WithPropertyId(PropertyIdValue)
            ->WithParameterValues([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<Gs2::Enchant::Model::FBalanceParameterValue>>>();
                    if (ParameterValuesValue == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *ParameterValuesValue)
                    {
                        v->Add(v2->ToModel());
                    }
                    return v;
                }()
            );
    }

    TSharedPtr<FEzBalanceParameterStatus> FEzBalanceParameterStatus::FromModel(const Gs2::Enchant::Model::FBalanceParameterStatusPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzBalanceParameterStatus>()
            ->WithParameterName(Model->GetParameterName())
            ->WithPropertyId(Model->GetPropertyId())
            ->WithParameterValues([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<FEzBalanceParameterValue>>>();
                    if (Model->GetParameterValues() == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *Model->GetParameterValues())
                    {
                        v->Add(FEzBalanceParameterValue::FromModel(v2));
                    }
                    return v;
                }()
            );
    }
}