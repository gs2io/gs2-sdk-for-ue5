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
#include "../Model/ScriptSetting.h"
#include "../Model/NotificationSetting.h"
#include "../Model/LogSetting.h"

namespace Gs2::Matchmaking::Request
{
    class FUpdateNamespaceRequest;

    class GS2MATCHMAKING_API FUpdateNamespaceRequest final : public TSharedFromThis<FUpdateNamespaceRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
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
        TSharedPtr<Model::FScriptSetting> ChangeRatingScriptValue;
        TSharedPtr<Model::FNotificationSetting> JoinNotificationValue;
        TSharedPtr<Model::FNotificationSetting> LeaveNotificationValue;
        TSharedPtr<Model::FNotificationSetting> CompleteNotificationValue;
        TSharedPtr<Model::FNotificationSetting> ChangeRatingNotificationValue;
        TSharedPtr<Model::FLogSetting> LogSettingValue;
        
    public:
        
        FUpdateNamespaceRequest();
        FUpdateNamespaceRequest(
            const FUpdateNamespaceRequest& From
        );
        ~FUpdateNamespaceRequest() = default;

        TSharedPtr<FUpdateNamespaceRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FUpdateNamespaceRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FUpdateNamespaceRequest> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FUpdateNamespaceRequest> WithEnableRating(const TOptional<bool> EnableRating);
        TSharedPtr<FUpdateNamespaceRequest> WithCreateGatheringTriggerType(const TOptional<FString> CreateGatheringTriggerType);
        TSharedPtr<FUpdateNamespaceRequest> WithCreateGatheringTriggerRealtimeNamespaceId(const TOptional<FString> CreateGatheringTriggerRealtimeNamespaceId);
        TSharedPtr<FUpdateNamespaceRequest> WithCreateGatheringTriggerScriptId(const TOptional<FString> CreateGatheringTriggerScriptId);
        TSharedPtr<FUpdateNamespaceRequest> WithCompleteMatchmakingTriggerType(const TOptional<FString> CompleteMatchmakingTriggerType);
        TSharedPtr<FUpdateNamespaceRequest> WithCompleteMatchmakingTriggerRealtimeNamespaceId(const TOptional<FString> CompleteMatchmakingTriggerRealtimeNamespaceId);
        TSharedPtr<FUpdateNamespaceRequest> WithCompleteMatchmakingTriggerScriptId(const TOptional<FString> CompleteMatchmakingTriggerScriptId);
        TSharedPtr<FUpdateNamespaceRequest> WithEnableCollaborateSeasonRating(const TOptional<FString> EnableCollaborateSeasonRating);
        TSharedPtr<FUpdateNamespaceRequest> WithCollaborateSeasonRatingNamespaceId(const TOptional<FString> CollaborateSeasonRatingNamespaceId);
        TSharedPtr<FUpdateNamespaceRequest> WithCollaborateSeasonRatingTtl(const TOptional<int32> CollaborateSeasonRatingTtl);
        TSharedPtr<FUpdateNamespaceRequest> WithChangeRatingScript(const TSharedPtr<Model::FScriptSetting> ChangeRatingScript);
        TSharedPtr<FUpdateNamespaceRequest> WithJoinNotification(const TSharedPtr<Model::FNotificationSetting> JoinNotification);
        TSharedPtr<FUpdateNamespaceRequest> WithLeaveNotification(const TSharedPtr<Model::FNotificationSetting> LeaveNotification);
        TSharedPtr<FUpdateNamespaceRequest> WithCompleteNotification(const TSharedPtr<Model::FNotificationSetting> CompleteNotification);
        TSharedPtr<FUpdateNamespaceRequest> WithChangeRatingNotification(const TSharedPtr<Model::FNotificationSetting> ChangeRatingNotification);
        TSharedPtr<FUpdateNamespaceRequest> WithLogSetting(const TSharedPtr<Model::FLogSetting> LogSetting);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
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
        TSharedPtr<Model::FScriptSetting> GetChangeRatingScript() const;
        TSharedPtr<Model::FNotificationSetting> GetJoinNotification() const;
        TSharedPtr<Model::FNotificationSetting> GetLeaveNotification() const;
        TSharedPtr<Model::FNotificationSetting> GetCompleteNotification() const;
        TSharedPtr<Model::FNotificationSetting> GetChangeRatingNotification() const;
        TSharedPtr<Model::FLogSetting> GetLogSetting() const;

        static TSharedPtr<FUpdateNamespaceRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUpdateNamespaceRequest, ESPMode::ThreadSafe> FUpdateNamespaceRequestPtr;
}