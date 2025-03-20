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
#include "RankingReward.h"

namespace Gs2::Ranking2::Model
{
    class GS2RANKING2_API FGlobalRankingModel final : public FGs2Object, public TSharedFromThis<FGlobalRankingModel>
    {
        TOptional<FString> GlobalRankingModelIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;
        TOptional<int64> MinimumValueValue;
        TOptional<int64> MaximumValueValue;
        TOptional<bool> SumValue;
        TOptional<FString> OrderDirectionValue;
        TOptional<FString> EntryPeriodEventIdValue;
        TSharedPtr<TArray<TSharedPtr<FRankingReward>>> RankingRewardsValue;
        TOptional<FString> AccessPeriodEventIdValue;
        TOptional<FString> RewardCalculationIndexValue;

    public:
        FGlobalRankingModel();
        FGlobalRankingModel(
            const FGlobalRankingModel& From
        );
        virtual ~FGlobalRankingModel() override = default;

        TSharedPtr<FGlobalRankingModel> WithGlobalRankingModelId(const TOptional<FString> GlobalRankingModelId);
        TSharedPtr<FGlobalRankingModel> WithName(const TOptional<FString> Name);
        TSharedPtr<FGlobalRankingModel> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FGlobalRankingModel> WithMinimumValue(const TOptional<int64> MinimumValue);
        TSharedPtr<FGlobalRankingModel> WithMaximumValue(const TOptional<int64> MaximumValue);
        TSharedPtr<FGlobalRankingModel> WithSum(const TOptional<bool> Sum);
        TSharedPtr<FGlobalRankingModel> WithOrderDirection(const TOptional<FString> OrderDirection);
        TSharedPtr<FGlobalRankingModel> WithEntryPeriodEventId(const TOptional<FString> EntryPeriodEventId);
        TSharedPtr<FGlobalRankingModel> WithRankingRewards(const TSharedPtr<TArray<TSharedPtr<FRankingReward>>> RankingRewards);
        TSharedPtr<FGlobalRankingModel> WithAccessPeriodEventId(const TOptional<FString> AccessPeriodEventId);
        TSharedPtr<FGlobalRankingModel> WithRewardCalculationIndex(const TOptional<FString> RewardCalculationIndex);

        TOptional<FString> GetGlobalRankingModelId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetMetadata() const;
        TOptional<int64> GetMinimumValue() const;
        FString GetMinimumValueString() const;
        TOptional<int64> GetMaximumValue() const;
        FString GetMaximumValueString() const;
        TOptional<bool> GetSum() const;
        FString GetSumString() const;
        TOptional<FString> GetOrderDirection() const;
        TOptional<FString> GetEntryPeriodEventId() const;
        TSharedPtr<TArray<TSharedPtr<FRankingReward>>> GetRankingRewards() const;
        TOptional<FString> GetAccessPeriodEventId() const;
        TOptional<FString> GetRewardCalculationIndex() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetRankingNameFromGrn(const FString Grn);

        static TSharedPtr<FGlobalRankingModel> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FGlobalRankingModel, ESPMode::ThreadSafe> FGlobalRankingModelPtr;
}