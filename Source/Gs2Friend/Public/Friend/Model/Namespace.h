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

namespace Gs2::Friend::Model
{
    class GS2FRIEND_API FNamespace final : public Gs2Object, public TSharedFromThis<FNamespace>
    {
        TOptional<FString> NamespaceIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> DescriptionValue;
        TSharedPtr<FScriptSetting> FollowScriptValue;
        TSharedPtr<FScriptSetting> UnfollowScriptValue;
        TSharedPtr<FScriptSetting> SendRequestScriptValue;
        TSharedPtr<FScriptSetting> CancelRequestScriptValue;
        TSharedPtr<FScriptSetting> AcceptRequestScriptValue;
        TSharedPtr<FScriptSetting> RejectRequestScriptValue;
        TSharedPtr<FScriptSetting> DeleteFriendScriptValue;
        TSharedPtr<FScriptSetting> UpdateProfileScriptValue;
        TSharedPtr<FNotificationSetting> FollowNotificationValue;
        TSharedPtr<FNotificationSetting> ReceiveRequestNotificationValue;
        TSharedPtr<FNotificationSetting> CancelRequestNotificationValue;
        TSharedPtr<FNotificationSetting> AcceptRequestNotificationValue;
        TSharedPtr<FNotificationSetting> RejectRequestNotificationValue;
        TSharedPtr<FNotificationSetting> DeleteFriendNotificationValue;
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
        TSharedPtr<FNamespace> WithFollowScript(const TSharedPtr<FScriptSetting> FollowScript);
        TSharedPtr<FNamespace> WithUnfollowScript(const TSharedPtr<FScriptSetting> UnfollowScript);
        TSharedPtr<FNamespace> WithSendRequestScript(const TSharedPtr<FScriptSetting> SendRequestScript);
        TSharedPtr<FNamespace> WithCancelRequestScript(const TSharedPtr<FScriptSetting> CancelRequestScript);
        TSharedPtr<FNamespace> WithAcceptRequestScript(const TSharedPtr<FScriptSetting> AcceptRequestScript);
        TSharedPtr<FNamespace> WithRejectRequestScript(const TSharedPtr<FScriptSetting> RejectRequestScript);
        TSharedPtr<FNamespace> WithDeleteFriendScript(const TSharedPtr<FScriptSetting> DeleteFriendScript);
        TSharedPtr<FNamespace> WithUpdateProfileScript(const TSharedPtr<FScriptSetting> UpdateProfileScript);
        TSharedPtr<FNamespace> WithFollowNotification(const TSharedPtr<FNotificationSetting> FollowNotification);
        TSharedPtr<FNamespace> WithReceiveRequestNotification(const TSharedPtr<FNotificationSetting> ReceiveRequestNotification);
        TSharedPtr<FNamespace> WithCancelRequestNotification(const TSharedPtr<FNotificationSetting> CancelRequestNotification);
        TSharedPtr<FNamespace> WithAcceptRequestNotification(const TSharedPtr<FNotificationSetting> AcceptRequestNotification);
        TSharedPtr<FNamespace> WithRejectRequestNotification(const TSharedPtr<FNotificationSetting> RejectRequestNotification);
        TSharedPtr<FNamespace> WithDeleteFriendNotification(const TSharedPtr<FNotificationSetting> DeleteFriendNotification);
        TSharedPtr<FNamespace> WithLogSetting(const TSharedPtr<FLogSetting> LogSetting);
        TSharedPtr<FNamespace> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FNamespace> WithUpdatedAt(const TOptional<int64> UpdatedAt);
        TSharedPtr<FNamespace> WithRevision(const TOptional<int64> Revision);

        TOptional<FString> GetNamespaceId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetDescription() const;
        TSharedPtr<FScriptSetting> GetFollowScript() const;
        TSharedPtr<FScriptSetting> GetUnfollowScript() const;
        TSharedPtr<FScriptSetting> GetSendRequestScript() const;
        TSharedPtr<FScriptSetting> GetCancelRequestScript() const;
        TSharedPtr<FScriptSetting> GetAcceptRequestScript() const;
        TSharedPtr<FScriptSetting> GetRejectRequestScript() const;
        TSharedPtr<FScriptSetting> GetDeleteFriendScript() const;
        TSharedPtr<FScriptSetting> GetUpdateProfileScript() const;
        TSharedPtr<FNotificationSetting> GetFollowNotification() const;
        TSharedPtr<FNotificationSetting> GetReceiveRequestNotification() const;
        TSharedPtr<FNotificationSetting> GetCancelRequestNotification() const;
        TSharedPtr<FNotificationSetting> GetAcceptRequestNotification() const;
        TSharedPtr<FNotificationSetting> GetRejectRequestNotification() const;
        TSharedPtr<FNotificationSetting> GetDeleteFriendNotification() const;
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