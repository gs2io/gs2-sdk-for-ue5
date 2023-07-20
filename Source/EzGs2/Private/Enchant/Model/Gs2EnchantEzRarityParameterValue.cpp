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

#include "EzGs2/Public/Enchant/Model/Gs2EnchantEzRarityParameterValue.h"

namespace Gs2::UE5::Enchant::Model
{

    TSharedPtr<FEzRarityParameterValue> FEzRarityParameterValue::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FEzRarityParameterValue> FEzRarityParameterValue::WithResourceName(
        const TOptional<FString> ResourceName
    )
    {
        this->ResourceNameValue = ResourceName;
        return SharedThis(this);
    }

    TSharedPtr<FEzRarityParameterValue> FEzRarityParameterValue::WithResourceValue(
        const TOptional<int64> ResourceValue
    )
    {
        this->ResourceValueValue = ResourceValue;
        return SharedThis(this);
    }
    TOptional<FString> FEzRarityParameterValue::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FEzRarityParameterValue::GetResourceName() const
    {
        return ResourceNameValue;
    }
    TOptional<int64> FEzRarityParameterValue::GetResourceValue() const
    {
        return ResourceValueValue;
    }

    FString FEzRarityParameterValue::GetResourceValueString() const
    {
        if (!ResourceValueValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), ResourceValueValue.GetValue());
    }

    Gs2::Enchant::Model::FRarityParameterValuePtr FEzRarityParameterValue::ToModel() const
    {
        return MakeShared<Gs2::Enchant::Model::FRarityParameterValue>()
            ->WithName(NameValue)
            ->WithResourceName(ResourceNameValue)
            ->WithResourceValue(ResourceValueValue);
    }

    TSharedPtr<FEzRarityParameterValue> FEzRarityParameterValue::FromModel(const Gs2::Enchant::Model::FRarityParameterValuePtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzRarityParameterValue>()
            ->WithName(Model->GetName())
            ->WithResourceName(Model->GetResourceName())
            ->WithResourceValue(Model->GetResourceValue());
    }
}