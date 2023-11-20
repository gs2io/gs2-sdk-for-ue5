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

#include "MegaField/Model/Gs2MegaFieldEzMyPosition.h"

namespace Gs2::UE5::MegaField::Model
{

    TSharedPtr<FEzMyPosition> FEzMyPosition::WithPosition(
        const TSharedPtr<Gs2::UE5::MegaField::Model::FEzPosition> Position
    )
    {
        this->PositionValue = Position;
        return SharedThis(this);
    }

    TSharedPtr<FEzMyPosition> FEzMyPosition::WithVector(
        const TSharedPtr<Gs2::UE5::MegaField::Model::FEzVector> Vector
    )
    {
        this->VectorValue = Vector;
        return SharedThis(this);
    }

    TSharedPtr<FEzMyPosition> FEzMyPosition::WithR(
        const TOptional<float> R
    )
    {
        this->RValue = R;
        return SharedThis(this);
    }
    TSharedPtr<Gs2::UE5::MegaField::Model::FEzPosition> FEzMyPosition::GetPosition() const
    {
        return PositionValue;
    }
    TSharedPtr<Gs2::UE5::MegaField::Model::FEzVector> FEzMyPosition::GetVector() const
    {
        return VectorValue;
    }
    TOptional<float> FEzMyPosition::GetR() const
    {
        return RValue;
    }

    FString FEzMyPosition::GetRString() const
    {
        if (!RValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%f"), RValue.GetValue());
    }

    Gs2::MegaField::Model::FMyPositionPtr FEzMyPosition::ToModel() const
    {
        return MakeShared<Gs2::MegaField::Model::FMyPosition>()
            ->WithPosition(PositionValue == nullptr ? nullptr : PositionValue->ToModel())
            ->WithVector(VectorValue == nullptr ? nullptr : VectorValue->ToModel())
            ->WithR(RValue);
    }

    TSharedPtr<FEzMyPosition> FEzMyPosition::FromModel(const Gs2::MegaField::Model::FMyPositionPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzMyPosition>()
            ->WithPosition(Model->GetPosition() != nullptr ? Gs2::UE5::MegaField::Model::FEzPosition::FromModel(Model->GetPosition()) : nullptr)
            ->WithVector(Model->GetVector() != nullptr ? Gs2::UE5::MegaField::Model::FEzVector::FromModel(Model->GetVector()) : nullptr)
            ->WithR(Model->GetR());
    }
}