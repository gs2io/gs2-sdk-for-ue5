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
#include "../Model/TransactionSetting.h"
#include "../Model/ScriptSetting.h"
#include "../Model/NotificationSetting.h"
#include "../Model/LogSetting.h"

namespace Gs2::Inbox::Request
{
    class FUpdateNamespaceRequest;

    class GS2INBOX_API FUpdateNamespaceRequest final : public TSharedFromThis<FUpdateNamespaceRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> DescriptionValue;
        TOptional<bool> IsAutomaticDeletingEnabledValue;
        TSharedPtr<Model::FTransactionSetting> TransactionSettingValue;
        TSharedPtr<Model::FScriptSetting> ReceiveMessageScriptValue;
        TSharedPtr<Model::FScriptSetting> ReadMessageScriptValue;
        TSharedPtr<Model::FScriptSetting> DeleteMessageScriptValue;
        TSharedPtr<Model::FNotificationSetting> ReceiveNotificationValue;
        TSharedPtr<Model::FLogSetting> LogSettingValue;
        TOptional<FString> QueueNamespaceIdValue;
        TOptional<FString> KeyIdValue;
        
    public:
        
        FUpdateNamespaceRequest();
        FUpdateNamespaceRequest(
            const FUpdateNamespaceRequest& From
        );
        ~FUpdateNamespaceRequest() = default;

        TSharedPtr<FUpdateNamespaceRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FUpdateNamespaceRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FUpdateNamespaceRequest> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FUpdateNamespaceRequest> WithIsAutomaticDeletingEnabled(const TOptional<bool> IsAutomaticDeletingEnabled);
        TSharedPtr<FUpdateNamespaceRequest> WithTransactionSetting(const TSharedPtr<Model::FTransactionSetting> TransactionSetting);
        TSharedPtr<FUpdateNamespaceRequest> WithReceiveMessageScript(const TSharedPtr<Model::FScriptSetting> ReceiveMessageScript);
        TSharedPtr<FUpdateNamespaceRequest> WithReadMessageScript(const TSharedPtr<Model::FScriptSetting> ReadMessageScript);
        TSharedPtr<FUpdateNamespaceRequest> WithDeleteMessageScript(const TSharedPtr<Model::FScriptSetting> DeleteMessageScript);
        TSharedPtr<FUpdateNamespaceRequest> WithReceiveNotification(const TSharedPtr<Model::FNotificationSetting> ReceiveNotification);
        TSharedPtr<FUpdateNamespaceRequest> WithLogSetting(const TSharedPtr<Model::FLogSetting> LogSetting);
        TSharedPtr<FUpdateNamespaceRequest> WithQueueNamespaceId(const TOptional<FString> QueueNamespaceId);
        TSharedPtr<FUpdateNamespaceRequest> WithKeyId(const TOptional<FString> KeyId);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetDescription() const;
        TOptional<bool> GetIsAutomaticDeletingEnabled() const;
        FString GetIsAutomaticDeletingEnabledString() const;
        TSharedPtr<Model::FTransactionSetting> GetTransactionSetting() const;
        TSharedPtr<Model::FScriptSetting> GetReceiveMessageScript() const;
        TSharedPtr<Model::FScriptSetting> GetReadMessageScript() const;
        TSharedPtr<Model::FScriptSetting> GetDeleteMessageScript() const;
        TSharedPtr<Model::FNotificationSetting> GetReceiveNotification() const;
        TSharedPtr<Model::FLogSetting> GetLogSetting() const;
        TOptional<FString> GetQueueNamespaceId() const;
        TOptional<FString> GetKeyId() const;

        static TSharedPtr<FUpdateNamespaceRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequestPtr;
}