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
#include "TransactionSetting.h"
#include "ScriptSetting.h"
#include "NotificationSetting.h"
#include "LogSetting.h"

namespace Gs2::Chat::Model
{
    class GS2CHAT_API FNamespace final : public FGs2Object, public TSharedFromThis<FNamespace>
    {
        TOptional<FString> NamespaceIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> DescriptionValue;
        TSharedPtr<FTransactionSetting> TransactionSettingValue;
        TOptional<bool> AllowCreateRoomValue;
        TOptional<int32> MessageLifeTimeDaysValue;
        TSharedPtr<FScriptSetting> PostMessageScriptValue;
        TSharedPtr<FScriptSetting> CreateRoomScriptValue;
        TSharedPtr<FScriptSetting> DeleteRoomScriptValue;
        TSharedPtr<FScriptSetting> SubscribeRoomScriptValue;
        TSharedPtr<FScriptSetting> UnsubscribeRoomScriptValue;
        TSharedPtr<FNotificationSetting> PostNotificationValue;
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
        TSharedPtr<FNamespace> WithTransactionSetting(const TSharedPtr<FTransactionSetting> TransactionSetting);
        TSharedPtr<FNamespace> WithAllowCreateRoom(const TOptional<bool> AllowCreateRoom);
        TSharedPtr<FNamespace> WithMessageLifeTimeDays(const TOptional<int32> MessageLifeTimeDays);
        TSharedPtr<FNamespace> WithPostMessageScript(const TSharedPtr<FScriptSetting> PostMessageScript);
        TSharedPtr<FNamespace> WithCreateRoomScript(const TSharedPtr<FScriptSetting> CreateRoomScript);
        TSharedPtr<FNamespace> WithDeleteRoomScript(const TSharedPtr<FScriptSetting> DeleteRoomScript);
        TSharedPtr<FNamespace> WithSubscribeRoomScript(const TSharedPtr<FScriptSetting> SubscribeRoomScript);
        TSharedPtr<FNamespace> WithUnsubscribeRoomScript(const TSharedPtr<FScriptSetting> UnsubscribeRoomScript);
        TSharedPtr<FNamespace> WithPostNotification(const TSharedPtr<FNotificationSetting> PostNotification);
        TSharedPtr<FNamespace> WithLogSetting(const TSharedPtr<FLogSetting> LogSetting);
        TSharedPtr<FNamespace> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FNamespace> WithUpdatedAt(const TOptional<int64> UpdatedAt);
        TSharedPtr<FNamespace> WithRevision(const TOptional<int64> Revision);

        TOptional<FString> GetNamespaceId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetDescription() const;
        TSharedPtr<FTransactionSetting> GetTransactionSetting() const;
        TOptional<bool> GetAllowCreateRoom() const;
        FString GetAllowCreateRoomString() const;
        TOptional<int32> GetMessageLifeTimeDays() const;
        FString GetMessageLifeTimeDaysString() const;
        TSharedPtr<FScriptSetting> GetPostMessageScript() const;
        TSharedPtr<FScriptSetting> GetCreateRoomScript() const;
        TSharedPtr<FScriptSetting> GetDeleteRoomScript() const;
        TSharedPtr<FScriptSetting> GetSubscribeRoomScript() const;
        TSharedPtr<FScriptSetting> GetUnsubscribeRoomScript() const;
        TSharedPtr<FNotificationSetting> GetPostNotification() const;
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