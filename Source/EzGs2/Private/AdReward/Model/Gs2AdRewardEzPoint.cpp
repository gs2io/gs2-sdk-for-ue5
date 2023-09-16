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

#include "EzGs2/Public/AdReward/Model/Gs2AdRewardEzPoint.h"

namespace Gs2::UE5::AdReward::Model
{

    TSharedPtr<FEzPoint> FEzPoint::WithPoint(
        const TOptional<int64> Point
    )
    {
        this->PointValue = Point;
        return SharedThis(this);
    }
    TOptional<int64> FEzPoint::GetPoint() const
    {
        return PointValue;
    }

    FString FEzPoint::GetPointString() const
    {
        if (!PointValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), PointValue.GetValue());
    }

    Gs2::AdReward::Model::FPointPtr FEzPoint::ToModel() const
    {
        return MakeShared<Gs2::AdReward::Model::FPoint>()
            ->WithPoint(PointValue);
    }

    TSharedPtr<FEzPoint> FEzPoint::FromModel(const Gs2::AdReward::Model::FPointPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzPoint>()
            ->WithPoint(Model->GetPoint());
    }
}