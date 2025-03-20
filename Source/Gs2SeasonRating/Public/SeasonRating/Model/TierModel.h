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
#include "Core/Gs2Object.h"

namespace Gs2::SeasonRating::Model
{
    class GS2SEASONRATING_API FTierModel final : public FGs2Object, public TSharedFromThis<FTierModel>
    {
        TOptional<FString> MetadataValue;
        TOptional<int32> RaiseRankBonusValue;
        TOptional<int32> EntryFeeValue;
        TOptional<int32> MinimumChangePointValue;
        TOptional<int32> MaximumChangePointValue;

    public:
        FTierModel();
        FTierModel(
            const FTierModel& From
        );
        virtual ~FTierModel() override = default;

        TSharedPtr<FTierModel> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FTierModel> WithRaiseRankBonus(const TOptional<int32> RaiseRankBonus);
        TSharedPtr<FTierModel> WithEntryFee(const TOptional<int32> EntryFee);
        TSharedPtr<FTierModel> WithMinimumChangePoint(const TOptional<int32> MinimumChangePoint);
        TSharedPtr<FTierModel> WithMaximumChangePoint(const TOptional<int32> MaximumChangePoint);

        TOptional<FString> GetMetadata() const;
        TOptional<int32> GetRaiseRankBonus() const;
        FString GetRaiseRankBonusString() const;
        TOptional<int32> GetEntryFee() const;
        FString GetEntryFeeString() const;
        TOptional<int32> GetMinimumChangePoint() const;
        FString GetMinimumChangePointString() const;
        TOptional<int32> GetMaximumChangePoint() const;
        FString GetMaximumChangePointString() const;


        static TSharedPtr<FTierModel> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FTierModel, ESPMode::ThreadSafe> FTierModelPtr;
}