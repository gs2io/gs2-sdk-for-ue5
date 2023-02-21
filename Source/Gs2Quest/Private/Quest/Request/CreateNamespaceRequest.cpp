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

#include "Quest/Request/CreateNamespaceRequest.h"

namespace Gs2::Quest::Request
{
    FCreateNamespaceRequest::FCreateNamespaceRequest():
        NameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        TransactionSettingValue(nullptr),
        StartQuestScriptValue(nullptr),
        CompleteQuestScriptValue(nullptr),
        FailedQuestScriptValue(nullptr),
        LogSettingValue(nullptr)
    {
    }

    FCreateNamespaceRequest::FCreateNamespaceRequest(
        const FCreateNamespaceRequest& From
    ):
        NameValue(From.NameValue),
        DescriptionValue(From.DescriptionValue),
        TransactionSettingValue(From.TransactionSettingValue),
        StartQuestScriptValue(From.StartQuestScriptValue),
        CompleteQuestScriptValue(From.CompleteQuestScriptValue),
        FailedQuestScriptValue(From.FailedQuestScriptValue),
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

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithTransactionSetting(
        const TSharedPtr<Model::FTransactionSetting> TransactionSetting
    )
    {
        this->TransactionSettingValue = TransactionSetting;
        return SharedThis(this);
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithStartQuestScript(
        const TSharedPtr<Model::FScriptSetting> StartQuestScript
    )
    {
        this->StartQuestScriptValue = StartQuestScript;
        return SharedThis(this);
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithCompleteQuestScript(
        const TSharedPtr<Model::FScriptSetting> CompleteQuestScript
    )
    {
        this->CompleteQuestScriptValue = CompleteQuestScript;
        return SharedThis(this);
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithFailedQuestScript(
        const TSharedPtr<Model::FScriptSetting> FailedQuestScript
    )
    {
        this->FailedQuestScriptValue = FailedQuestScript;
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

    TSharedPtr<Model::FTransactionSetting> FCreateNamespaceRequest::GetTransactionSetting() const
    {
        if (!TransactionSettingValue.IsValid())
        {
            return nullptr;
        }
        return TransactionSettingValue;
    }

    TSharedPtr<Model::FScriptSetting> FCreateNamespaceRequest::GetStartQuestScript() const
    {
        if (!StartQuestScriptValue.IsValid())
        {
            return nullptr;
        }
        return StartQuestScriptValue;
    }

    TSharedPtr<Model::FScriptSetting> FCreateNamespaceRequest::GetCompleteQuestScript() const
    {
        if (!CompleteQuestScriptValue.IsValid())
        {
            return nullptr;
        }
        return CompleteQuestScriptValue;
    }

    TSharedPtr<Model::FScriptSetting> FCreateNamespaceRequest::GetFailedQuestScript() const
    {
        if (!FailedQuestScriptValue.IsValid())
        {
            return nullptr;
        }
        return FailedQuestScriptValue;
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
          ->WithTransactionSetting(Data->HasField("transactionSetting") ? [Data]() -> Model::FTransactionSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>("transactionSetting"))
                  {
                      return nullptr;
                  }
                  return Model::FTransactionSetting::FromJson(Data->GetObjectField("transactionSetting"));
             }() : nullptr)
          ->WithStartQuestScript(Data->HasField("startQuestScript") ? [Data]() -> Model::FScriptSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>("startQuestScript"))
                  {
                      return nullptr;
                  }
                  return Model::FScriptSetting::FromJson(Data->GetObjectField("startQuestScript"));
             }() : nullptr)
          ->WithCompleteQuestScript(Data->HasField("completeQuestScript") ? [Data]() -> Model::FScriptSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>("completeQuestScript"))
                  {
                      return nullptr;
                  }
                  return Model::FScriptSetting::FromJson(Data->GetObjectField("completeQuestScript"));
             }() : nullptr)
          ->WithFailedQuestScript(Data->HasField("failedQuestScript") ? [Data]() -> Model::FScriptSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>("failedQuestScript"))
                  {
                      return nullptr;
                  }
                  return Model::FScriptSetting::FromJson(Data->GetObjectField("failedQuestScript"));
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
        if (TransactionSettingValue != nullptr && TransactionSettingValue.IsValid())
        {
            JsonRootObject->SetObjectField("transactionSetting", TransactionSettingValue->ToJson());
        }
        if (StartQuestScriptValue != nullptr && StartQuestScriptValue.IsValid())
        {
            JsonRootObject->SetObjectField("startQuestScript", StartQuestScriptValue->ToJson());
        }
        if (CompleteQuestScriptValue != nullptr && CompleteQuestScriptValue.IsValid())
        {
            JsonRootObject->SetObjectField("completeQuestScript", CompleteQuestScriptValue->ToJson());
        }
        if (FailedQuestScriptValue != nullptr && FailedQuestScriptValue.IsValid())
        {
            JsonRootObject->SetObjectField("failedQuestScript", FailedQuestScriptValue->ToJson());
        }
        if (LogSettingValue != nullptr && LogSettingValue.IsValid())
        {
            JsonRootObject->SetObjectField("logSetting", LogSettingValue->ToJson());
        }
        return JsonRootObject;
    }
}