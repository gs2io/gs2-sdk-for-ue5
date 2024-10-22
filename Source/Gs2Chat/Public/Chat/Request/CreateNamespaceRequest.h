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

namespace Gs2::Chat::Request
{
    class FCreateNamespaceRequest;

    class GS2CHAT_API FCreateNamespaceRequest final : public TSharedFromThis<FCreateNamespaceRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NameValue;
        TOptional<FString> DescriptionValue;
        TOptional<bool> AllowCreateRoomValue;
        TOptional<int32> MessageLifeTimeDaysValue;
        TSharedPtr<Model::FScriptSetting> PostMessageScriptValue;
        TSharedPtr<Model::FScriptSetting> CreateRoomScriptValue;
        TSharedPtr<Model::FScriptSetting> DeleteRoomScriptValue;
        TSharedPtr<Model::FScriptSetting> SubscribeRoomScriptValue;
        TSharedPtr<Model::FScriptSetting> UnsubscribeRoomScriptValue;
        TSharedPtr<Model::FNotificationSetting> PostNotificationValue;
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
        TSharedPtr<FCreateNamespaceRequest> WithAllowCreateRoom(const TOptional<bool> AllowCreateRoom);
        TSharedPtr<FCreateNamespaceRequest> WithMessageLifeTimeDays(const TOptional<int32> MessageLifeTimeDays);
        TSharedPtr<FCreateNamespaceRequest> WithPostMessageScript(const TSharedPtr<Model::FScriptSetting> PostMessageScript);
        TSharedPtr<FCreateNamespaceRequest> WithCreateRoomScript(const TSharedPtr<Model::FScriptSetting> CreateRoomScript);
        TSharedPtr<FCreateNamespaceRequest> WithDeleteRoomScript(const TSharedPtr<Model::FScriptSetting> DeleteRoomScript);
        TSharedPtr<FCreateNamespaceRequest> WithSubscribeRoomScript(const TSharedPtr<Model::FScriptSetting> SubscribeRoomScript);
        TSharedPtr<FCreateNamespaceRequest> WithUnsubscribeRoomScript(const TSharedPtr<Model::FScriptSetting> UnsubscribeRoomScript);
        TSharedPtr<FCreateNamespaceRequest> WithPostNotification(const TSharedPtr<Model::FNotificationSetting> PostNotification);
        TSharedPtr<FCreateNamespaceRequest> WithLogSetting(const TSharedPtr<Model::FLogSetting> LogSetting);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetDescription() const;
        TOptional<bool> GetAllowCreateRoom() const;
        FString GetAllowCreateRoomString() const;
        TOptional<int32> GetMessageLifeTimeDays() const;
        FString GetMessageLifeTimeDaysString() const;
        TSharedPtr<Model::FScriptSetting> GetPostMessageScript() const;
        TSharedPtr<Model::FScriptSetting> GetCreateRoomScript() const;
        TSharedPtr<Model::FScriptSetting> GetDeleteRoomScript() const;
        TSharedPtr<Model::FScriptSetting> GetSubscribeRoomScript() const;
        TSharedPtr<Model::FScriptSetting> GetUnsubscribeRoomScript() const;
        TSharedPtr<Model::FNotificationSetting> GetPostNotification() const;
        TSharedPtr<Model::FLogSetting> GetLogSetting() const;

        static TSharedPtr<FCreateNamespaceRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FCreateNamespaceRequest, ESPMode::ThreadSafe> FCreateNamespaceRequestPtr;
}