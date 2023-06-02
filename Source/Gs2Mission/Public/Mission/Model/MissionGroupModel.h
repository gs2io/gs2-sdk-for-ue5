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
#include "MissionTaskModel.h"

namespace Gs2::Mission::Model
{
    class GS2MISSION_API FMissionGroupModel final : public Gs2Object, public TSharedFromThis<FMissionGroupModel>
    {
        TOptional<FString> MissionGroupIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;
        TSharedPtr<TArray<TSharedPtr<FMissionTaskModel>>> TasksValue;
        TOptional<FString> ResetTypeValue;
        TOptional<int32> ResetDayOfMonthValue;
        TOptional<FString> ResetDayOfWeekValue;
        TOptional<int32> ResetHourValue;
        TOptional<FString> CompleteNotificationNamespaceIdValue;

    public:
        FMissionGroupModel();
        FMissionGroupModel(
            const FMissionGroupModel& From
        );
        virtual ~FMissionGroupModel() override = default;

        TSharedPtr<FMissionGroupModel> WithMissionGroupId(const TOptional<FString> MissionGroupId);
        TSharedPtr<FMissionGroupModel> WithName(const TOptional<FString> Name);
        TSharedPtr<FMissionGroupModel> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FMissionGroupModel> WithTasks(const TSharedPtr<TArray<TSharedPtr<FMissionTaskModel>>> Tasks);
        TSharedPtr<FMissionGroupModel> WithResetType(const TOptional<FString> ResetType);
        TSharedPtr<FMissionGroupModel> WithResetDayOfMonth(const TOptional<int32> ResetDayOfMonth);
        TSharedPtr<FMissionGroupModel> WithResetDayOfWeek(const TOptional<FString> ResetDayOfWeek);
        TSharedPtr<FMissionGroupModel> WithResetHour(const TOptional<int32> ResetHour);
        TSharedPtr<FMissionGroupModel> WithCompleteNotificationNamespaceId(const TOptional<FString> CompleteNotificationNamespaceId);

        TOptional<FString> GetMissionGroupId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetMetadata() const;
        TSharedPtr<TArray<TSharedPtr<FMissionTaskModel>>> GetTasks() const;
        TOptional<FString> GetResetType() const;
        TOptional<int32> GetResetDayOfMonth() const;
        FString GetResetDayOfMonthString() const;
        TOptional<FString> GetResetDayOfWeek() const;
        TOptional<int32> GetResetHour() const;
        FString GetResetHourString() const;
        TOptional<FString> GetCompleteNotificationNamespaceId() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetMissionGroupNameFromGrn(const FString Grn);

        static TSharedPtr<FMissionGroupModel> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FMissionGroupModel, ESPMode::ThreadSafe> FMissionGroupModelPtr;
}