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

#include "EzGs2/Public/Enchant/Model/Gs2EnchantEzBalanceParameterValue.h"

namespace Gs2::UE5::Enchant::Model
{

    TSharedPtr<FEzBalanceParameterValue> FEzBalanceParameterValue::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FEzBalanceParameterValue> FEzBalanceParameterValue::WithValue(
        const TOptional<int64> Value
    )
    {
        this->ValueValue = Value;
        return SharedThis(this);
    }
    TOptional<FString> FEzBalanceParameterValue::GetName() const
    {
        return NameValue;
    }
    TOptional<int64> FEzBalanceParameterValue::GetValue() const
    {
        return ValueValue;
    }

    FString FEzBalanceParameterValue::GetValueString() const
    {
        if (!ValueValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), ValueValue.GetValue());
    }

    Gs2::Enchant::Model::FBalanceParameterValuePtr FEzBalanceParameterValue::ToModel() const
    {
        return MakeShared<Gs2::Enchant::Model::FBalanceParameterValue>()
            ->WithName(NameValue)
            ->WithValue(ValueValue);
    }

    TSharedPtr<FEzBalanceParameterValue> FEzBalanceParameterValue::FromModel(const Gs2::Enchant::Model::FBalanceParameterValuePtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzBalanceParameterValue>()
            ->WithName(Model->GetName())
            ->WithValue(Model->GetValue());
    }
}