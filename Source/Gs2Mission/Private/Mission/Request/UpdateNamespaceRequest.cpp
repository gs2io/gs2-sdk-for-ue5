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

#include "Mission/Request/UpdateNamespaceRequest.h"

namespace Gs2::Mission::Request
{
    FUpdateNamespaceRequest::FUpdateNamespaceRequest():
        NamespaceNameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        TransactionSettingValue(nullptr),
        MissionCompleteScriptValue(nullptr),
        CounterIncrementScriptValue(nullptr),
        ReceiveRewardsScriptValue(nullptr),
        CompleteNotificationValue(nullptr),
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
        TransactionSettingValue(From.TransactionSettingValue),
        MissionCompleteScriptValue(From.MissionCompleteScriptValue),
        CounterIncrementScriptValue(From.CounterIncrementScriptValue),
        ReceiveRewardsScriptValue(From.ReceiveRewardsScriptValue),
        CompleteNotificationValue(From.CompleteNotificationValue),
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

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::WithTransactionSetting(
        const TSharedPtr<Model::FTransactionSetting> TransactionSetting
    )
    {
        this->TransactionSettingValue = TransactionSetting;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::WithMissionCompleteScript(
        const TSharedPtr<Model::FScriptSetting> MissionCompleteScript
    )
    {
        this->MissionCompleteScriptValue = MissionCompleteScript;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::WithCounterIncrementScript(
        const TSharedPtr<Model::FScriptSetting> CounterIncrementScript
    )
    {
        this->CounterIncrementScriptValue = CounterIncrementScript;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::WithReceiveRewardsScript(
        const TSharedPtr<Model::FScriptSetting> ReceiveRewardsScript
    )
    {
        this->ReceiveRewardsScriptValue = ReceiveRewardsScript;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::WithCompleteNotification(
        const TSharedPtr<Model::FNotificationSetting> CompleteNotification
    )
    {
        this->CompleteNotificationValue = CompleteNotification;
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

    TSharedPtr<Model::FTransactionSetting> FUpdateNamespaceRequest::GetTransactionSetting() const
    {
        if (!TransactionSettingValue.IsValid())
        {
            return nullptr;
        }
        return TransactionSettingValue;
    }

    TSharedPtr<Model::FScriptSetting> FUpdateNamespaceRequest::GetMissionCompleteScript() const
    {
        if (!MissionCompleteScriptValue.IsValid())
        {
            return nullptr;
        }
        return MissionCompleteScriptValue;
    }

    TSharedPtr<Model::FScriptSetting> FUpdateNamespaceRequest::GetCounterIncrementScript() const
    {
        if (!CounterIncrementScriptValue.IsValid())
        {
            return nullptr;
        }
        return CounterIncrementScriptValue;
    }

    TSharedPtr<Model::FScriptSetting> FUpdateNamespaceRequest::GetReceiveRewardsScript() const
    {
        if (!ReceiveRewardsScriptValue.IsValid())
        {
            return nullptr;
        }
        return ReceiveRewardsScriptValue;
    }

    TSharedPtr<Model::FNotificationSetting> FUpdateNamespaceRequest::GetCompleteNotification() const
    {
        if (!CompleteNotificationValue.IsValid())
        {
            return nullptr;
        }
        return CompleteNotificationValue;
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
          ->WithTransactionSetting(Data->HasField(ANSI_TO_TCHAR("transactionSetting")) ? [Data]() -> Model::FTransactionSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("transactionSetting")))
                  {
                      return nullptr;
                  }
                  return Model::FTransactionSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("transactionSetting")));
              }() : nullptr)
          ->WithMissionCompleteScript(Data->HasField(ANSI_TO_TCHAR("missionCompleteScript")) ? [Data]() -> Model::FScriptSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("missionCompleteScript")))
                  {
                      return nullptr;
                  }
                  return Model::FScriptSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("missionCompleteScript")));
              }() : nullptr)
          ->WithCounterIncrementScript(Data->HasField(ANSI_TO_TCHAR("counterIncrementScript")) ? [Data]() -> Model::FScriptSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("counterIncrementScript")))
                  {
                      return nullptr;
                  }
                  return Model::FScriptSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("counterIncrementScript")));
              }() : nullptr)
          ->WithReceiveRewardsScript(Data->HasField(ANSI_TO_TCHAR("receiveRewardsScript")) ? [Data]() -> Model::FScriptSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("receiveRewardsScript")))
                  {
                      return nullptr;
                  }
                  return Model::FScriptSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("receiveRewardsScript")));
              }() : nullptr)
          ->WithCompleteNotification(Data->HasField(ANSI_TO_TCHAR("completeNotification")) ? [Data]() -> Model::FNotificationSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("completeNotification")))
                  {
                      return nullptr;
                  }
                  return Model::FNotificationSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("completeNotification")));
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
        if (TransactionSettingValue != nullptr && TransactionSettingValue.IsValid())
        {
            JsonRootObject->SetObjectField("transactionSetting", TransactionSettingValue->ToJson());
        }
        if (MissionCompleteScriptValue != nullptr && MissionCompleteScriptValue.IsValid())
        {
            JsonRootObject->SetObjectField("missionCompleteScript", MissionCompleteScriptValue->ToJson());
        }
        if (CounterIncrementScriptValue != nullptr && CounterIncrementScriptValue.IsValid())
        {
            JsonRootObject->SetObjectField("counterIncrementScript", CounterIncrementScriptValue->ToJson());
        }
        if (ReceiveRewardsScriptValue != nullptr && ReceiveRewardsScriptValue.IsValid())
        {
            JsonRootObject->SetObjectField("receiveRewardsScript", ReceiveRewardsScriptValue->ToJson());
        }
        if (CompleteNotificationValue != nullptr && CompleteNotificationValue.IsValid())
        {
            JsonRootObject->SetObjectField("completeNotification", CompleteNotificationValue->ToJson());
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