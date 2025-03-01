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

#include "Exchange/Request/UpdateNamespaceRequest.h"

namespace Gs2::Exchange::Request
{
    FUpdateNamespaceRequest::FUpdateNamespaceRequest():
        NamespaceNameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        EnableAwaitExchangeValue(TOptional<bool>()),
        EnableDirectExchangeValue(TOptional<bool>()),
        TransactionSettingValue(nullptr),
        ExchangeScriptValue(nullptr),
        IncrementalExchangeScriptValue(nullptr),
        AcquireAwaitScriptValue(nullptr),
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
        EnableAwaitExchangeValue(From.EnableAwaitExchangeValue),
        EnableDirectExchangeValue(From.EnableDirectExchangeValue),
        TransactionSettingValue(From.TransactionSettingValue),
        ExchangeScriptValue(From.ExchangeScriptValue),
        IncrementalExchangeScriptValue(From.IncrementalExchangeScriptValue),
        AcquireAwaitScriptValue(From.AcquireAwaitScriptValue),
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

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::WithEnableAwaitExchange(
        const TOptional<bool> EnableAwaitExchange
    )
    {
        this->EnableAwaitExchangeValue = EnableAwaitExchange;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::WithEnableDirectExchange(
        const TOptional<bool> EnableDirectExchange
    )
    {
        this->EnableDirectExchangeValue = EnableDirectExchange;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::WithTransactionSetting(
        const TSharedPtr<Model::FTransactionSetting> TransactionSetting
    )
    {
        this->TransactionSettingValue = TransactionSetting;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::WithExchangeScript(
        const TSharedPtr<Model::FScriptSetting> ExchangeScript
    )
    {
        this->ExchangeScriptValue = ExchangeScript;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::WithIncrementalExchangeScript(
        const TSharedPtr<Model::FScriptSetting> IncrementalExchangeScript
    )
    {
        this->IncrementalExchangeScriptValue = IncrementalExchangeScript;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::WithAcquireAwaitScript(
        const TSharedPtr<Model::FScriptSetting> AcquireAwaitScript
    )
    {
        this->AcquireAwaitScriptValue = AcquireAwaitScript;
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

    TOptional<bool> FUpdateNamespaceRequest::GetEnableAwaitExchange() const
    {
        return EnableAwaitExchangeValue;
    }

    FString FUpdateNamespaceRequest::GetEnableAwaitExchangeString() const
    {
        if (!EnableAwaitExchangeValue.IsSet())
        {
            return FString("null");
        }
        return FString(EnableAwaitExchangeValue.GetValue() ? "true" : "false");
    }

    TOptional<bool> FUpdateNamespaceRequest::GetEnableDirectExchange() const
    {
        return EnableDirectExchangeValue;
    }

    FString FUpdateNamespaceRequest::GetEnableDirectExchangeString() const
    {
        if (!EnableDirectExchangeValue.IsSet())
        {
            return FString("null");
        }
        return FString(EnableDirectExchangeValue.GetValue() ? "true" : "false");
    }

    TSharedPtr<Model::FTransactionSetting> FUpdateNamespaceRequest::GetTransactionSetting() const
    {
        if (!TransactionSettingValue.IsValid())
        {
            return nullptr;
        }
        return TransactionSettingValue;
    }

    TSharedPtr<Model::FScriptSetting> FUpdateNamespaceRequest::GetExchangeScript() const
    {
        if (!ExchangeScriptValue.IsValid())
        {
            return nullptr;
        }
        return ExchangeScriptValue;
    }

    TSharedPtr<Model::FScriptSetting> FUpdateNamespaceRequest::GetIncrementalExchangeScript() const
    {
        if (!IncrementalExchangeScriptValue.IsValid())
        {
            return nullptr;
        }
        return IncrementalExchangeScriptValue;
    }

    TSharedPtr<Model::FScriptSetting> FUpdateNamespaceRequest::GetAcquireAwaitScript() const
    {
        if (!AcquireAwaitScriptValue.IsValid())
        {
            return nullptr;
        }
        return AcquireAwaitScriptValue;
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
            ->WithEnableAwaitExchange(Data->HasField(ANSI_TO_TCHAR("enableAwaitExchange")) ? [Data]() -> TOptional<bool>
              {
                  bool v;
                    if (Data->TryGetBoolField(ANSI_TO_TCHAR("enableAwaitExchange"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<bool>();
              }() : TOptional<bool>())
            ->WithEnableDirectExchange(Data->HasField(ANSI_TO_TCHAR("enableDirectExchange")) ? [Data]() -> TOptional<bool>
              {
                  bool v;
                    if (Data->TryGetBoolField(ANSI_TO_TCHAR("enableDirectExchange"), v))
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
          ->WithExchangeScript(Data->HasField(ANSI_TO_TCHAR("exchangeScript")) ? [Data]() -> Model::FScriptSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("exchangeScript")))
                  {
                      return nullptr;
                  }
                  return Model::FScriptSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("exchangeScript")));
              }() : nullptr)
          ->WithIncrementalExchangeScript(Data->HasField(ANSI_TO_TCHAR("incrementalExchangeScript")) ? [Data]() -> Model::FScriptSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("incrementalExchangeScript")))
                  {
                      return nullptr;
                  }
                  return Model::FScriptSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("incrementalExchangeScript")));
              }() : nullptr)
          ->WithAcquireAwaitScript(Data->HasField(ANSI_TO_TCHAR("acquireAwaitScript")) ? [Data]() -> Model::FScriptSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("acquireAwaitScript")))
                  {
                      return nullptr;
                  }
                  return Model::FScriptSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("acquireAwaitScript")));
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
        if (EnableAwaitExchangeValue.IsSet())
        {
            JsonRootObject->SetBoolField("enableAwaitExchange", EnableAwaitExchangeValue.GetValue());
        }
        if (EnableDirectExchangeValue.IsSet())
        {
            JsonRootObject->SetBoolField("enableDirectExchange", EnableDirectExchangeValue.GetValue());
        }
        if (TransactionSettingValue != nullptr && TransactionSettingValue.IsValid())
        {
            JsonRootObject->SetObjectField("transactionSetting", TransactionSettingValue->ToJson());
        }
        if (ExchangeScriptValue != nullptr && ExchangeScriptValue.IsValid())
        {
            JsonRootObject->SetObjectField("exchangeScript", ExchangeScriptValue->ToJson());
        }
        if (IncrementalExchangeScriptValue != nullptr && IncrementalExchangeScriptValue.IsValid())
        {
            JsonRootObject->SetObjectField("incrementalExchangeScript", IncrementalExchangeScriptValue->ToJson());
        }
        if (AcquireAwaitScriptValue != nullptr && AcquireAwaitScriptValue.IsValid())
        {
            JsonRootObject->SetObjectField("acquireAwaitScript", AcquireAwaitScriptValue->ToJson());
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