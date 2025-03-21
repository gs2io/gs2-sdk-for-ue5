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

namespace Gs2::Mission::Model
{
    class GS2MISSION_API FMissionGroupModelMaster final : public FGs2Object, public TSharedFromThis<FMissionGroupModelMaster>
    {
        TOptional<FString> MissionGroupIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> ResetTypeValue;
        TOptional<int32> ResetDayOfMonthValue;
        TOptional<FString> ResetDayOfWeekValue;
        TOptional<int32> ResetHourValue;
        TOptional<int64> AnchorTimestampValue;
        TOptional<int32> DaysValue;
        TOptional<FString> CompleteNotificationNamespaceIdValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> UpdatedAtValue;
        TOptional<int64> RevisionValue;

    public:
        FMissionGroupModelMaster();
        FMissionGroupModelMaster(
            const FMissionGroupModelMaster& From
        );
        virtual ~FMissionGroupModelMaster() override = default;

        TSharedPtr<FMissionGroupModelMaster> WithMissionGroupId(const TOptional<FString> MissionGroupId);
        TSharedPtr<FMissionGroupModelMaster> WithName(const TOptional<FString> Name);
        TSharedPtr<FMissionGroupModelMaster> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FMissionGroupModelMaster> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FMissionGroupModelMaster> WithResetType(const TOptional<FString> ResetType);
        TSharedPtr<FMissionGroupModelMaster> WithResetDayOfMonth(const TOptional<int32> ResetDayOfMonth);
        TSharedPtr<FMissionGroupModelMaster> WithResetDayOfWeek(const TOptional<FString> ResetDayOfWeek);
        TSharedPtr<FMissionGroupModelMaster> WithResetHour(const TOptional<int32> ResetHour);
        TSharedPtr<FMissionGroupModelMaster> WithAnchorTimestamp(const TOptional<int64> AnchorTimestamp);
        TSharedPtr<FMissionGroupModelMaster> WithDays(const TOptional<int32> Days);
        TSharedPtr<FMissionGroupModelMaster> WithCompleteNotificationNamespaceId(const TOptional<FString> CompleteNotificationNamespaceId);
        TSharedPtr<FMissionGroupModelMaster> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FMissionGroupModelMaster> WithUpdatedAt(const TOptional<int64> UpdatedAt);
        TSharedPtr<FMissionGroupModelMaster> WithRevision(const TOptional<int64> Revision);

        TOptional<FString> GetMissionGroupId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetMetadata() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetResetType() const;
        TOptional<int32> GetResetDayOfMonth() const;
        FString GetResetDayOfMonthString() const;
        TOptional<FString> GetResetDayOfWeek() const;
        TOptional<int32> GetResetHour() const;
        FString GetResetHourString() const;
        TOptional<int64> GetAnchorTimestamp() const;
        FString GetAnchorTimestampString() const;
        TOptional<int32> GetDays() const;
        FString GetDaysString() const;
        TOptional<FString> GetCompleteNotificationNamespaceId() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;
        TOptional<int64> GetUpdatedAt() const;
        FString GetUpdatedAtString() const;
        TOptional<int64> GetRevision() const;
        FString GetRevisionString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetMissionGroupNameFromGrn(const FString Grn);

        static TSharedPtr<FMissionGroupModelMaster> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FMissionGroupModelMaster, ESPMode::ThreadSafe> FMissionGroupModelMasterPtr;
}