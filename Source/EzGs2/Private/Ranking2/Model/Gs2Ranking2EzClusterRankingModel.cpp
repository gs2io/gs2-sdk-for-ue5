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

#include "Ranking2/Model/Gs2Ranking2EzClusterRankingModel.h"

namespace Gs2::UE5::Ranking2::Model
{

    TSharedPtr<FEzClusterRankingModel> FEzClusterRankingModel::WithClusterRankingModelId(
        const TOptional<FString> ClusterRankingModelId
    )
    {
        this->ClusterRankingModelIdValue = ClusterRankingModelId;
        return SharedThis(this);
    }

    TSharedPtr<FEzClusterRankingModel> FEzClusterRankingModel::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FEzClusterRankingModel> FEzClusterRankingModel::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FEzClusterRankingModel> FEzClusterRankingModel::WithMinimumValue(
        const TOptional<int64> MinimumValue
    )
    {
        this->MinimumValueValue = MinimumValue;
        return SharedThis(this);
    }

    TSharedPtr<FEzClusterRankingModel> FEzClusterRankingModel::WithMaximumValue(
        const TOptional<int64> MaximumValue
    )
    {
        this->MaximumValueValue = MaximumValue;
        return SharedThis(this);
    }

    TSharedPtr<FEzClusterRankingModel> FEzClusterRankingModel::WithSum(
        const TOptional<bool> Sum
    )
    {
        this->SumValue = Sum;
        return SharedThis(this);
    }

    TSharedPtr<FEzClusterRankingModel> FEzClusterRankingModel::WithOrderDirection(
        const TOptional<FString> OrderDirection
    )
    {
        this->OrderDirectionValue = OrderDirection;
        return SharedThis(this);
    }

    TSharedPtr<FEzClusterRankingModel> FEzClusterRankingModel::WithClusterType(
        const TOptional<FString> ClusterType
    )
    {
        this->ClusterTypeValue = ClusterType;
        return SharedThis(this);
    }

    TSharedPtr<FEzClusterRankingModel> FEzClusterRankingModel::WithRankingRewards(
        const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Ranking2::Model::FEzRankingReward>>> RankingRewards
    )
    {
        this->RankingRewardsValue = RankingRewards;
        return SharedThis(this);
    }

    TSharedPtr<FEzClusterRankingModel> FEzClusterRankingModel::WithEntryPeriodEventId(
        const TOptional<FString> EntryPeriodEventId
    )
    {
        this->EntryPeriodEventIdValue = EntryPeriodEventId;
        return SharedThis(this);
    }

    TSharedPtr<FEzClusterRankingModel> FEzClusterRankingModel::WithAccessPeriodEventId(
        const TOptional<FString> AccessPeriodEventId
    )
    {
        this->AccessPeriodEventIdValue = AccessPeriodEventId;
        return SharedThis(this);
    }
    TOptional<FString> FEzClusterRankingModel::GetClusterRankingModelId() const
    {
        return ClusterRankingModelIdValue;
    }
    TOptional<FString> FEzClusterRankingModel::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FEzClusterRankingModel::GetMetadata() const
    {
        return MetadataValue;
    }
    TOptional<int64> FEzClusterRankingModel::GetMinimumValue() const
    {
        return MinimumValueValue;
    }

    FString FEzClusterRankingModel::GetMinimumValueString() const
    {
        if (!MinimumValueValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), MinimumValueValue.GetValue());
    }
    TOptional<int64> FEzClusterRankingModel::GetMaximumValue() const
    {
        return MaximumValueValue;
    }

    FString FEzClusterRankingModel::GetMaximumValueString() const
    {
        if (!MaximumValueValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), MaximumValueValue.GetValue());
    }
    TOptional<bool> FEzClusterRankingModel::GetSum() const
    {
        return SumValue;
    }

    FString FEzClusterRankingModel::GetSumString() const
    {
        if (!SumValue.IsSet())
        {
            return FString("null");
        }
        return FString(SumValue.GetValue() ? "true" : "false");
    }
    TOptional<FString> FEzClusterRankingModel::GetOrderDirection() const
    {
        return OrderDirectionValue;
    }
    TOptional<FString> FEzClusterRankingModel::GetClusterType() const
    {
        return ClusterTypeValue;
    }
    TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Ranking2::Model::FEzRankingReward>>> FEzClusterRankingModel::GetRankingRewards() const
    {
        return RankingRewardsValue;
    }
    TOptional<FString> FEzClusterRankingModel::GetEntryPeriodEventId() const
    {
        return EntryPeriodEventIdValue;
    }
    TOptional<FString> FEzClusterRankingModel::GetAccessPeriodEventId() const
    {
        return AccessPeriodEventIdValue;
    }

    Gs2::Ranking2::Model::FClusterRankingModelPtr FEzClusterRankingModel::ToModel() const
    {
        return MakeShared<Gs2::Ranking2::Model::FClusterRankingModel>()
            ->WithClusterRankingModelId(ClusterRankingModelIdValue)
            ->WithName(NameValue)
            ->WithMetadata(MetadataValue)
            ->WithMinimumValue(MinimumValueValue)
            ->WithMaximumValue(MaximumValueValue)
            ->WithSum(SumValue)
            ->WithOrderDirection(OrderDirectionValue)
            ->WithClusterType(ClusterTypeValue)
            ->WithRankingRewards([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<Gs2::Ranking2::Model::FRankingReward>>>();
                    if (RankingRewardsValue == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *RankingRewardsValue)
                    {
                        v->Add(v2->ToModel());
                    }
                    return v;
                }()
            )
            ->WithEntryPeriodEventId(EntryPeriodEventIdValue)
            ->WithAccessPeriodEventId(AccessPeriodEventIdValue);
    }

    TSharedPtr<FEzClusterRankingModel> FEzClusterRankingModel::FromModel(const Gs2::Ranking2::Model::FClusterRankingModelPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzClusterRankingModel>()
            ->WithClusterRankingModelId(Model->GetClusterRankingModelId())
            ->WithName(Model->GetName())
            ->WithMetadata(Model->GetMetadata())
            ->WithMinimumValue(Model->GetMinimumValue())
            ->WithMaximumValue(Model->GetMaximumValue())
            ->WithSum(Model->GetSum())
            ->WithOrderDirection(Model->GetOrderDirection())
            ->WithClusterType(Model->GetClusterType())
            ->WithRankingRewards([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<FEzRankingReward>>>();
                    if (Model->GetRankingRewards() == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *Model->GetRankingRewards())
                    {
                        v->Add(FEzRankingReward::FromModel(v2));
                    }
                    return v;
                }()
            )
            ->WithEntryPeriodEventId(Model->GetEntryPeriodEventId())
            ->WithAccessPeriodEventId(Model->GetAccessPeriodEventId());
    }
}