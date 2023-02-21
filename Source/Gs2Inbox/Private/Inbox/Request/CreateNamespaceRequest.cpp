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

#include "Inbox/Request/CreateNamespaceRequest.h"

namespace Gs2::Inbox::Request
{
    FCreateNamespaceRequest::FCreateNamespaceRequest():
        NameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        IsAutomaticDeletingEnabledValue(TOptional<bool>()),
        TransactionSettingValue(nullptr),
        ReceiveMessageScriptValue(nullptr),
        ReadMessageScriptValue(nullptr),
        DeleteMessageScriptValue(nullptr),
        ReceiveNotificationValue(nullptr),
        LogSettingValue(nullptr)
    {
    }

    FCreateNamespaceRequest::FCreateNamespaceRequest(
        const FCreateNamespaceRequest& From
    ):
        NameValue(From.NameValue),
        DescriptionValue(From.DescriptionValue),
        IsAutomaticDeletingEnabledValue(From.IsAutomaticDeletingEnabledValue),
        TransactionSettingValue(From.TransactionSettingValue),
        ReceiveMessageScriptValue(From.ReceiveMessageScriptValue),
        ReadMessageScriptValue(From.ReadMessageScriptValue),
        DeleteMessageScriptValue(From.DeleteMessageScriptValue),
        ReceiveNotificationValue(From.ReceiveNotificationValue),
        LogSettingValue(From.LogSettingValue)
    {
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
        return SharedThis(this);
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithIsAutomaticDeletingEnabled(
        const TOptional<bool> IsAutomaticDeletingEnabled
    )
    {
        this->IsAutomaticDeletingEnabledValue = IsAutomaticDeletingEnabled;
        return SharedThis(this);
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithTransactionSetting(
        const TSharedPtr<Model::FTransactionSetting> TransactionSetting
    )
    {
        this->TransactionSettingValue = TransactionSetting;
        return SharedThis(this);
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithReceiveMessageScript(
        const TSharedPtr<Model::FScriptSetting> ReceiveMessageScript
    )
    {
        this->ReceiveMessageScriptValue = ReceiveMessageScript;
        return SharedThis(this);
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithReadMessageScript(
        const TSharedPtr<Model::FScriptSetting> ReadMessageScript
    )
    {
        this->ReadMessageScriptValue = ReadMessageScript;
        return SharedThis(this);
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithDeleteMessageScript(
        const TSharedPtr<Model::FScriptSetting> DeleteMessageScript
    )
    {
        this->DeleteMessageScriptValue = DeleteMessageScript;
        return SharedThis(this);
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithReceiveNotification(
        const TSharedPtr<Model::FNotificationSetting> ReceiveNotification
    )
    {
        this->ReceiveNotificationValue = ReceiveNotification;
        return SharedThis(this);
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithLogSetting(
        const TSharedPtr<Model::FLogSetting> LogSetting
    )
    {
        this->LogSettingValue = LogSetting;
        return SharedThis(this);
    }

    TOptional<FString> FCreateNamespaceRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FCreateNamespaceRequest::GetName() const
    {
        return NameValue;
    }

    TOptional<FString> FCreateNamespaceRequest::GetDescription() const
    {
        return DescriptionValue;
    }

    TOptional<bool> FCreateNamespaceRequest::GetIsAutomaticDeletingEnabled() const
    {
        return IsAutomaticDeletingEnabledValue;
    }

    FString FCreateNamespaceRequest::GetIsAutomaticDeletingEnabledString() const
    {
        if (!IsAutomaticDeletingEnabledValue.IsSet())
        {
            return FString("null");
        }
        return FString(IsAutomaticDeletingEnabledValue.GetValue() ? "true" : "false");
    }

    TSharedPtr<Model::FTransactionSetting> FCreateNamespaceRequest::GetTransactionSetting() const
    {
        if (!TransactionSettingValue.IsValid())
        {
            return nullptr;
        }
        return TransactionSettingValue;
    }

    TSharedPtr<Model::FScriptSetting> FCreateNamespaceRequest::GetReceiveMessageScript() const
    {
        if (!ReceiveMessageScriptValue.IsValid())
        {
            return nullptr;
        }
        return ReceiveMessageScriptValue;
    }

    TSharedPtr<Model::FScriptSetting> FCreateNamespaceRequest::GetReadMessageScript() const
    {
        if (!ReadMessageScriptValue.IsValid())
        {
            return nullptr;
        }
        return ReadMessageScriptValue;
    }

    TSharedPtr<Model::FScriptSetting> FCreateNamespaceRequest::GetDeleteMessageScript() const
    {
        if (!DeleteMessageScriptValue.IsValid())
        {
            return nullptr;
        }
        return DeleteMessageScriptValue;
    }

    TSharedPtr<Model::FNotificationSetting> FCreateNamespaceRequest::GetReceiveNotification() const
    {
        if (!ReceiveNotificationValue.IsValid())
        {
            return nullptr;
        }
        return ReceiveNotificationValue;
    }

    TSharedPtr<Model::FLogSetting> FCreateNamespaceRequest::GetLogSetting() const
    {
        if (!LogSettingValue.IsValid())
        {
            return nullptr;
        }
        return LogSettingValue;
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FCreateNamespaceRequest>()
            ->WithContextStack(Data->HasField("contextStack") ? TOptional<FString>(Data->GetStringField("contextStack")) : TOptional<FString>())
            ->WithName(Data->HasField("name") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("name", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithDescription(Data->HasField("description") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("description", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithIsAutomaticDeletingEnabled(Data->HasField("isAutomaticDeletingEnabled") ? [Data]() -> TOptional<bool>
              {
                  bool v;
                    if (Data->TryGetBoolField("isAutomaticDeletingEnabled", v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<bool>();
              }() : TOptional<bool>())
          ->WithTransactionSetting(Data->HasField("transactionSetting") ? [Data]() -> Model::FTransactionSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>("transactionSetting"))
                  {
                      return nullptr;
                  }
                  return Model::FTransactionSetting::FromJson(Data->GetObjectField("transactionSetting"));
             }() : nullptr)
          ->WithReceiveMessageScript(Data->HasField("receiveMessageScript") ? [Data]() -> Model::FScriptSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>("receiveMessageScript"))
                  {
                      return nullptr;
                  }
                  return Model::FScriptSetting::FromJson(Data->GetObjectField("receiveMessageScript"));
             }() : nullptr)
          ->WithReadMessageScript(Data->HasField("readMessageScript") ? [Data]() -> Model::FScriptSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>("readMessageScript"))
                  {
                      return nullptr;
                  }
                  return Model::FScriptSetting::FromJson(Data->GetObjectField("readMessageScript"));
             }() : nullptr)
          ->WithDeleteMessageScript(Data->HasField("deleteMessageScript") ? [Data]() -> Model::FScriptSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>("deleteMessageScript"))
                  {
                      return nullptr;
                  }
                  return Model::FScriptSetting::FromJson(Data->GetObjectField("deleteMessageScript"));
             }() : nullptr)
          ->WithReceiveNotification(Data->HasField("receiveNotification") ? [Data]() -> Model::FNotificationSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>("receiveNotification"))
                  {
                      return nullptr;
                  }
                  return Model::FNotificationSetting::FromJson(Data->GetObjectField("receiveNotification"));
             }() : nullptr)
          ->WithLogSetting(Data->HasField("logSetting") ? [Data]() -> Model::FLogSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>("logSetting"))
                  {
                      return nullptr;
                  }
                  return Model::FLogSetting::FromJson(Data->GetObjectField("logSetting"));
             }() : nullptr);
    }

    TSharedPtr<FJsonObject> FCreateNamespaceRequest::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ContextStackValue.IsSet())
        {
            JsonRootObject->SetStringField("contextStack", ContextStackValue.GetValue());
        }
        if (NameValue.IsSet())
        {
            JsonRootObject->SetStringField("name", NameValue.GetValue());
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
        return JsonRootObject;
    }
}