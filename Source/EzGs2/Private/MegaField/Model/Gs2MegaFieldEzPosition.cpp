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

#include "MegaField/Model/Gs2MegaFieldEzPosition.h"

namespace Gs2::UE5::MegaField::Model
{

    TSharedPtr<FEzPosition> FEzPosition::WithX(
        const TOptional<float> X
    )
    {
        this->XValue = X;
        return SharedThis(this);
    }

    TSharedPtr<FEzPosition> FEzPosition::WithY(
        const TOptional<float> Y
    )
    {
        this->YValue = Y;
        return SharedThis(this);
    }

    TSharedPtr<FEzPosition> FEzPosition::WithZ(
        const TOptional<float> Z
    )
    {
        this->ZValue = Z;
        return SharedThis(this);
    }
    TOptional<float> FEzPosition::GetX() const
    {
        return XValue;
    }

    FString FEzPosition::GetXString() const
    {
        if (!XValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%f"), XValue.GetValue());
    }
    TOptional<float> FEzPosition::GetY() const
    {
        return YValue;
    }

    FString FEzPosition::GetYString() const
    {
        if (!YValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%f"), YValue.GetValue());
    }
    TOptional<float> FEzPosition::GetZ() const
    {
        return ZValue;
    }

    FString FEzPosition::GetZString() const
    {
        if (!ZValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%f"), ZValue.GetValue());
    }

    Gs2::MegaField::Model::FPositionPtr FEzPosition::ToModel() const
    {
        return MakeShared<Gs2::MegaField::Model::FPosition>()
            ->WithX(XValue)
            ->WithY(YValue)
            ->WithZ(ZValue);
    }

    TSharedPtr<FEzPosition> FEzPosition::FromModel(const Gs2::MegaField::Model::FPositionPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzPosition>()
            ->WithX(Model->GetX())
            ->WithY(Model->GetY())
            ->WithZ(Model->GetZ());
    }
}