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
#include "MegaField/Model/Scope.h"

namespace Gs2::UE5::MegaField::Model
{
	class EZGS2_API FEzScope final : public TSharedFromThis<FEzScope>
	{
        TOptional<float> RValue;
        TOptional<int32> LimitValue;

	public:
        TSharedPtr<FEzScope> WithR(const TOptional<float> R);
        TSharedPtr<FEzScope> WithLimit(const TOptional<int32> Limit);

        TOptional<float> GetR() const;
        FString GetRString() const;

        TOptional<int32> GetLimit() const;
        FString GetLimitString() const;

        Gs2::MegaField::Model::FScopePtr ToModel() const;
        static TSharedPtr<FEzScope> FromModel(Gs2::MegaField::Model::FScopePtr Model);
    };
    typedef TSharedPtr<FEzScope> FEzScopePtr;
}