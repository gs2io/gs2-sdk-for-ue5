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
            ->WithEntryPeriodEventId(Model->GetEntryPeriodEventId())
            ->WithAccessPeriodEventId(Model->GetAccessPeriodEventId());
    }
}