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

namespace Gs2::Chat::Request
{
    class FUpdateNamespaceRequest;

    class GS2CHAT_API FUpdateNamespaceRequest final : public TSharedFromThis<FUpdateNamespaceRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> DescriptionValue;
        TOptional<bool> AllowCreateRoomValue;
        TSharedPtr<Model::FScriptSetting> PostMessageScriptValue;
        TSharedPtr<Model::FScriptSetting> CreateRoomScriptValue;
        TSharedPtr<Model::FScriptSetting> DeleteRoomScriptValue;
        TSharedPtr<Model::FScriptSetting> SubscribeRoomScriptValue;
        TSharedPtr<Model::FScriptSetting> UnsubscribeRoomScriptValue;
        TSharedPtr<Model::FNotificationSetting> PostNotificationValue;
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
        TSharedPtr<FUpdateNamespaceRequest> WithAllowCreateRoom(const TOptional<bool> AllowCreateRoom);
        TSharedPtr<FUpdateNamespaceRequest> WithPostMessageScript(const TSharedPtr<Model::FScriptSetting> PostMessageScript);
        TSharedPtr<FUpdateNamespaceRequest> WithCreateRoomScript(const TSharedPtr<Model::FScriptSetting> CreateRoomScript);
        TSharedPtr<FUpdateNamespaceRequest> WithDeleteRoomScript(const TSharedPtr<Model::FScriptSetting> DeleteRoomScript);
        TSharedPtr<FUpdateNamespaceRequest> WithSubscribeRoomScript(const TSharedPtr<Model::FScriptSetting> SubscribeRoomScript);
        TSharedPtr<FUpdateNamespaceRequest> WithUnsubscribeRoomScript(const TSharedPtr<Model::FScriptSetting> UnsubscribeRoomScript);
        TSharedPtr<FUpdateNamespaceRequest> WithPostNotification(const TSharedPtr<Model::FNotificationSetting> PostNotification);
        TSharedPtr<FUpdateNamespaceRequest> WithLogSetting(const TSharedPtr<Model::FLogSetting> LogSetting);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetDescription() const;
        TOptional<bool> GetAllowCreateRoom() const;
        FString GetAllowCreateRoomString() const;
        TSharedPtr<Model::FScriptSetting> GetPostMessageScript() const;
        TSharedPtr<Model::FScriptSetting> GetCreateRoomScript() const;
        TSharedPtr<Model::FScriptSetting> GetDeleteRoomScript() const;
        TSharedPtr<Model::FScriptSetting> GetSubscribeRoomScript() const;
        TSharedPtr<Model::FScriptSetting> GetUnsubscribeRoomScript() const;
        TSharedPtr<Model::FNotificationSetting> GetPostNotification() const;
        TSharedPtr<Model::FLogSetting> GetLogSetting() const;

        static TSharedPtr<FUpdateNamespaceRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequestPtr;
}