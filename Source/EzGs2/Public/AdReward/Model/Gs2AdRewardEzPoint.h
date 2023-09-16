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
#include "AdReward/Model/Point.h"

namespace Gs2::UE5::AdReward::Model
{
	class EZGS2_API FEzPoint final : public TSharedFromThis<FEzPoint>
	{
        TOptional<int64> PointValue;

	public:
        TSharedPtr<FEzPoint> WithPoint(const TOptional<int64> Point);

        TOptional<int64> GetPoint() const;
        FString GetPointString() const;

        Gs2::AdReward::Model::FPointPtr ToModel() const;
        static TSharedPtr<FEzPoint> FromModel(Gs2::AdReward::Model::FPointPtr Model);
    };
    typedef TSharedPtr<FEzPoint> FEzPointPtr;
}