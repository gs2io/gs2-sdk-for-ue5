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
#include "MegaField/Model/MyPosition.h"
#include "Gs2MegaFieldEzPosition.h"
#include "Gs2MegaFieldEzVector.h"

namespace Gs2::UE5::MegaField::Model
{
	class EZGS2_API FEzMyPosition final : public TSharedFromThis<FEzMyPosition>
	{
        TSharedPtr<Gs2::UE5::MegaField::Model::FEzPosition> PositionValue;
        TSharedPtr<Gs2::UE5::MegaField::Model::FEzVector> VectorValue;
        TOptional<float> RValue;

	public:
        TSharedPtr<FEzMyPosition> WithPosition(const TSharedPtr<Gs2::UE5::MegaField::Model::FEzPosition> Position);
        TSharedPtr<FEzMyPosition> WithVector(const TSharedPtr<Gs2::UE5::MegaField::Model::FEzVector> Vector);
        TSharedPtr<FEzMyPosition> WithR(const TOptional<float> R);

        TSharedPtr<Gs2::UE5::MegaField::Model::FEzPosition> GetPosition() const;

        TSharedPtr<Gs2::UE5::MegaField::Model::FEzVector> GetVector() const;

        TOptional<float> GetR() const;
        FString GetRString() const;

        Gs2::MegaField::Model::FMyPositionPtr ToModel() const;
        static TSharedPtr<FEzMyPosition> FromModel(Gs2::MegaField::Model::FMyPositionPtr Model);
    };
    typedef TSharedPtr<FEzMyPosition> FEzMyPositionPtr;
}