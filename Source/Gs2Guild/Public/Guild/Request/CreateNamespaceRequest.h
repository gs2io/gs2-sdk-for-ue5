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
    class FCreateNamespaceRequest;

    class GS2GUILD_API FCreateNamespaceRequest final : public TSharedFromThis<FCreateNamespaceRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NameValue;
        TOptional<FString> DescriptionValue;
        TSharedPtr<Model::FNotificationSetting> JoinNotificationValue;
        TSharedPtr<Model::FNotificationSetting> LeaveNotificationValue;
        TSharedPtr<Model::FNotificationSetting> ChangeMemberNotificationValue;
        TSharedPtr<Model::FNotificationSetting> ReceiveRequestNotificationValue;
        TSharedPtr<Model::FNotificationSetting> RemoveRequestNotificationValue;
        TSharedPtr<Model::FScriptSetting> CreateGuildScriptValue;
        TSharedPtr<Model::FScriptSetting> JoinGuildScriptValue;
        TSharedPtr<Model::FScriptSetting> LeaveGuildScriptValue;
        TSharedPtr<Model::FScriptSetting> ChangeRoleScriptValue;
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
        TSharedPtr<FCreateNamespaceRequest> WithJoinNotification(const TSharedPtr<Model::FNotificationSetting> JoinNotification);
        TSharedPtr<FCreateNamespaceRequest> WithLeaveNotification(const TSharedPtr<Model::FNotificationSetting> LeaveNotification);
        TSharedPtr<FCreateNamespaceRequest> WithChangeMemberNotification(const TSharedPtr<Model::FNotificationSetting> ChangeMemberNotification);
        TSharedPtr<FCreateNamespaceRequest> WithReceiveRequestNotification(const TSharedPtr<Model::FNotificationSetting> ReceiveRequestNotification);
        TSharedPtr<FCreateNamespaceRequest> WithRemoveRequestNotification(const TSharedPtr<Model::FNotificationSetting> RemoveRequestNotification);
        TSharedPtr<FCreateNamespaceRequest> WithCreateGuildScript(const TSharedPtr<Model::FScriptSetting> CreateGuildScript);
        TSharedPtr<FCreateNamespaceRequest> WithJoinGuildScript(const TSharedPtr<Model::FScriptSetting> JoinGuildScript);
        TSharedPtr<FCreateNamespaceRequest> WithLeaveGuildScript(const TSharedPtr<Model::FScriptSetting> LeaveGuildScript);
        TSharedPtr<FCreateNamespaceRequest> WithChangeRoleScript(const TSharedPtr<Model::FScriptSetting> ChangeRoleScript);
        TSharedPtr<FCreateNamespaceRequest> WithLogSetting(const TSharedPtr<Model::FLogSetting> LogSetting);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetDescription() const;
        TSharedPtr<Model::FNotificationSetting> GetJoinNotification() const;
        TSharedPtr<Model::FNotificationSetting> GetLeaveNotification() const;
        TSharedPtr<Model::FNotificationSetting> GetChangeMemberNotification() const;
        TSharedPtr<Model::FNotificationSetting> GetReceiveRequestNotification() const;
        TSharedPtr<Model::FNotificationSetting> GetRemoveRequestNotification() const;
        TSharedPtr<Model::FScriptSetting> GetCreateGuildScript() const;
        TSharedPtr<Model::FScriptSetting> GetJoinGuildScript() const;
        TSharedPtr<Model::FScriptSetting> GetLeaveGuildScript() const;
        TSharedPtr<Model::FScriptSetting> GetChangeRoleScript() const;
        TSharedPtr<Model::FLogSetting> GetLogSetting() const;

        static TSharedPtr<FCreateNamespaceRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequestPtr;
}