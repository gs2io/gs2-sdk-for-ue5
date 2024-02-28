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
#include "ScriptSetting.h"
#include "NotificationSetting.h"
#include "LogSetting.h"

namespace Gs2::Matchmaking::Model
{
    class GS2MATCHMAKING_API FNamespace final : public Gs2Object, public TSharedFromThis<FNamespace>
    {
        TOptional<FString> NamespaceIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> DescriptionValue;
        TOptional<bool> EnableRatingValue;
        TOptional<FString> CreateGatheringTriggerTypeValue;
        TOptional<FString> CreateGatheringTriggerRealtimeNamespaceIdValue;
        TOptional<FString> CreateGatheringTriggerScriptIdValue;
        TOptional<FString> CompleteMatchmakingTriggerTypeValue;
        TOptional<FString> CompleteMatchmakingTriggerRealtimeNamespaceIdValue;
        TOptional<FString> CompleteMatchmakingTriggerScriptIdValue;
        TOptional<FString> EnableCollaborateSeasonRatingValue;
        TOptional<FString> CollaborateSeasonRatingNamespaceIdValue;
        TOptional<int32> CollaborateSeasonRatingTtlValue;
        TSharedPtr<FScriptSetting> ChangeRatingScriptValue;
        TSharedPtr<FNotificationSetting> JoinNotificationValue;
        TSharedPtr<FNotificationSetting> LeaveNotificationValue;
        TSharedPtr<FNotificationSetting> CompleteNotificationValue;
        TSharedPtr<FNotificationSetting> ChangeRatingNotificationValue;
        TSharedPtr<FLogSetting> LogSettingValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> UpdatedAtValue;
        TOptional<int64> RevisionValue;

    public:
        FNamespace();
        FNamespace(
            const FNamespace& From
        );
        virtual ~FNamespace() override = default;

        TSharedPtr<FNamespace> WithNamespaceId(const TOptional<FString> NamespaceId);
        TSharedPtr<FNamespace> WithName(const TOptional<FString> Name);
        TSharedPtr<FNamespace> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FNamespace> WithEnableRating(const TOptional<bool> EnableRating);
        TSharedPtr<FNamespace> WithCreateGatheringTriggerType(const TOptional<FString> CreateGatheringTriggerType);
        TSharedPtr<FNamespace> WithCreateGatheringTriggerRealtimeNamespaceId(const TOptional<FString> CreateGatheringTriggerRealtimeNamespaceId);
        TSharedPtr<FNamespace> WithCreateGatheringTriggerScriptId(const TOptional<FString> CreateGatheringTriggerScriptId);
        TSharedPtr<FNamespace> WithCompleteMatchmakingTriggerType(const TOptional<FString> CompleteMatchmakingTriggerType);
        TSharedPtr<FNamespace> WithCompleteMatchmakingTriggerRealtimeNamespaceId(const TOptional<FString> CompleteMatchmakingTriggerRealtimeNamespaceId);
        TSharedPtr<FNamespace> WithCompleteMatchmakingTriggerScriptId(const TOptional<FString> CompleteMatchmakingTriggerScriptId);
        TSharedPtr<FNamespace> WithEnableCollaborateSeasonRating(const TOptional<FString> EnableCollaborateSeasonRating);
        TSharedPtr<FNamespace> WithCollaborateSeasonRatingNamespaceId(const TOptional<FString> CollaborateSeasonRatingNamespaceId);
        TSharedPtr<FNamespace> WithCollaborateSeasonRatingTtl(const TOptional<int32> CollaborateSeasonRatingTtl);
        TSharedPtr<FNamespace> WithChangeRatingScript(const TSharedPtr<FScriptSetting> ChangeRatingScript);
        TSharedPtr<FNamespace> WithJoinNotification(const TSharedPtr<FNotificationSetting> JoinNotification);
        TSharedPtr<FNamespace> WithLeaveNotification(const TSharedPtr<FNotificationSetting> LeaveNotification);
        TSharedPtr<FNamespace> WithCompleteNotification(const TSharedPtr<FNotificationSetting> CompleteNotification);
        TSharedPtr<FNamespace> WithChangeRatingNotification(const TSharedPtr<FNotificationSetting> ChangeRatingNotification);
        TSharedPtr<FNamespace> WithLogSetting(const TSharedPtr<FLogSetting> LogSetting);
        TSharedPtr<FNamespace> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FNamespace> WithUpdatedAt(const TOptional<int64> UpdatedAt);
        TSharedPtr<FNamespace> WithRevision(const TOptional<int64> Revision);

        TOptional<FString> GetNamespaceId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetDescription() const;
        TOptional<bool> GetEnableRating() const;
        FString GetEnableRatingString() const;
        TOptional<FString> GetCreateGatheringTriggerType() const;
        TOptional<FString> GetCreateGatheringTriggerRealtimeNamespaceId() const;
        TOptional<FString> GetCreateGatheringTriggerScriptId() const;
        TOptional<FString> GetCompleteMatchmakingTriggerType() const;
        TOptional<FString> GetCompleteMatchmakingTriggerRealtimeNamespaceId() const;
        TOptional<FString> GetCompleteMatchmakingTriggerScriptId() const;
        TOptional<FString> GetEnableCollaborateSeasonRating() const;
        TOptional<FString> GetCollaborateSeasonRatingNamespaceId() const;
        TOptional<int32> GetCollaborateSeasonRatingTtl() const;
        FString GetCollaborateSeasonRatingTtlString() const;
        TSharedPtr<FScriptSetting> GetChangeRatingScript() const;
        TSharedPtr<FNotificationSetting> GetJoinNotification() const;
        TSharedPtr<FNotificationSetting> GetLeaveNotification() const;
        TSharedPtr<FNotificationSetting> GetCompleteNotification() const;
        TSharedPtr<FNotificationSetting> GetChangeRatingNotification() const;
        TSharedPtr<FLogSetting> GetLogSetting() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;
        TOptional<int64> GetUpdatedAt() const;
        FString GetUpdatedAtString() const;
        TOptional<int64> GetRevision() const;
        FString GetRevisionString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);

        static TSharedPtr<FNamespace> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FNamespace, ESPMode::ThreadSafe> FNamespacePtr;
}