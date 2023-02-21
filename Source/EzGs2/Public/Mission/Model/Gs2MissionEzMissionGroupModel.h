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
#include "Mission/Model/MissionGroupModel.h"
#include "Gs2MissionEzMissionTaskModel.h"

namespace Gs2::UE5::Mission::Model
{
	class EZGS2_API FEzMissionGroupModel final : public TSharedFromThis<FEzMissionGroupModel>
	{
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;
        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Mission::Model::FEzMissionTaskModel>>> TasksValue;
        TOptional<FString> ResetTypeValue;
        TOptional<int32> ResetDayOfMonthValue;
        TOptional<FString> ResetDayOfWeekValue;
        TOptional<int32> ResetHourValue;
        TOptional<FString> CompleteNotificationNamespaceIdValue;

	public:
        TSharedPtr<FEzMissionGroupModel> WithName(const TOptional<FString> Name);
        TSharedPtr<FEzMissionGroupModel> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FEzMissionGroupModel> WithTasks(const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Mission::Model::FEzMissionTaskModel>>> Tasks);
        TSharedPtr<FEzMissionGroupModel> WithResetType(const TOptional<FString> ResetType);
        TSharedPtr<FEzMissionGroupModel> WithResetDayOfMonth(const TOptional<int32> ResetDayOfMonth);
        TSharedPtr<FEzMissionGroupModel> WithResetDayOfWeek(const TOptional<FString> ResetDayOfWeek);
        TSharedPtr<FEzMissionGroupModel> WithResetHour(const TOptional<int32> ResetHour);
        TSharedPtr<FEzMissionGroupModel> WithCompleteNotificationNamespaceId(const TOptional<FString> CompleteNotificationNamespaceId);

        TOptional<FString> GetName() const;

        TOptional<FString> GetMetadata() const;

        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Mission::Model::FEzMissionTaskModel>>> GetTasks() const;

        TOptional<FString> GetResetType() const;

        TOptional<int32> GetResetDayOfMonth() const;
        FString GetResetDayOfMonthString() const;

        TOptional<FString> GetResetDayOfWeek() const;

        TOptional<int32> GetResetHour() const;
        FString GetResetHourString() const;

        TOptional<FString> GetCompleteNotificationNamespaceId() const;

        Gs2::Mission::Model::FMissionGroupModelPtr ToModel() const;
        static TSharedPtr<FEzMissionGroupModel> FromModel(Gs2::Mission::Model::FMissionGroupModelPtr Model);
    };
    typedef TSharedPtr<FEzMissionGroupModel> FEzMissionGroupModelPtr;
}