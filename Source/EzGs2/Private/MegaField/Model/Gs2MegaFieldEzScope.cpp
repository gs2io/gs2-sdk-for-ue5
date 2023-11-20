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

#include "MegaField/Model/Gs2MegaFieldEzScope.h"

namespace Gs2::UE5::MegaField::Model
{

    TSharedPtr<FEzScope> FEzScope::WithR(
        const TOptional<float> R
    )
    {
        this->RValue = R;
        return SharedThis(this);
    }

    TSharedPtr<FEzScope> FEzScope::WithLimit(
        const TOptional<int32> Limit
    )
    {
        this->LimitValue = Limit;
        return SharedThis(this);
    }
    TOptional<float> FEzScope::GetR() const
    {
        return RValue;
    }

    FString FEzScope::GetRString() const
    {
        if (!RValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%f"), RValue.GetValue());
    }
    TOptional<int32> FEzScope::GetLimit() const
    {
        return LimitValue;
    }

    FString FEzScope::GetLimitString() const
    {
        if (!LimitValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), LimitValue.GetValue());
    }

    Gs2::MegaField::Model::FScopePtr FEzScope::ToModel() const
    {
        return MakeShared<Gs2::MegaField::Model::FScope>()
            ->WithR(RValue)
            ->WithLimit(LimitValue);
    }

    TSharedPtr<FEzScope> FEzScope::FromModel(const Gs2::MegaField::Model::FScopePtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzScope>()
            ->WithR(Model->GetR())
            ->WithLimit(Model->GetLimit());
    }
}