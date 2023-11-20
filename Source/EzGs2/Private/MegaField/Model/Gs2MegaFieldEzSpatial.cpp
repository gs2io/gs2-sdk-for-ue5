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

#include "MegaField/Model/Gs2MegaFieldEzSpatial.h"

namespace Gs2::UE5::MegaField::Model
{

    TSharedPtr<FEzSpatial> FEzSpatial::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FEzSpatial> FEzSpatial::WithAreaModelName(
        const TOptional<FString> AreaModelName
    )
    {
        this->AreaModelNameValue = AreaModelName;
        return SharedThis(this);
    }

    TSharedPtr<FEzSpatial> FEzSpatial::WithLayerModelName(
        const TOptional<FString> LayerModelName
    )
    {
        this->LayerModelNameValue = LayerModelName;
        return SharedThis(this);
    }

    TSharedPtr<FEzSpatial> FEzSpatial::WithPosition(
        const TSharedPtr<Gs2::UE5::MegaField::Model::FEzPosition> Position
    )
    {
        this->PositionValue = Position;
        return SharedThis(this);
    }

    TSharedPtr<FEzSpatial> FEzSpatial::WithVector(
        const TSharedPtr<Gs2::UE5::MegaField::Model::FEzVector> Vector
    )
    {
        this->VectorValue = Vector;
        return SharedThis(this);
    }
    TOptional<FString> FEzSpatial::GetUserId() const
    {
        return UserIdValue;
    }
    TOptional<FString> FEzSpatial::GetAreaModelName() const
    {
        return AreaModelNameValue;
    }
    TOptional<FString> FEzSpatial::GetLayerModelName() const
    {
        return LayerModelNameValue;
    }
    TSharedPtr<Gs2::UE5::MegaField::Model::FEzPosition> FEzSpatial::GetPosition() const
    {
        return PositionValue;
    }
    TSharedPtr<Gs2::UE5::MegaField::Model::FEzVector> FEzSpatial::GetVector() const
    {
        return VectorValue;
    }

    Gs2::MegaField::Model::FSpatialPtr FEzSpatial::ToModel() const
    {
        return MakeShared<Gs2::MegaField::Model::FSpatial>()
            ->WithUserId(UserIdValue)
            ->WithAreaModelName(AreaModelNameValue)
            ->WithLayerModelName(LayerModelNameValue)
            ->WithPosition(PositionValue == nullptr ? nullptr : PositionValue->ToModel())
            ->WithVector(VectorValue == nullptr ? nullptr : VectorValue->ToModel());
    }

    TSharedPtr<FEzSpatial> FEzSpatial::FromModel(const Gs2::MegaField::Model::FSpatialPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzSpatial>()
            ->WithUserId(Model->GetUserId())
            ->WithAreaModelName(Model->GetAreaModelName())
            ->WithLayerModelName(Model->GetLayerModelName())
            ->WithPosition(Model->GetPosition() != nullptr ? Gs2::UE5::MegaField::Model::FEzPosition::FromModel(Model->GetPosition()) : nullptr)
            ->WithVector(Model->GetVector() != nullptr ? Gs2::UE5::MegaField::Model::FEzVector::FromModel(Model->GetVector()) : nullptr);
    }
}