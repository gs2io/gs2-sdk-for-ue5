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

namespace Gs2::Friend::Request
{
    class FCreateNamespaceRequest;

    class GS2FRIEND_API FCreateNamespaceRequest final : public TSharedFromThis<FCreateNamespaceRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NameValue;
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
        TSharedPtr<Model::FNotificationSetting> AcceptRequestNotificationValue;
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
        TSharedPtr<FCreateNamespaceRequest> WithFollowScript(const TSharedPtr<Model::FScriptSetting> FollowScript);
        TSharedPtr<FCreateNamespaceRequest> WithUnfollowScript(const TSharedPtr<Model::FScriptSetting> UnfollowScript);
        TSharedPtr<FCreateNamespaceRequest> WithSendRequestScript(const TSharedPtr<Model::FScriptSetting> SendRequestScript);
        TSharedPtr<FCreateNamespaceRequest> WithCancelRequestScript(const TSharedPtr<Model::FScriptSetting> CancelRequestScript);
        TSharedPtr<FCreateNamespaceRequest> WithAcceptRequestScript(const TSharedPtr<Model::FScriptSetting> AcceptRequestScript);
        TSharedPtr<FCreateNamespaceRequest> WithRejectRequestScript(const TSharedPtr<Model::FScriptSetting> RejectRequestScript);
        TSharedPtr<FCreateNamespaceRequest> WithDeleteFriendScript(const TSharedPtr<Model::FScriptSetting> DeleteFriendScript);
        TSharedPtr<FCreateNamespaceRequest> WithUpdateProfileScript(const TSharedPtr<Model::FScriptSetting> UpdateProfileScript);
        TSharedPtr<FCreateNamespaceRequest> WithFollowNotification(const TSharedPtr<Model::FNotificationSetting> FollowNotification);
        TSharedPtr<FCreateNamespaceRequest> WithReceiveRequestNotification(const TSharedPtr<Model::FNotificationSetting> ReceiveRequestNotification);
        TSharedPtr<FCreateNamespaceRequest> WithAcceptRequestNotification(const TSharedPtr<Model::FNotificationSetting> AcceptRequestNotification);
        TSharedPtr<FCreateNamespaceRequest> WithLogSetting(const TSharedPtr<Model::FLogSetting> LogSetting);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetName() const;
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
        TSharedPtr<Model::FNotificationSetting> GetAcceptRequestNotification() const;
        TSharedPtr<Model::FLogSetting> GetLogSetting() const;

        static TSharedPtr<FCreateNamespaceRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FCreateNamespaceRequest, ESPMode::ThreadSafe> FCreateNamespaceRequestPtr;
}