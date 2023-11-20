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

#include "Limit/Model/Gs2LimitEzLimitModel.h"

namespace Gs2::UE5::Limit::Model
{

    TSharedPtr<FEzLimitModel> FEzLimitModel::WithLimitModelId(
        const TOptional<FString> LimitModelId
    )
    {
        this->LimitModelIdValue = LimitModelId;
        return SharedThis(this);
    }

    TSharedPtr<FEzLimitModel> FEzLimitModel::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FEzLimitModel> FEzLimitModel::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FEzLimitModel> FEzLimitModel::WithResetType(
        const TOptional<FString> ResetType
    )
    {
        this->ResetTypeValue = ResetType;
        return SharedThis(this);
    }

    TSharedPtr<FEzLimitModel> FEzLimitModel::WithResetDayOfMonth(
        const TOptional<int32> ResetDayOfMonth
    )
    {
        this->ResetDayOfMonthValue = ResetDayOfMonth;
        return SharedThis(this);
    }

    TSharedPtr<FEzLimitModel> FEzLimitModel::WithResetDayOfWeek(
        const TOptional<FString> ResetDayOfWeek
    )
    {
        this->ResetDayOfWeekValue = ResetDayOfWeek;
        return SharedThis(this);
    }

    TSharedPtr<FEzLimitModel> FEzLimitModel::WithResetHour(
        const TOptional<int32> ResetHour
    )
    {
        this->ResetHourValue = ResetHour;
        return SharedThis(this);
    }
    TOptional<FString> FEzLimitModel::GetLimitModelId() const
    {
        return LimitModelIdValue;
    }
    TOptional<FString> FEzLimitModel::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FEzLimitModel::GetMetadata() const
    {
        return MetadataValue;
    }
    TOptional<FString> FEzLimitModel::GetResetType() const
    {
        return ResetTypeValue;
    }
    TOptional<int32> FEzLimitModel::GetResetDayOfMonth() const
    {
        return ResetDayOfMonthValue;
    }

    FString FEzLimitModel::GetResetDayOfMonthString() const
    {
        if (!ResetDayOfMonthValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), ResetDayOfMonthValue.GetValue());
    }
    TOptional<FString> FEzLimitModel::GetResetDayOfWeek() const
    {
        return ResetDayOfWeekValue;
    }
    TOptional<int32> FEzLimitModel::GetResetHour() const
    {
        return ResetHourValue;
    }

    FString FEzLimitModel::GetResetHourString() const
    {
        if (!ResetHourValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), ResetHourValue.GetValue());
    }

    Gs2::Limit::Model::FLimitModelPtr FEzLimitModel::ToModel() const
    {
        return MakeShared<Gs2::Limit::Model::FLimitModel>()
            ->WithLimitModelId(LimitModelIdValue)
            ->WithName(NameValue)
            ->WithMetadata(MetadataValue)
            ->WithResetType(ResetTypeValue)
            ->WithResetDayOfMonth(ResetDayOfMonthValue)
            ->WithResetDayOfWeek(ResetDayOfWeekValue)
            ->WithResetHour(ResetHourValue);
    }

    TSharedPtr<FEzLimitModel> FEzLimitModel::FromModel(const Gs2::Limit::Model::FLimitModelPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzLimitModel>()
            ->WithLimitModelId(Model->GetLimitModelId())
            ->WithName(Model->GetName())
            ->WithMetadata(Model->GetMetadata())
            ->WithResetType(Model->GetResetType())
            ->WithResetDayOfMonth(Model->GetResetDayOfMonth())
            ->WithResetDayOfWeek(Model->GetResetDayOfWeek())
            ->WithResetHour(Model->GetResetHour());
    }
}