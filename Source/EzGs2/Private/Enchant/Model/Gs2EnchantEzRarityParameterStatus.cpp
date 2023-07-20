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

#include "EzGs2/Public/Enchant/Model/Gs2EnchantEzRarityParameterStatus.h"

namespace Gs2::UE5::Enchant::Model
{

    TSharedPtr<FEzRarityParameterStatus> FEzRarityParameterStatus::WithParameterName(
        const TOptional<FString> ParameterName
    )
    {
        this->ParameterNameValue = ParameterName;
        return SharedThis(this);
    }

    TSharedPtr<FEzRarityParameterStatus> FEzRarityParameterStatus::WithPropertyId(
        const TOptional<FString> PropertyId
    )
    {
        this->PropertyIdValue = PropertyId;
        return SharedThis(this);
    }

    TSharedPtr<FEzRarityParameterStatus> FEzRarityParameterStatus::WithParameterValues(
        const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Enchant::Model::FEzRarityParameterValue>>> ParameterValues
    )
    {
        this->ParameterValuesValue = ParameterValues;
        return SharedThis(this);
    }
    TOptional<FString> FEzRarityParameterStatus::GetParameterName() const
    {
        return ParameterNameValue;
    }
    TOptional<FString> FEzRarityParameterStatus::GetPropertyId() const
    {
        return PropertyIdValue;
    }
    TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Enchant::Model::FEzRarityParameterValue>>> FEzRarityParameterStatus::GetParameterValues() const
    {
        return ParameterValuesValue;
    }

    Gs2::Enchant::Model::FRarityParameterStatusPtr FEzRarityParameterStatus::ToModel() const
    {
        return MakeShared<Gs2::Enchant::Model::FRarityParameterStatus>()
            ->WithParameterName(ParameterNameValue)
            ->WithPropertyId(PropertyIdValue)
            ->WithParameterValues([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<Gs2::Enchant::Model::FRarityParameterValue>>>();
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

    TSharedPtr<FEzRarityParameterStatus> FEzRarityParameterStatus::FromModel(const Gs2::Enchant::Model::FRarityParameterStatusPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzRarityParameterStatus>()
            ->WithParameterName(Model->GetParameterName())
            ->WithPropertyId(Model->GetPropertyId())
            ->WithParameterValues([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<FEzRarityParameterValue>>>();
                    if (Model->GetParameterValues() == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *Model->GetParameterValues())
                    {
                        v->Add(FEzRarityParameterValue::FromModel(v2));
                    }
                    return v;
                }()
            );
    }
}