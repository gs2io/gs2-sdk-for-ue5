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
#include "MegaField/Model/Vector.h"

namespace Gs2::UE5::MegaField::Model
{
	class EZGS2_API FEzVector final : public TSharedFromThis<FEzVector>
	{
        TOptional<float> XValue;
        TOptional<float> YValue;
        TOptional<float> ZValue;

	public:
        TSharedPtr<FEzVector> WithX(const TOptional<float> X);
        TSharedPtr<FEzVector> WithY(const TOptional<float> Y);
        TSharedPtr<FEzVector> WithZ(const TOptional<float> Z);

        TOptional<float> GetX() const;
        FString GetXString() const;

        TOptional<float> GetY() const;
        FString GetYString() const;

        TOptional<float> GetZ() const;
        FString GetZString() const;

        Gs2::MegaField::Model::FVectorPtr ToModel() const;
        static TSharedPtr<FEzVector> FromModel(Gs2::MegaField::Model::FVectorPtr Model);
    };
    typedef TSharedPtr<FEzVector> FEzVectorPtr;
}