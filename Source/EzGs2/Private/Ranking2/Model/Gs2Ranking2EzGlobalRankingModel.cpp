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

#include "Ranking2/Model/Gs2Ranking2EzGlobalRankingModel.h"

namespace Gs2::UE5::Ranking2::Model
{

    TSharedPtr<FEzGlobalRankingModel> FEzGlobalRankingModel::WithGlobalRankingModelId(
        const TOptional<FString> GlobalRankingModelId
    )
    {
        this->GlobalRankingModelIdValue = GlobalRankingModelId;
        return SharedThis(this);
    }

    TSharedPtr<FEzGlobalRankingModel> FEzGlobalRankingModel::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FEzGlobalRankingModel> FEzGlobalRankingModel::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FEzGlobalRankingModel> FEzGlobalRankingModel::WithMinimumValue(
        const TOptional<int64> MinimumValue
    )
    {
        this->MinimumValueValue = MinimumValue;
        return SharedThis(this);
    }

    TSharedPtr<FEzGlobalRankingModel> FEzGlobalRankingModel::WithMaximumValue(
        const TOptional<int64> MaximumValue
    )
    {
        this->MaximumValueValue = MaximumValue;
        return SharedThis(this);
    }

    TSharedPtr<FEzGlobalRankingModel> FEzGlobalRankingModel::WithSum(
        const TOptional<bool> Sum
    )
    {
        this->SumValue = Sum;
        return SharedThis(this);
    }

    TSharedPtr<FEzGlobalRankingModel> FEzGlobalRankingModel::WithOrderDirection(
        const TOptional<FString> OrderDirection
    )
    {
        this->OrderDirectionValue = OrderDirection;
        return SharedThis(this);
    }

    TSharedPtr<FEzGlobalRankingModel> FEzGlobalRankingModel::WithRankingRewards(
        const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Ranking2::Model::FEzRankingReward>>> RankingRewards
    )
    {
        this->RankingRewardsValue = RankingRewards;
        return SharedThis(this);
    }

    TSharedPtr<FEzGlobalRankingModel> FEzGlobalRankingModel::WithEntryPeriodEventId(
        const TOptional<FString> EntryPeriodEventId
    )
    {
        this->EntryPeriodEventIdValue = EntryPeriodEventId;
        return SharedThis(this);
    }

    TSharedPtr<FEzGlobalRankingModel> FEzGlobalRankingModel::WithAccessPeriodEventId(
        const TOptional<FString> AccessPeriodEventId
    )
    {
        this->AccessPeriodEventIdValue = AccessPeriodEventId;
        return SharedThis(this);
    }
    TOptional<FString> FEzGlobalRankingModel::GetGlobalRankingModelId() const
    {
        return GlobalRankingModelIdValue;
    }
    TOptional<FString> FEzGlobalRankingModel::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FEzGlobalRankingModel::GetMetadata() const
    {
        return MetadataValue;
    }
    TOptional<int64> FEzGlobalRankingModel::GetMinimumValue() const
    {
        return MinimumValueValue;
    }

    FString FEzGlobalRankingModel::GetMinimumValueString() const
    {
        if (!MinimumValueValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), MinimumValueValue.GetValue());
    }
    TOptional<int64> FEzGlobalRankingModel::GetMaximumValue() const
    {
        return MaximumValueValue;
    }

    FString FEzGlobalRankingModel::GetMaximumValueString() const
    {
        if (!MaximumValueValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), MaximumValueValue.GetValue());
    }
    TOptional<bool> FEzGlobalRankingModel::GetSum() const
    {
        return SumValue;
    }

    FString FEzGlobalRankingModel::GetSumString() const
    {
        if (!SumValue.IsSet())
        {
            return FString("null");
        }
        return FString(SumValue.GetValue() ? "true" : "false");
    }
    TOptional<FString> FEzGlobalRankingModel::GetOrderDirection() const
    {
        return OrderDirectionValue;
    }
    TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Ranking2::Model::FEzRankingReward>>> FEzGlobalRankingModel::GetRankingRewards() const
    {
        return RankingRewardsValue;
    }
    TOptional<FString> FEzGlobalRankingModel::GetEntryPeriodEventId() const
    {
        return EntryPeriodEventIdValue;
    }
    TOptional<FString> FEzGlobalRankingModel::GetAccessPeriodEventId() const
    {
        return AccessPeriodEventIdValue;
    }

    Gs2::Ranking2::Model::FGlobalRankingModelPtr FEzGlobalRankingModel::ToModel() const
    {
        return MakeShared<Gs2::Ranking2::Model::FGlobalRankingModel>()
            ->WithGlobalRankingModelId(GlobalRankingModelIdValue)
            ->WithName(NameValue)
            ->WithMetadata(MetadataValue)
            ->WithMinimumValue(MinimumValueValue)
            ->WithMaximumValue(MaximumValueValue)
            ->WithSum(SumValue)
            ->WithOrderDirection(OrderDirectionValue)
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

    TSharedPtr<FEzGlobalRankingModel> FEzGlobalRankingModel::FromModel(const Gs2::Ranking2::Model::FGlobalRankingModelPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzGlobalRankingModel>()
            ->WithGlobalRankingModelId(Model->GetGlobalRankingModelId())
            ->WithName(Model->GetName())
            ->WithMetadata(Model->GetMetadata())
            ->WithMinimumValue(Model->GetMinimumValue())
            ->WithMaximumValue(Model->GetMaximumValue())
            ->WithSum(Model->GetSum())
            ->WithOrderDirection(Model->GetOrderDirection())
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