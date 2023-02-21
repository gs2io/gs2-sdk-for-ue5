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

#pragma once

#include "CoreMinimal.h"
#include "MegaField/Model/Spatial.h"
#include "Gs2MegaFieldEzPosition.h"
#include "Gs2MegaFieldEzVector.h"

namespace Gs2::UE5::MegaField::Model
{
	class EZGS2_API FEzSpatial final : public TSharedFromThis<FEzSpatial>
	{
        TOptional<FString> UserIdValue;
        TOptional<FString> AreaModelNameValue;
        TOptional<FString> LayerModelNameValue;
        TSharedPtr<Gs2::UE5::MegaField::Model::FEzPosition> PositionValue;
        TSharedPtr<Gs2::UE5::MegaField::Model::FEzVector> VectorValue;

	public:
        TSharedPtr<FEzSpatial> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FEzSpatial> WithAreaModelName(const TOptional<FString> AreaModelName);
        TSharedPtr<FEzSpatial> WithLayerModelName(const TOptional<FString> LayerModelName);
        TSharedPtr<FEzSpatial> WithPosition(const TSharedPtr<Gs2::UE5::MegaField::Model::FEzPosition> Position);
        TSharedPtr<FEzSpatial> WithVector(const TSharedPtr<Gs2::UE5::MegaField::Model::FEzVector> Vector);

        TOptional<FString> GetUserId() const;

        TOptional<FString> GetAreaModelName() const;

        TOptional<FString> GetLayerModelName() const;

        TSharedPtr<Gs2::UE5::MegaField::Model::FEzPosition> GetPosition() const;

        TSharedPtr<Gs2::UE5::MegaField::Model::FEzVector> GetVector() const;

        Gs2::MegaField::Model::FSpatialPtr ToModel() const;
        static TSharedPtr<FEzSpatial> FromModel(Gs2::MegaField::Model::FSpatialPtr Model);
    };
    typedef TSharedPtr<FEzSpatial> FEzSpatialPtr;
}