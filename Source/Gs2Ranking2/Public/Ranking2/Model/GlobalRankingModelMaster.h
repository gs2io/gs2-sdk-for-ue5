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
    class GS2RANKING2_API FGlobalRankingModelMaster final : public FGs2Object, public TSharedFromThis<FGlobalRankingModelMaster>
    {
        TOptional<FString> GlobalRankingModelIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        TOptional<int64> MinimumValueValue;
        TOptional<int64> MaximumValueValue;
        TOptional<bool> SumValue;
        TOptional<FString> OrderDirectionValue;
        TOptional<FString> EntryPeriodEventIdValue;
        TSharedPtr<TArray<TSharedPtr<FRankingReward>>> RankingRewardsValue;
        TOptional<FString> AccessPeriodEventIdValue;
        TOptional<FString> RewardCalculationIndexValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> UpdatedAtValue;
        TOptional<int64> RevisionValue;

    public:
        FGlobalRankingModelMaster();
        FGlobalRankingModelMaster(
            const FGlobalRankingModelMaster& From
        );
        virtual ~FGlobalRankingModelMaster() override = default;

        TSharedPtr<FGlobalRankingModelMaster> WithGlobalRankingModelId(const TOptional<FString> GlobalRankingModelId);
        TSharedPtr<FGlobalRankingModelMaster> WithName(const TOptional<FString> Name);
        TSharedPtr<FGlobalRankingModelMaster> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FGlobalRankingModelMaster> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FGlobalRankingModelMaster> WithMinimumValue(const TOptional<int64> MinimumValue);
        TSharedPtr<FGlobalRankingModelMaster> WithMaximumValue(const TOptional<int64> MaximumValue);
        TSharedPtr<FGlobalRankingModelMaster> WithSum(const TOptional<bool> Sum);
        TSharedPtr<FGlobalRankingModelMaster> WithOrderDirection(const TOptional<FString> OrderDirection);
        TSharedPtr<FGlobalRankingModelMaster> WithEntryPeriodEventId(const TOptional<FString> EntryPeriodEventId);
        TSharedPtr<FGlobalRankingModelMaster> WithRankingRewards(const TSharedPtr<TArray<TSharedPtr<FRankingReward>>> RankingRewards);
        TSharedPtr<FGlobalRankingModelMaster> WithAccessPeriodEventId(const TOptional<FString> AccessPeriodEventId);
        TSharedPtr<FGlobalRankingModelMaster> WithRewardCalculationIndex(const TOptional<FString> RewardCalculationIndex);
        TSharedPtr<FGlobalRankingModelMaster> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FGlobalRankingModelMaster> WithUpdatedAt(const TOptional<int64> UpdatedAt);
        TSharedPtr<FGlobalRankingModelMaster> WithRevision(const TOptional<int64> Revision);

        TOptional<FString> GetGlobalRankingModelId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetDescription() const;
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
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;
        TOptional<int64> GetUpdatedAt() const;
        FString GetUpdatedAtString() const;
        TOptional<int64> GetRevision() const;
        FString GetRevisionString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetRankingNameFromGrn(const FString Grn);

        static TSharedPtr<FGlobalRankingModelMaster> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FGlobalRankingModelMaster, ESPMode::ThreadSafe> FGlobalRankingModelMasterPtr;
}