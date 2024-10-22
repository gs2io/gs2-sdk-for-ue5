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

namespace Gs2::Friend::Request
{
    class FUpdateNamespaceRequest;

    class GS2FRIEND_API FUpdateNamespaceRequest final : public TSharedFromThis<FUpdateNamespaceRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> DescriptionValue;
        TSharedPtr<Model::FScriptSetting> FollowScriptValue;
        TSharedPtr<Model::FScriptSetting> UnfollowScriptValue;
        TSharedPtr<Model::FScriptSetting> SendRequestScriptValue;
        TSharedPtr<Model::FScriptSetting> CancelRequestScriptValue;
        TSharedPtr<Model::FScriptSetting> AcceptRequestScriptValue;
        TSharedPtr<Model::FScriptSetting> RejectRequestScriptValue;
        TSharedPtr<Model::FScriptSetting> DeleteFriendScriptValue;
        TSharedPtr<Model::FScriptSetting> UpdateProfileScriptValue;
        TSharedPtr<Model::FNotificationSetting> FollowNotificationValue;
        TSharedPtr<Model::FNotificationSetting> ReceiveRequestNotificationValue;
        TSharedPtr<Model::FNotificationSetting> CancelRequestNotificationValue;
        TSharedPtr<Model::FNotificationSetting> AcceptRequestNotificationValue;
        TSharedPtr<Model::FNotificationSetting> RejectRequestNotificationValue;
        TSharedPtr<Model::FNotificationSetting> DeleteFriendNotificationValue;
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
        TSharedPtr<FUpdateNamespaceRequest> WithFollowScript(const TSharedPtr<Model::FScriptSetting> FollowScript);
        TSharedPtr<FUpdateNamespaceRequest> WithUnfollowScript(const TSharedPtr<Model::FScriptSetting> UnfollowScript);
        TSharedPtr<FUpdateNamespaceRequest> WithSendRequestScript(const TSharedPtr<Model::FScriptSetting> SendRequestScript);
        TSharedPtr<FUpdateNamespaceRequest> WithCancelRequestScript(const TSharedPtr<Model::FScriptSetting> CancelRequestScript);
        TSharedPtr<FUpdateNamespaceRequest> WithAcceptRequestScript(const TSharedPtr<Model::FScriptSetting> AcceptRequestScript);
        TSharedPtr<FUpdateNamespaceRequest> WithRejectRequestScript(const TSharedPtr<Model::FScriptSetting> RejectRequestScript);
        TSharedPtr<FUpdateNamespaceRequest> WithDeleteFriendScript(const TSharedPtr<Model::FScriptSetting> DeleteFriendScript);
        TSharedPtr<FUpdateNamespaceRequest> WithUpdateProfileScript(const TSharedPtr<Model::FScriptSetting> UpdateProfileScript);
        TSharedPtr<FUpdateNamespaceRequest> WithFollowNotification(const TSharedPtr<Model::FNotificationSetting> FollowNotification);
        TSharedPtr<FUpdateNamespaceRequest> WithReceiveRequestNotification(const TSharedPtr<Model::FNotificationSetting> ReceiveRequestNotification);
        TSharedPtr<FUpdateNamespaceRequest> WithCancelRequestNotification(const TSharedPtr<Model::FNotificationSetting> CancelRequestNotification);
        TSharedPtr<FUpdateNamespaceRequest> WithAcceptRequestNotification(const TSharedPtr<Model::FNotificationSetting> AcceptRequestNotification);
        TSharedPtr<FUpdateNamespaceRequest> WithRejectRequestNotification(const TSharedPtr<Model::FNotificationSetting> RejectRequestNotification);
        TSharedPtr<FUpdateNamespaceRequest> WithDeleteFriendNotification(const TSharedPtr<Model::FNotificationSetting> DeleteFriendNotification);
        TSharedPtr<FUpdateNamespaceRequest> WithLogSetting(const TSharedPtr<Model::FLogSetting> LogSetting);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetDescription() const;
        TSharedPtr<Model::FScriptSetting> GetFollowScript() const;
        TSharedPtr<Model::FScriptSetting> GetUnfollowScript() const;
        TSharedPtr<Model::FScriptSetting> GetSendRequestScript() const;
        TSharedPtr<Model::FScriptSetting> GetCancelRequestScript() const;
        TSharedPtr<Model::FScriptSetting> GetAcceptRequestScript() const;
        TSharedPtr<Model::FScriptSetting> GetRejectRequestScript() const;
        TSharedPtr<Model::FScriptSetting> GetDeleteFriendScript() const;
        TSharedPtr<Model::FScriptSetting> GetUpdateProfileScript() const;
        TSharedPtr<Model::FNotificationSetting> GetFollowNotification() const;
        TSharedPtr<Model::FNotificationSetting> GetReceiveRequestNotification() const;
        TSharedPtr<Model::FNotificationSetting> GetCancelRequestNotification() const;
        TSharedPtr<Model::FNotificationSetting> GetAcceptRequestNotification() const;
        TSharedPtr<Model::FNotificationSetting> GetRejectRequestNotification() const;
        TSharedPtr<Model::FNotificationSetting> GetDeleteFriendNotification() const;
        TSharedPtr<Model::FLogSetting> GetLogSetting() const;

        static TSharedPtr<FUpdateNamespaceRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequestPtr;
}