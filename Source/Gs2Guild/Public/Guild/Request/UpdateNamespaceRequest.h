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
#include "../Model/NotificationSetting.h"
#include "../Model/ScriptSetting.h"
#include "../Model/LogSetting.h"

namespace Gs2::Guild::Request
{
    class FUpdateNamespaceRequest;

    class GS2GUILD_API FUpdateNamespaceRequest final : public TSharedFromThis<FUpdateNamespaceRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> DescriptionValue;
        TSharedPtr<Model::FNotificationSetting> ChangeNotificationValue;
        TSharedPtr<Model::FNotificationSetting> JoinNotificationValue;
        TSharedPtr<Model::FNotificationSetting> LeaveNotificationValue;
        TSharedPtr<Model::FNotificationSetting> ChangeMemberNotificationValue;
        TSharedPtr<Model::FNotificationSetting> ReceiveRequestNotificationValue;
        TSharedPtr<Model::FNotificationSetting> RemoveRequestNotificationValue;
        TSharedPtr<Model::FScriptSetting> CreateGuildScriptValue;
        TSharedPtr<Model::FScriptSetting> UpdateGuildScriptValue;
        TSharedPtr<Model::FScriptSetting> JoinGuildScriptValue;
        TSharedPtr<Model::FScriptSetting> LeaveGuildScriptValue;
        TSharedPtr<Model::FScriptSetting> ChangeRoleScriptValue;
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
        TSharedPtr<FUpdateNamespaceRequest> WithChangeNotification(const TSharedPtr<Model::FNotificationSetting> ChangeNotification);
        TSharedPtr<FUpdateNamespaceRequest> WithJoinNotification(const TSharedPtr<Model::FNotificationSetting> JoinNotification);
        TSharedPtr<FUpdateNamespaceRequest> WithLeaveNotification(const TSharedPtr<Model::FNotificationSetting> LeaveNotification);
        TSharedPtr<FUpdateNamespaceRequest> WithChangeMemberNotification(const TSharedPtr<Model::FNotificationSetting> ChangeMemberNotification);
        TSharedPtr<FUpdateNamespaceRequest> WithReceiveRequestNotification(const TSharedPtr<Model::FNotificationSetting> ReceiveRequestNotification);
        TSharedPtr<FUpdateNamespaceRequest> WithRemoveRequestNotification(const TSharedPtr<Model::FNotificationSetting> RemoveRequestNotification);
        TSharedPtr<FUpdateNamespaceRequest> WithCreateGuildScript(const TSharedPtr<Model::FScriptSetting> CreateGuildScript);
        TSharedPtr<FUpdateNamespaceRequest> WithUpdateGuildScript(const TSharedPtr<Model::FScriptSetting> UpdateGuildScript);
        TSharedPtr<FUpdateNamespaceRequest> WithJoinGuildScript(const TSharedPtr<Model::FScriptSetting> JoinGuildScript);
        TSharedPtr<FUpdateNamespaceRequest> WithLeaveGuildScript(const TSharedPtr<Model::FScriptSetting> LeaveGuildScript);
        TSharedPtr<FUpdateNamespaceRequest> WithChangeRoleScript(const TSharedPtr<Model::FScriptSetting> ChangeRoleScript);
        TSharedPtr<FUpdateNamespaceRequest> WithLogSetting(const TSharedPtr<Model::FLogSetting> LogSetting);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetDescription() const;
        TSharedPtr<Model::FNotificationSetting> GetChangeNotification() const;
        TSharedPtr<Model::FNotificationSetting> GetJoinNotification() const;
        TSharedPtr<Model::FNotificationSetting> GetLeaveNotification() const;
        TSharedPtr<Model::FNotificationSetting> GetChangeMemberNotification() const;
        TSharedPtr<Model::FNotificationSetting> GetReceiveRequestNotification() const;
        TSharedPtr<Model::FNotificationSetting> GetRemoveRequestNotification() const;
        TSharedPtr<Model::FScriptSetting> GetCreateGuildScript() const;
        TSharedPtr<Model::FScriptSetting> GetUpdateGuildScript() const;
        TSharedPtr<Model::FScriptSetting> GetJoinGuildScript() const;
        TSharedPtr<Model::FScriptSetting> GetLeaveGuildScript() const;
        TSharedPtr<Model::FScriptSetting> GetChangeRoleScript() const;
        TSharedPtr<Model::FLogSetting> GetLogSetting() const;

        static TSharedPtr<FUpdateNamespaceRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequestPtr;
}