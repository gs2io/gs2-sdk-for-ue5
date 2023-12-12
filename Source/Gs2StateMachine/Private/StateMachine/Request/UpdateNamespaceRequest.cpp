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

#include "StateMachine/Request/UpdateNamespaceRequest.h"

namespace Gs2::StateMachine::Request
{
    FUpdateNamespaceRequest::FUpdateNamespaceRequest():
        NamespaceNameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        SupportSpeculativeExecutionValue(TOptional<FString>()),
        TransactionSettingValue(nullptr),
        StartScriptValue(nullptr),
        PassScriptValue(nullptr),
        ErrorScriptValue(nullptr),
        LowestStateMachineVersionValue(TOptional<int64>()),
        LogSettingValue(nullptr)
    {
    }

    FUpdateNamespaceRequest::FUpdateNamespaceRequest(
        const FUpdateNamespaceRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        DescriptionValue(From.DescriptionValue),
        SupportSpeculativeExecutionValue(From.SupportSpeculativeExecutionValue),
        TransactionSettingValue(From.TransactionSettingValue),
        StartScriptValue(From.StartScriptValue),
        PassScriptValue(From.PassScriptValue),
        ErrorScriptValue(From.ErrorScriptValue),
        LowestStateMachineVersionValue(From.LowestStateMachineVersionValue),
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

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::WithSupportSpeculativeExecution(
        const TOptional<FString> SupportSpeculativeExecution
    )
    {
        this->SupportSpeculativeExecutionValue = SupportSpeculativeExecution;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::WithTransactionSetting(
        const TSharedPtr<Model::FTransactionSetting> TransactionSetting
    )
    {
        this->TransactionSettingValue = TransactionSetting;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::WithStartScript(
        const TSharedPtr<Model::FScriptSetting> StartScript
    )
    {
        this->StartScriptValue = StartScript;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::WithPassScript(
        const TSharedPtr<Model::FScriptSetting> PassScript
    )
    {
        this->PassScriptValue = PassScript;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::WithErrorScript(
        const TSharedPtr<Model::FScriptSetting> ErrorScript
    )
    {
        this->ErrorScriptValue = ErrorScript;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::WithLowestStateMachineVersion(
        const TOptional<int64> LowestStateMachineVersion
    )
    {
        this->LowestStateMachineVersionValue = LowestStateMachineVersion;
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

    TOptional<FString> FUpdateNamespaceRequest::GetSupportSpeculativeExecution() const
    {
        return SupportSpeculativeExecutionValue;
    }

    TSharedPtr<Model::FTransactionSetting> FUpdateNamespaceRequest::GetTransactionSetting() const
    {
        if (!TransactionSettingValue.IsValid())
        {
            return nullptr;
        }
        return TransactionSettingValue;
    }

    TSharedPtr<Model::FScriptSetting> FUpdateNamespaceRequest::GetStartScript() const
    {
        if (!StartScriptValue.IsValid())
        {
            return nullptr;
        }
        return StartScriptValue;
    }

    TSharedPtr<Model::FScriptSetting> FUpdateNamespaceRequest::GetPassScript() const
    {
        if (!PassScriptValue.IsValid())
        {
            return nullptr;
        }
        return PassScriptValue;
    }

    TSharedPtr<Model::FScriptSetting> FUpdateNamespaceRequest::GetErrorScript() const
    {
        if (!ErrorScriptValue.IsValid())
        {
            return nullptr;
        }
        return ErrorScriptValue;
    }

    TOptional<int64> FUpdateNamespaceRequest::GetLowestStateMachineVersion() const
    {
        return LowestStateMachineVersionValue;
    }

    FString FUpdateNamespaceRequest::GetLowestStateMachineVersionString() const
    {
        if (!LowestStateMachineVersionValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), LowestStateMachineVersionValue.GetValue());
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
                  FString v("");
                    if (Data->TryGetStringField("namespaceName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithDescription(Data->HasField("description") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("description", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithSupportSpeculativeExecution(Data->HasField("supportSpeculativeExecution") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("supportSpeculativeExecution", v))
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
          ->WithStartScript(Data->HasField("startScript") ? [Data]() -> Model::FScriptSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>("startScript"))
                  {
                      return nullptr;
                  }
                  return Model::FScriptSetting::FromJson(Data->GetObjectField("startScript"));
             }() : nullptr)
          ->WithPassScript(Data->HasField("passScript") ? [Data]() -> Model::FScriptSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>("passScript"))
                  {
                      return nullptr;
                  }
                  return Model::FScriptSetting::FromJson(Data->GetObjectField("passScript"));
             }() : nullptr)
          ->WithErrorScript(Data->HasField("errorScript") ? [Data]() -> Model::FScriptSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>("errorScript"))
                  {
                      return nullptr;
                  }
                  return Model::FScriptSetting::FromJson(Data->GetObjectField("errorScript"));
             }() : nullptr)
            ->WithLowestStateMachineVersion(Data->HasField("lowestStateMachineVersion") ? [Data]() -> TOptional<int64>
              {
                  int64 v;
                    if (Data->TryGetNumberField("lowestStateMachineVersion", v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int64>();
              }() : TOptional<int64>())
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
        if (SupportSpeculativeExecutionValue.IsSet())
        {
            JsonRootObject->SetStringField("supportSpeculativeExecution", SupportSpeculativeExecutionValue.GetValue());
        }
        if (TransactionSettingValue != nullptr && TransactionSettingValue.IsValid())
        {
            JsonRootObject->SetObjectField("transactionSetting", TransactionSettingValue->ToJson());
        }
        if (StartScriptValue != nullptr && StartScriptValue.IsValid())
        {
            JsonRootObject->SetObjectField("startScript", StartScriptValue->ToJson());
        }
        if (PassScriptValue != nullptr && PassScriptValue.IsValid())
        {
            JsonRootObject->SetObjectField("passScript", PassScriptValue->ToJson());
        }
        if (ErrorScriptValue != nullptr && ErrorScriptValue.IsValid())
        {
            JsonRootObject->SetObjectField("errorScript", ErrorScriptValue->ToJson());
        }
        if (LowestStateMachineVersionValue.IsSet())
        {
            JsonRootObject->SetStringField("lowestStateMachineVersion", FString::Printf(TEXT("%lld"), LowestStateMachineVersionValue.GetValue()));
        }
        if (LogSettingValue != nullptr && LogSettingValue.IsValid())
        {
            JsonRootObject->SetObjectField("logSetting", LogSettingValue->ToJson());
        }
        return JsonRootObject;
    }
}