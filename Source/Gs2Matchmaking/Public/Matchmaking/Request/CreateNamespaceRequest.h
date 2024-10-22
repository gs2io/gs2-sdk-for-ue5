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
#include "Dom/JsonObject.h"
#include "../Model/ScriptSetting.h"
#include "../Model/NotificationSetting.h"
#include "../Model/LogSetting.h"

namespace Gs2::Matchmaking::Request
{
    class FCreateNamespaceRequest;

    class GS2MATCHMAKING_API FCreateNamespaceRequest final : public TSharedFromThis<FCreateNamespaceRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NameValue;
        TOptional<FString> DescriptionValue;
        TOptional<bool> EnableRatingValue;
        TOptional<FString> EnableDisconnectDetectionValue;
        TOptional<int32> DisconnectDetectionTimeoutSecondsValue;
        TOptional<FString> CreateGatheringTriggerTypeValue;
        TOptional<FString> CreateGatheringTriggerRealtimeNamespaceIdValue;
        TOptional<FString> CreateGatheringTriggerScriptIdValue;
        TOptional<FString> CompleteMatchmakingTriggerTypeValue;
        TOptional<FString> CompleteMatchmakingTriggerRealtimeNamespaceIdValue;
        TOptional<FString> CompleteMatchmakingTriggerScriptIdValue;
        TOptional<FString> EnableCollaborateSeasonRatingValue;
        TOptional<FString> CollaborateSeasonRatingNamespaceIdValue;
        TOptional<int32> CollaborateSeasonRatingTtlValue;
        TSharedPtr<Model::FScriptSetting> ChangeRatingScriptValue;
        TSharedPtr<Model::FNotificationSetting> JoinNotificationValue;
        TSharedPtr<Model::FNotificationSetting> LeaveNotificationValue;
        TSharedPtr<Model::FNotificationSetting> CompleteNotificationValue;
        TSharedPtr<Model::FNotificationSetting> ChangeRatingNotificationValue;
        TSharedPtr<Model::FLogSetting> LogSettingValue;
        
    public:
        
        FCreateNamespaceRequest();
        FCreateNamespaceRequest(
            const FCreateNamespaceRequest& From
        );
        ~FCreateNamespaceRequest() = default;

        TSharedPtr<FCreateNamespaceRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FCreateNamespaceRequest> WithName(const TOptional<FString> Name);
        TSharedPtr<FCreateNamespaceRequest> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FCreateNamespaceRequest> WithEnableRating(const TOptional<bool> EnableRating);
        TSharedPtr<FCreateNamespaceRequest> WithEnableDisconnectDetection(const TOptional<FString> EnableDisconnectDetection);
        TSharedPtr<FCreateNamespaceRequest> WithDisconnectDetectionTimeoutSeconds(const TOptional<int32> DisconnectDetectionTimeoutSeconds);
        TSharedPtr<FCreateNamespaceRequest> WithCreateGatheringTriggerType(const TOptional<FString> CreateGatheringTriggerType);
        TSharedPtr<FCreateNamespaceRequest> WithCreateGatheringTriggerRealtimeNamespaceId(const TOptional<FString> CreateGatheringTriggerRealtimeNamespaceId);
        TSharedPtr<FCreateNamespaceRequest> WithCreateGatheringTriggerScriptId(const TOptional<FString> CreateGatheringTriggerScriptId);
        TSharedPtr<FCreateNamespaceRequest> WithCompleteMatchmakingTriggerType(const TOptional<FString> CompleteMatchmakingTriggerType);
        TSharedPtr<FCreateNamespaceRequest> WithCompleteMatchmakingTriggerRealtimeNamespaceId(const TOptional<FString> CompleteMatchmakingTriggerRealtimeNamespaceId);
        TSharedPtr<FCreateNamespaceRequest> WithCompleteMatchmakingTriggerScriptId(const TOptional<FString> CompleteMatchmakingTriggerScriptId);
        TSharedPtr<FCreateNamespaceRequest> WithEnableCollaborateSeasonRating(const TOptional<FString> EnableCollaborateSeasonRating);
        TSharedPtr<FCreateNamespaceRequest> WithCollaborateSeasonRatingNamespaceId(const TOptional<FString> CollaborateSeasonRatingNamespaceId);
        TSharedPtr<FCreateNamespaceRequest> WithCollaborateSeasonRatingTtl(const TOptional<int32> CollaborateSeasonRatingTtl);
        TSharedPtr<FCreateNamespaceRequest> WithChangeRatingScript(const TSharedPtr<Model::FScriptSetting> ChangeRatingScript);
        TSharedPtr<FCreateNamespaceRequest> WithJoinNotification(const TSharedPtr<Model::FNotificationSetting> JoinNotification);
        TSharedPtr<FCreateNamespaceRequest> WithLeaveNotification(const TSharedPtr<Model::FNotificationSetting> LeaveNotification);
        TSharedPtr<FCreateNamespaceRequest> WithCompleteNotification(const TSharedPtr<Model::FNotificationSetting> CompleteNotification);
        TSharedPtr<FCreateNamespaceRequest> WithChangeRatingNotification(const TSharedPtr<Model::FNotificationSetting> ChangeRatingNotification);
        TSharedPtr<FCreateNamespaceRequest> WithLogSetting(const TSharedPtr<Model::FLogSetting> LogSetting);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetDescription() const;
        TOptional<bool> GetEnableRating() const;
        FString GetEnableRatingString() const;
        TOptional<FString> GetEnableDisconnectDetection() const;
        TOptional<int32> GetDisconnectDetectionTimeoutSeconds() const;
        FString GetDisconnectDetectionTimeoutSecondsString() const;
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
        TSharedPtr<Model::FScriptSetting> GetChangeRatingScript() const;
        TSharedPtr<Model::FNotificationSetting> GetJoinNotification() const;
        TSharedPtr<Model::FNotificationSetting> GetLeaveNotification() const;
        TSharedPtr<Model::FNotificationSetting> GetCompleteNotification() const;
        TSharedPtr<Model::FNotificationSetting> GetChangeRatingNotification() const;
        TSharedPtr<Model::FLogSetting> GetLogSetting() const;

        static TSharedPtr<FCreateNamespaceRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequestPtr;
}