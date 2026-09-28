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

#include "Ranking2/Model/Gs2Ranking2EzSubscribeRankingModel.h"

namespace Gs2::UE5::Ranking2::Model
{

    TSharedPtr<FEzSubscribeRankingModel> FEzSubscribeRankingModel::WithSubscribeRankingModelId(
        const TOptional<FString> SubscribeRankingModelId
    )
    {
        this->SubscribeRankingModelIdValue = SubscribeRankingModelId;
        return SharedThis(this);
    }

    TSharedPtr<FEzSubscribeRankingModel> FEzSubscribeRankingModel::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FEzSubscribeRankingModel> FEzSubscribeRankingModel::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FEzSubscribeRankingModel> FEzSubscribeRankingModel::WithMinimumValue(
        const TOptional<int64> MinimumValue
    )
    {
        this->MinimumValueValue = MinimumValue;
        return SharedThis(this);
    }

    TSharedPtr<FEzSubscribeRankingModel> FEzSubscribeRankingModel::WithMaximumValue(
        const TOptional<int64> MaximumValue
    )
    {
        this->MaximumValueValue = MaximumValue;
        return SharedThis(this);
    }

    TSharedPtr<FEzSubscribeRankingModel> FEzSubscribeRankingModel::WithSum(
        const TOptional<bool> Sum
    )
    {
        this->SumValue = Sum;
        return SharedThis(this);
    }

    TSharedPtr<FEzSubscribeRankingModel> FEzSubscribeRankingModel::WithOrderDirection(
        const TOptional<FString> OrderDirection
    )
    {
        this->OrderDirectionValue = OrderDirection;
        return SharedThis(this);
    }

    TSharedPtr<FEzSubscribeRankingModel> FEzSubscribeRankingModel::WithEntryPeriodEventId(
        const TOptional<FString> EntryPeriodEventId
    )
    {
        this->EntryPeriodEventIdValue = EntryPeriodEventId;
        return SharedThis(this);
    }

    TSharedPtr<FEzSubscribeRankingModel> FEzSubscribeRankingModel::WithAccessPeriodEventId(
        const TOptional<FString> AccessPeriodEventId
    )
    {
        this->AccessPeriodEventIdValue = AccessPeriodEventId;
        return SharedThis(this);
    }
    TOptional<FString> FEzSubscribeRankingModel::GetSubscribeRankingModelId() const
    {
        return SubscribeRankingModelIdValue;
    }
    TOptional<FString> FEzSubscribeRankingModel::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FEzSubscribeRankingModel::GetMetadata() const
    {
        return MetadataValue;
    }
    TOptional<int64> FEzSubscribeRankingModel::GetMinimumValue() const
    {
        return MinimumValueValue;
    }

    FString FEzSubscribeRankingModel::GetMinimumValueString() const
    {
        if (!MinimumValueValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), MinimumValueValue.GetValue());
    }
    TOptional<int64> FEzSubscribeRankingModel::GetMaximumValue() const
    {
        return MaximumValueValue;
    }

    FString FEzSubscribeRankingModel::GetMaximumValueString() const
    {
        if (!MaximumValueValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), MaximumValueValue.GetValue());
    }
    TOptional<bool> FEzSubscribeRankingModel::GetSum() const
    {
        return SumValue;
    }

    FString FEzSubscribeRankingModel::GetSumString() const
    {
        if (!SumValue.IsSet())
        {
            return FString("null");
        }
        return FString(SumValue.GetValue() ? "true" : "false");
    }
    TOptional<FString> FEzSubscribeRankingModel::GetOrderDirection() const
    {
        return OrderDirectionValue;
    }
    TOptional<FString> FEzSubscribeRankingModel::GetEntryPeriodEventId() const
    {
        return EntryPeriodEventIdValue;
    }
    TOptional<FString> FEzSubscribeRankingModel::GetAccessPeriodEventId() const
    {
        return AccessPeriodEventIdValue;
    }

    Gs2::Ranking2::Model::FSubscribeRankingModelPtr FEzSubscribeRankingModel::ToModel() const
    {
        return MakeShared<Gs2::Ranking2::Model::FSubscribeRankingModel>()
            ->WithSubscribeRankingModelId(SubscribeRankingModelIdValue)
            ->WithName(NameValue)
            ->WithMetadata(MetadataValue)
            ->WithMinimumValue(MinimumValueValue)
            ->WithMaximumValue(MaximumValueValue)
            ->WithSum(SumValue)
            ->WithOrderDirection(OrderDirectionValue)
            ->WithEntryPeriodEventId(EntryPeriodEventIdValue)
            ->WithAccessPeriodEventId(AccessPeriodEventIdValue);
    }

    TSharedPtr<FEzSubscribeRankingModel> FEzSubscribeRankingModel::FromModel(const Gs2::Ranking2::Model::FSubscribeRankingModelPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzSubscribeRankingModel>()
            ->WithSubscribeRankingModelId(Model->GetSubscribeRankingModelId())
            ->WithName(Model->GetName())
            ->WithMetadata(Model->GetMetadata())
            ->WithMinimumValue(Model->GetMinimumValue())
            ->WithMaximumValue(Model->GetMaximumValue())
            ->WithSum(Model->GetSum())
            ->WithOrderDirection(Model->GetOrderDirection())
            ->WithEntryPeriodEventId(Model->GetEntryPeriodEventId())
            ->WithAccessPeriodEventId(Model->GetAccessPeriodEventId());
    }
}