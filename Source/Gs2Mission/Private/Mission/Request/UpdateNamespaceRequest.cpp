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
        LogSettingValue(nullptr)
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
        LogSettingValue(From.LogSettingValue)
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

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FUpdateNamespaceRequest>()
            ->WithContextStack(Data->HasField("contextStack") ? TOptional<FString>(Data->GetStringField("contextStack")) : TOptional<FString>())
            ->WithNamespaceName(Data->HasField("namespaceName") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("namespaceName", v))
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
          ->WithTransactionSetting(Data->HasField("transactionSetting") ? [Data]() -> Model::FTransactionSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>("transactionSetting"))
                  {
                      return nullptr;
                  }
                  return Model::FTransactionSetting::FromJson(Data->GetObjectField("transactionSetting"));
             }() : nullptr)
          ->WithMissionCompleteScript(Data->HasField("missionCompleteScript") ? [Data]() -> Model::FScriptSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>("missionCompleteScript"))
                  {
                      return nullptr;
                  }
                  return Model::FScriptSetting::FromJson(Data->GetObjectField("missionCompleteScript"));
             }() : nullptr)
          ->WithCounterIncrementScript(Data->HasField("counterIncrementScript") ? [Data]() -> Model::FScriptSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>("counterIncrementScript"))
                  {
                      return nullptr;
                  }
                  return Model::FScriptSetting::FromJson(Data->GetObjectField("counterIncrementScript"));
             }() : nullptr)
          ->WithReceiveRewardsScript(Data->HasField("receiveRewardsScript") ? [Data]() -> Model::FScriptSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>("receiveRewardsScript"))
                  {
                      return nullptr;
                  }
                  return Model::FScriptSetting::FromJson(Data->GetObjectField("receiveRewardsScript"));
             }() : nullptr)
          ->WithCompleteNotification(Data->HasField("completeNotification") ? [Data]() -> Model::FNotificationSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>("completeNotification"))
                  {
                      return nullptr;
                  }
                  return Model::FNotificationSetting::FromJson(Data->GetObjectField("completeNotification"));
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
        return JsonRootObject;
    }
}