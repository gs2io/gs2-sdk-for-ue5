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

#include "Mission/Model/Gs2MissionEzMissionGroupModel.h"

namespace Gs2::UE5::Mission::Model
{

    TSharedPtr<FEzMissionGroupModel> FEzMissionGroupModel::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FEzMissionGroupModel> FEzMissionGroupModel::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FEzMissionGroupModel> FEzMissionGroupModel::WithTasks(
        const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Mission::Model::FEzMissionTaskModel>>> Tasks
    )
    {
        this->TasksValue = Tasks;
        return SharedThis(this);
    }

    TSharedPtr<FEzMissionGroupModel> FEzMissionGroupModel::WithResetType(
        const TOptional<FString> ResetType
    )
    {
        this->ResetTypeValue = ResetType;
        return SharedThis(this);
    }

    TSharedPtr<FEzMissionGroupModel> FEzMissionGroupModel::WithResetDayOfMonth(
        const TOptional<int32> ResetDayOfMonth
    )
    {
        this->ResetDayOfMonthValue = ResetDayOfMonth;
        return SharedThis(this);
    }

    TSharedPtr<FEzMissionGroupModel> FEzMissionGroupModel::WithResetDayOfWeek(
        const TOptional<FString> ResetDayOfWeek
    )
    {
        this->ResetDayOfWeekValue = ResetDayOfWeek;
        return SharedThis(this);
    }

    TSharedPtr<FEzMissionGroupModel> FEzMissionGroupModel::WithResetHour(
        const TOptional<int32> ResetHour
    )
    {
        this->ResetHourValue = ResetHour;
        return SharedThis(this);
    }

    TSharedPtr<FEzMissionGroupModel> FEzMissionGroupModel::WithCompleteNotificationNamespaceId(
        const TOptional<FString> CompleteNotificationNamespaceId
    )
    {
        this->CompleteNotificationNamespaceIdValue = CompleteNotificationNamespaceId;
        return SharedThis(this);
    }
    TOptional<FString> FEzMissionGroupModel::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FEzMissionGroupModel::GetMetadata() const
    {
        return MetadataValue;
    }
    TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Mission::Model::FEzMissionTaskModel>>> FEzMissionGroupModel::GetTasks() const
    {
        return TasksValue;
    }
    TOptional<FString> FEzMissionGroupModel::GetResetType() const
    {
        return ResetTypeValue;
    }
    TOptional<int32> FEzMissionGroupModel::GetResetDayOfMonth() const
    {
        return ResetDayOfMonthValue;
    }

    FString FEzMissionGroupModel::GetResetDayOfMonthString() const
    {
        if (!ResetDayOfMonthValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), ResetDayOfMonthValue.GetValue());
    }
    TOptional<FString> FEzMissionGroupModel::GetResetDayOfWeek() const
    {
        return ResetDayOfWeekValue;
    }
    TOptional<int32> FEzMissionGroupModel::GetResetHour() const
    {
        return ResetHourValue;
    }

    FString FEzMissionGroupModel::GetResetHourString() const
    {
        if (!ResetHourValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), ResetHourValue.GetValue());
    }
    TOptional<FString> FEzMissionGroupModel::GetCompleteNotificationNamespaceId() const
    {
        return CompleteNotificationNamespaceIdValue;
    }

    Gs2::Mission::Model::FMissionGroupModelPtr FEzMissionGroupModel::ToModel() const
    {
        return MakeShared<Gs2::Mission::Model::FMissionGroupModel>()
            ->WithName(NameValue)
            ->WithMetadata(MetadataValue)
            ->WithTasks([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<Gs2::Mission::Model::FMissionTaskModel>>>();
                    if (TasksValue == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *TasksValue)
                    {
                        v->Add(v2->ToModel());
                    }
                    return v;
                }()
            )
            ->WithResetType(ResetTypeValue)
            ->WithResetDayOfMonth(ResetDayOfMonthValue)
            ->WithResetDayOfWeek(ResetDayOfWeekValue)
            ->WithResetHour(ResetHourValue)
            ->WithCompleteNotificationNamespaceId(CompleteNotificationNamespaceIdValue);
    }

    TSharedPtr<FEzMissionGroupModel> FEzMissionGroupModel::FromModel(const Gs2::Mission::Model::FMissionGroupModelPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzMissionGroupModel>()
            ->WithName(Model->GetName())
            ->WithMetadata(Model->GetMetadata())
            ->WithTasks([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<FEzMissionTaskModel>>>();
                    if (Model->GetTasks() == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *Model->GetTasks())
                    {
                        v->Add(FEzMissionTaskModel::FromModel(v2));
                    }
                    return v;
                }()
            )
            ->WithResetType(Model->GetResetType())
            ->WithResetDayOfMonth(Model->GetResetDayOfMonth())
            ->WithResetDayOfWeek(Model->GetResetDayOfWeek())
            ->WithResetHour(Model->GetResetHour())
            ->WithCompleteNotificationNamespaceId(Model->GetCompleteNotificationNamespaceId());
    }
}