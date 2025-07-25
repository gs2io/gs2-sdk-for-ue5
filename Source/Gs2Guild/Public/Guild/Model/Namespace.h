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
#include "NotificationSetting.h"
#include "ScriptSetting.h"
#include "LogSetting.h"

namespace Gs2::Guild::Model
{
    class GS2GUILD_API FNamespace final : public FGs2Object, public TSharedFromThis<FNamespace>
    {
        TOptional<FString> NamespaceIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> DescriptionValue;
        TSharedPtr<FNotificationSetting> ChangeNotificationValue;
        TSharedPtr<FNotificationSetting> JoinNotificationValue;
        TSharedPtr<FNotificationSetting> LeaveNotificationValue;
        TSharedPtr<FNotificationSetting> ChangeMemberNotificationValue;
        TSharedPtr<FNotificationSetting> ReceiveRequestNotificationValue;
        TSharedPtr<FNotificationSetting> RemoveRequestNotificationValue;
        TSharedPtr<FScriptSetting> CreateGuildScriptValue;
        TSharedPtr<FScriptSetting> UpdateGuildScriptValue;
        TSharedPtr<FScriptSetting> JoinGuildScriptValue;
        TSharedPtr<FScriptSetting> ReceiveJoinRequestScriptValue;
        TSharedPtr<FScriptSetting> LeaveGuildScriptValue;
        TSharedPtr<FScriptSetting> ChangeRoleScriptValue;
        TSharedPtr<FScriptSetting> DeleteGuildScriptValue;
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
        TSharedPtr<FNamespace> WithChangeNotification(const TSharedPtr<FNotificationSetting> ChangeNotification);
        TSharedPtr<FNamespace> WithJoinNotification(const TSharedPtr<FNotificationSetting> JoinNotification);
        TSharedPtr<FNamespace> WithLeaveNotification(const TSharedPtr<FNotificationSetting> LeaveNotification);
        TSharedPtr<FNamespace> WithChangeMemberNotification(const TSharedPtr<FNotificationSetting> ChangeMemberNotification);
        TSharedPtr<FNamespace> WithReceiveRequestNotification(const TSharedPtr<FNotificationSetting> ReceiveRequestNotification);
        TSharedPtr<FNamespace> WithRemoveRequestNotification(const TSharedPtr<FNotificationSetting> RemoveRequestNotification);
        TSharedPtr<FNamespace> WithCreateGuildScript(const TSharedPtr<FScriptSetting> CreateGuildScript);
        TSharedPtr<FNamespace> WithUpdateGuildScript(const TSharedPtr<FScriptSetting> UpdateGuildScript);
        TSharedPtr<FNamespace> WithJoinGuildScript(const TSharedPtr<FScriptSetting> JoinGuildScript);
        TSharedPtr<FNamespace> WithReceiveJoinRequestScript(const TSharedPtr<FScriptSetting> ReceiveJoinRequestScript);
        TSharedPtr<FNamespace> WithLeaveGuildScript(const TSharedPtr<FScriptSetting> LeaveGuildScript);
        TSharedPtr<FNamespace> WithChangeRoleScript(const TSharedPtr<FScriptSetting> ChangeRoleScript);
        TSharedPtr<FNamespace> WithDeleteGuildScript(const TSharedPtr<FScriptSetting> DeleteGuildScript);
        TSharedPtr<FNamespace> WithLogSetting(const TSharedPtr<FLogSetting> LogSetting);
        TSharedPtr<FNamespace> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FNamespace> WithUpdatedAt(const TOptional<int64> UpdatedAt);
        TSharedPtr<FNamespace> WithRevision(const TOptional<int64> Revision);

        TOptional<FString> GetNamespaceId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetDescription() const;
        TSharedPtr<FNotificationSetting> GetChangeNotification() const;
        TSharedPtr<FNotificationSetting> GetJoinNotification() const;
        TSharedPtr<FNotificationSetting> GetLeaveNotification() const;
        TSharedPtr<FNotificationSetting> GetChangeMemberNotification() const;
        TSharedPtr<FNotificationSetting> GetReceiveRequestNotification() const;
        TSharedPtr<FNotificationSetting> GetRemoveRequestNotification() const;
        TSharedPtr<FScriptSetting> GetCreateGuildScript() const;
        TSharedPtr<FScriptSetting> GetUpdateGuildScript() const;
        TSharedPtr<FScriptSetting> GetJoinGuildScript() const;
        TSharedPtr<FScriptSetting> GetReceiveJoinRequestScript() const;
        TSharedPtr<FScriptSetting> GetLeaveGuildScript() const;
        TSharedPtr<FScriptSetting> GetChangeRoleScript() const;
        TSharedPtr<FScriptSetting> GetDeleteGuildScript() const;
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