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

#include "Buff/Model/Gs2BuffEzBuffEntryModel.h"

namespace Gs2::UE5::Buff::Model
{

    TSharedPtr<FEzBuffEntryModel> FEzBuffEntryModel::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FEzBuffEntryModel> FEzBuffEntryModel::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FEzBuffEntryModel> FEzBuffEntryModel::WithTargetType(
        const TOptional<FString> TargetType
    )
    {
        this->TargetTypeValue = TargetType;
        return SharedThis(this);
    }

    TSharedPtr<FEzBuffEntryModel> FEzBuffEntryModel::WithTargetModel(
        const TSharedPtr<Gs2::UE5::Buff::Model::FEzBuffTargetModel> TargetModel
    )
    {
        this->TargetModelValue = TargetModel;
        return SharedThis(this);
    }

    TSharedPtr<FEzBuffEntryModel> FEzBuffEntryModel::WithTargetAction(
        const TSharedPtr<Gs2::UE5::Buff::Model::FEzBuffTargetAction> TargetAction
    )
    {
        this->TargetActionValue = TargetAction;
        return SharedThis(this);
    }

    TSharedPtr<FEzBuffEntryModel> FEzBuffEntryModel::WithExpression(
        const TOptional<FString> Expression
    )
    {
        this->ExpressionValue = Expression;
        return SharedThis(this);
    }

    TSharedPtr<FEzBuffEntryModel> FEzBuffEntryModel::WithApplyPeriodScheduleEventId(
        const TOptional<FString> ApplyPeriodScheduleEventId
    )
    {
        this->ApplyPeriodScheduleEventIdValue = ApplyPeriodScheduleEventId;
        return SharedThis(this);
    }
    TOptional<FString> FEzBuffEntryModel::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FEzBuffEntryModel::GetMetadata() const
    {
        return MetadataValue;
    }
    TOptional<FString> FEzBuffEntryModel::GetTargetType() const
    {
        return TargetTypeValue;
    }
    TSharedPtr<Gs2::UE5::Buff::Model::FEzBuffTargetModel> FEzBuffEntryModel::GetTargetModel() const
    {
        return TargetModelValue;
    }
    TSharedPtr<Gs2::UE5::Buff::Model::FEzBuffTargetAction> FEzBuffEntryModel::GetTargetAction() const
    {
        return TargetActionValue;
    }
    TOptional<FString> FEzBuffEntryModel::GetExpression() const
    {
        return ExpressionValue;
    }
    TOptional<FString> FEzBuffEntryModel::GetApplyPeriodScheduleEventId() const
    {
        return ApplyPeriodScheduleEventIdValue;
    }

    Gs2::Buff::Model::FBuffEntryModelPtr FEzBuffEntryModel::ToModel() const
    {
        return MakeShared<Gs2::Buff::Model::FBuffEntryModel>()
            ->WithName(NameValue)
            ->WithMetadata(MetadataValue)
            ->WithTargetType(TargetTypeValue)
            ->WithTargetModel(TargetModelValue == nullptr ? nullptr : TargetModelValue->ToModel())
            ->WithTargetAction(TargetActionValue == nullptr ? nullptr : TargetActionValue->ToModel())
            ->WithExpression(ExpressionValue)
            ->WithApplyPeriodScheduleEventId(ApplyPeriodScheduleEventIdValue);
    }

    TSharedPtr<FEzBuffEntryModel> FEzBuffEntryModel::FromModel(const Gs2::Buff::Model::FBuffEntryModelPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzBuffEntryModel>()
            ->WithName(Model->GetName())
            ->WithMetadata(Model->GetMetadata())
            ->WithTargetType(Model->GetTargetType())
            ->WithTargetModel(Model->GetTargetModel() != nullptr ? Gs2::UE5::Buff::Model::FEzBuffTargetModel::FromModel(Model->GetTargetModel()) : nullptr)
            ->WithTargetAction(Model->GetTargetAction() != nullptr ? Gs2::UE5::Buff::Model::FEzBuffTargetAction::FromModel(Model->GetTargetAction()) : nullptr)
            ->WithExpression(Model->GetExpression())
            ->WithApplyPeriodScheduleEventId(Model->GetApplyPeriodScheduleEventId());
    }
}