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
#include "SeasonRating/Model/TierModel.h"

namespace Gs2::UE5::SeasonRating::Model
{
	class EZGS2_API FEzTierModel final : public TSharedFromThis<FEzTierModel>
	{
        TOptional<FString> MetadataValue;
        TOptional<int32> RaiseRankBonusValue;
        TOptional<int32> MinimumChangePointValue;
        TOptional<int32> MaximumChangePointValue;

	public:
        TSharedPtr<FEzTierModel> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FEzTierModel> WithRaiseRankBonus(const TOptional<int32> RaiseRankBonus);
        TSharedPtr<FEzTierModel> WithMinimumChangePoint(const TOptional<int32> MinimumChangePoint);
        TSharedPtr<FEzTierModel> WithMaximumChangePoint(const TOptional<int32> MaximumChangePoint);

        TOptional<FString> GetMetadata() const;

        TOptional<int32> GetRaiseRankBonus() const;
        FString GetRaiseRankBonusString() const;

        TOptional<int32> GetMinimumChangePoint() const;
        FString GetMinimumChangePointString() const;

        TOptional<int32> GetMaximumChangePoint() const;
        FString GetMaximumChangePointString() const;

        Gs2::SeasonRating::Model::FTierModelPtr ToModel() const;
        static TSharedPtr<FEzTierModel> FromModel(Gs2::SeasonRating::Model::FTierModelPtr Model);
    };
    typedef TSharedPtr<FEzTierModel> FEzTierModelPtr;
}