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

#include "EzGs2/Public/Idle/Model/Gs2IdleEzCategoryModel.h"

namespace Gs2::UE5::Idle::Model
{

    TSharedPtr<FEzCategoryModel> FEzCategoryModel::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FEzCategoryModel> FEzCategoryModel::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FEzCategoryModel> FEzCategoryModel::WithRewardIntervalMinutes(
        const TOptional<int32> RewardIntervalMinutes
    )
    {
        this->RewardIntervalMinutesValue = RewardIntervalMinutes;
        return SharedThis(this);
    }

    TSharedPtr<FEzCategoryModel> FEzCategoryModel::WithIdlePeriodScheduleId(
        const TOptional<FString> IdlePeriodScheduleId
    )
    {
        this->IdlePeriodScheduleIdValue = IdlePeriodScheduleId;
        return SharedThis(this);
    }

    TSharedPtr<FEzCategoryModel> FEzCategoryModel::WithReceivePeriodScheduleId(
        const TOptional<FString> ReceivePeriodScheduleId
    )
    {
        this->ReceivePeriodScheduleIdValue = ReceivePeriodScheduleId;
        return SharedThis(this);
    }
    TOptional<FString> FEzCategoryModel::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FEzCategoryModel::GetMetadata() const
    {
        return MetadataValue;
    }
    TOptional<int32> FEzCategoryModel::GetRewardIntervalMinutes() const
    {
        return RewardIntervalMinutesValue;
    }

    FString FEzCategoryModel::GetRewardIntervalMinutesString() const
    {
        if (!RewardIntervalMinutesValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), RewardIntervalMinutesValue.GetValue());
    }
    TOptional<FString> FEzCategoryModel::GetIdlePeriodScheduleId() const
    {
        return IdlePeriodScheduleIdValue;
    }
    TOptional<FString> FEzCategoryModel::GetReceivePeriodScheduleId() const
    {
        return ReceivePeriodScheduleIdValue;
    }

    Gs2::Idle::Model::FCategoryModelPtr FEzCategoryModel::ToModel() const
    {
        return MakeShared<Gs2::Idle::Model::FCategoryModel>()
            ->WithName(NameValue)
            ->WithMetadata(MetadataValue)
            ->WithRewardIntervalMinutes(RewardIntervalMinutesValue)
            ->WithIdlePeriodScheduleId(IdlePeriodScheduleIdValue)
            ->WithReceivePeriodScheduleId(ReceivePeriodScheduleIdValue);
    }

    TSharedPtr<FEzCategoryModel> FEzCategoryModel::FromModel(const Gs2::Idle::Model::FCategoryModelPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzCategoryModel>()
            ->WithName(Model->GetName())
            ->WithMetadata(Model->GetMetadata())
            ->WithRewardIntervalMinutes(Model->GetRewardIntervalMinutes())
            ->WithIdlePeriodScheduleId(Model->GetIdlePeriodScheduleId())
            ->WithReceivePeriodScheduleId(Model->GetReceivePeriodScheduleId());
    }
}