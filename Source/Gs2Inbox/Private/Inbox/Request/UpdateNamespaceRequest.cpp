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

#include "Inbox/Request/UpdateNamespaceRequest.h"

namespace Gs2::Inbox::Request
{
    FUpdateNamespaceRequest::FUpdateNamespaceRequest():
        NamespaceNameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        IsAutomaticDeletingEnabledValue(TOptional<bool>()),
        TransactionSettingValue(nullptr),
        ReceiveMessageScriptValue(nullptr),
        ReadMessageScriptValue(nullptr),
        DeleteMessageScriptValue(nullptr),
        ReceiveNotificationValue(nullptr),
        LogSettingValue(nullptr),
        QueueNamespaceIdValue(TOptional<FString>()),
        KeyIdValue(TOptional<FString>())
    {
    }

    FUpdateNamespaceRequest::FUpdateNamespaceRequest(
        const FUpdateNamespaceRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        DescriptionValue(From.DescriptionValue),
        IsAutomaticDeletingEnabledValue(From.IsAutomaticDeletingEnabledValue),
        TransactionSettingValue(From.TransactionSettingValue),
        ReceiveMessageScriptValue(From.ReceiveMessageScriptValue),
        ReadMessageScriptValue(From.ReadMessageScriptValue),
        DeleteMessageScriptValue(From.DeleteMessageScriptValue),
        ReceiveNotificationValue(From.ReceiveNotificationValue),
        LogSettingValue(From.LogSettingValue),
        QueueNamespaceIdValue(From.QueueNamespaceIdValue),
        KeyIdValue(From.KeyIdValue)
    {
    }

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::WithIsAutomaticDeletingEnabled(
        const TOptional<bool> IsAutomaticDeletingEnabled
    )
    {
        this->IsAutomaticDeletingEnabledValue = IsAutomaticDeletingEnabled;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::WithTransactionSetting(
        const TSharedPtr<Model::FTransactionSetting> TransactionSetting
    )
    {
        this->TransactionSettingValue = TransactionSetting;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::WithReceiveMessageScript(
        const TSharedPtr<Model::FScriptSetting> ReceiveMessageScript
    )
    {
        this->ReceiveMessageScriptValue = ReceiveMessageScript;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::WithReadMessageScript(
        const TSharedPtr<Model::FScriptSetting> ReadMessageScript
    )
    {
        this->ReadMessageScriptValue = ReadMessageScript;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::WithDeleteMessageScript(
        const TSharedPtr<Model::FScriptSetting> DeleteMessageScript
    )
    {
        this->DeleteMessageScriptValue = DeleteMessageScript;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::WithReceiveNotification(
        const TSharedPtr<Model::FNotificationSetting> ReceiveNotification
    )
    {
        this->ReceiveNotificationValue = ReceiveNotification;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::WithLogSetting(
        const TSharedPtr<Model::FLogSetting> LogSetting
    )
    {
        this->LogSettingValue = LogSetting;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::WithQueueNamespaceId(
        const TOptional<FString> QueueNamespaceId
    )
    {
        this->QueueNamespaceIdValue = QueueNamespaceId;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::WithKeyId(
        const TOptional<FString> KeyId
    )
    {
        this->KeyIdValue = KeyId;
        return SharedThis(this);
    }

    TOptional<FString> FUpdateNamespaceRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FUpdateNamespaceRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FUpdateNamespaceRequest::GetDescription() const
    {
        return DescriptionValue;
    }

    TOptional<bool> FUpdateNamespaceRequest::GetIsAutomaticDeletingEnabled() const
    {
        return IsAutomaticDeletingEnabledValue;
    }

    FString FUpdateNamespaceRequest::GetIsAutomaticDeletingEnabledString() const
    {
        if (!IsAutomaticDeletingEnabledValue.IsSet())
        {
            return FString("null");
        }
        return FString(IsAutomaticDeletingEnabledValue.GetValue() ? "true" : "false");
    }

    TSharedPtr<Model::FTransactionSetting> FUpdateNamespaceRequest::GetTransactionSetting() const
    {
        if (!TransactionSettingValue.IsValid())
        {
            return nullptr;
        }
        return TransactionSettingValue;
    }

    TSharedPtr<Model::FScriptSetting> FUpdateNamespaceRequest::GetReceiveMessageScript() const
    {
        if (!ReceiveMessageScriptValue.IsValid())
        {
            return nullptr;
        }
        return ReceiveMessageScriptValue;
    }

    TSharedPtr<Model::FScriptSetting> FUpdateNamespaceRequest::GetReadMessageScript() const
    {
        if (!ReadMessageScriptValue.IsValid())
        {
            return nullptr;
        }
        return ReadMessageScriptValue;
    }

    TSharedPtr<Model::FScriptSetting> FUpdateNamespaceRequest::GetDeleteMessageScript() const
    {
        if (!DeleteMessageScriptValue.IsValid())
        {
            return nullptr;
        }
        return DeleteMessageScriptValue;
    }

    TSharedPtr<Model::FNotificationSetting> FUpdateNamespaceRequest::GetReceiveNotification() const
    {
        if (!ReceiveNotificationValue.IsValid())
        {
            return nullptr;
        }
        return ReceiveNotificationValue;
    }

    TSharedPtr<Model::FLogSetting> FUpdateNamespaceRequest::GetLogSetting() const
    {
        if (!LogSettingValue.IsValid())
        {
            return nullptr;
        }
        return LogSettingValue;
    }

    TOptional<FString> FUpdateNamespaceRequest::GetQueueNamespaceId() const
    {
        return QueueNamespaceIdValue;
    }

    TOptional<FString> FUpdateNamespaceRequest::GetKeyId() const
    {
        return KeyIdValue;
    }

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FUpdateNamespaceRequest>()
            ->WithContextStack(Data->HasField(ANSI_TO_TCHAR("contextStack")) ? TOptional<FString>(Data->GetStringField(ANSI_TO_TCHAR("contextStack"))) : TOptional<FString>())
            ->WithNamespaceName(Data->HasField(ANSI_TO_TCHAR("namespaceName")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("namespaceName"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithDescription(Data->HasField(ANSI_TO_TCHAR("description")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("description"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithIsAutomaticDeletingEnabled(Data->HasField(ANSI_TO_TCHAR("isAutomaticDeletingEnabled")) ? [Data]() -> TOptional<bool>
              {
                  bool v;
                    if (Data->TryGetBoolField(ANSI_TO_TCHAR("isAutomaticDeletingEnabled"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<bool>();
              }() : TOptional<bool>())
          ->WithTransactionSetting(Data->HasField(ANSI_TO_TCHAR("transactionSetting")) ? [Data]() -> Model::FTransactionSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("transactionSetting")))
                  {
                      return nullptr;
                  }
                  return Model::FTransactionSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("transactionSetting")));
              }() : nullptr)
          ->WithReceiveMessageScript(Data->HasField(ANSI_TO_TCHAR("receiveMessageScript")) ? [Data]() -> Model::FScriptSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("receiveMessageScript")))
                  {
                      return nullptr;
                  }
                  return Model::FScriptSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("receiveMessageScript")));
              }() : nullptr)
          ->WithReadMessageScript(Data->HasField(ANSI_TO_TCHAR("readMessageScript")) ? [Data]() -> Model::FScriptSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("readMessageScript")))
                  {
                      return nullptr;
                  }
                  return Model::FScriptSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("readMessageScript")));
              }() : nullptr)
          ->WithDeleteMessageScript(Data->HasField(ANSI_TO_TCHAR("deleteMessageScript")) ? [Data]() -> Model::FScriptSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("deleteMessageScript")))
                  {
                      return nullptr;
                  }
                  return Model::FScriptSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("deleteMessageScript")));
              }() : nullptr)
          ->WithReceiveNotification(Data->HasField(ANSI_TO_TCHAR("receiveNotification")) ? [Data]() -> Model::FNotificationSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("receiveNotification")))
                  {
                      return nullptr;
                  }
                  return Model::FNotificationSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("receiveNotification")));
              }() : nullptr)
          ->WithLogSetting(Data->HasField(ANSI_TO_TCHAR("logSetting")) ? [Data]() -> Model::FLogSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("logSetting")))
                  {
                      return nullptr;
                  }
                  return Model::FLogSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("logSetting")));
              }() : nullptr)
            ->WithQueueNamespaceId(Data->HasField(ANSI_TO_TCHAR("queueNamespaceId")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("queueNamespaceId"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithKeyId(Data->HasField(ANSI_TO_TCHAR("keyId")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("keyId"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FUpdateNamespaceRequest::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ContextStackValue.IsSet())
        {
            JsonRootObject->SetStringField("contextStack", ContextStackValue.GetValue());
        }
        if (NamespaceNameValue.IsSet())
        {
            JsonRootObject->SetStringField("namespaceName", NamespaceNameValue.GetValue());
        }
        if (DescriptionValue.IsSet())
        {
            JsonRootObject->SetStringField("description", DescriptionValue.GetValue());
        }
        if (IsAutomaticDeletingEnabledValue.IsSet())
        {
            JsonRootObject->SetBoolField("isAutomaticDeletingEnabled", IsAutomaticDeletingEnabledValue.GetValue());
        }
        if (TransactionSettingValue != nullptr && TransactionSettingValue.IsValid())
        {
            JsonRootObject->SetObjectField("transactionSetting", TransactionSettingValue->ToJson());
        }
        if (ReceiveMessageScriptValue != nullptr && ReceiveMessageScriptValue.IsValid())
        {
            JsonRootObject->SetObjectField("receiveMessageScript", ReceiveMessageScriptValue->ToJson());
        }
        if (ReadMessageScriptValue != nullptr && ReadMessageScriptValue.IsValid())
        {
            JsonRootObject->SetObjectField("readMessageScript", ReadMessageScriptValue->ToJson());
        }
        if (DeleteMessageScriptValue != nullptr && DeleteMessageScriptValue.IsValid())
        {
            JsonRootObject->SetObjectField("deleteMessageScript", DeleteMessageScriptValue->ToJson());
        }
        if (ReceiveNotificationValue != nullptr && ReceiveNotificationValue.IsValid())
        {
            JsonRootObject->SetObjectField("receiveNotification", ReceiveNotificationValue->ToJson());
        }
        if (LogSettingValue != nullptr && LogSettingValue.IsValid())
        {
            JsonRootObject->SetObjectField("logSetting", LogSettingValue->ToJson());
        }
        if (QueueNamespaceIdValue.IsSet())
        {
            JsonRootObject->SetStringField("queueNamespaceId", QueueNamespaceIdValue.GetValue());
        }
        if (KeyIdValue.IsSet())
        {
            JsonRootObject->SetStringField("keyId", KeyIdValue.GetValue());
        }
        return JsonRootObject;
    }
}