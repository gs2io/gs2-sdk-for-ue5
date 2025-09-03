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

#include "Money/Request/UpdateNamespaceRequest.h"

namespace Gs2::Money::Request
{
    FUpdateNamespaceRequest::FUpdateNamespaceRequest():
        NamespaceNameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        TransactionSettingValue(nullptr),
        PriorityValue(TOptional<FString>()),
        AppleKeyValue(TOptional<FString>()),
        GoogleKeyValue(TOptional<FString>()),
        EnableFakeReceiptValue(TOptional<bool>()),
        CreateWalletScriptValue(nullptr),
        DepositScriptValue(nullptr),
        WithdrawScriptValue(nullptr),
        LogSettingValue(nullptr)
    {
    }

    FUpdateNamespaceRequest::FUpdateNamespaceRequest(
        const FUpdateNamespaceRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        DescriptionValue(From.DescriptionValue),
        TransactionSettingValue(From.TransactionSettingValue),
        PriorityValue(From.PriorityValue),
        AppleKeyValue(From.AppleKeyValue),
        GoogleKeyValue(From.GoogleKeyValue),
        EnableFakeReceiptValue(From.EnableFakeReceiptValue),
        CreateWalletScriptValue(From.CreateWalletScriptValue),
        DepositScriptValue(From.DepositScriptValue),
        WithdrawScriptValue(From.WithdrawScriptValue),
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

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::WithPriority(
        const TOptional<FString> Priority
    )
    {
        this->PriorityValue = Priority;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::WithAppleKey(
        const TOptional<FString> AppleKey
    )
    {
        this->AppleKeyValue = AppleKey;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::WithGoogleKey(
        const TOptional<FString> GoogleKey
    )
    {
        this->GoogleKeyValue = GoogleKey;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::WithEnableFakeReceipt(
        const TOptional<bool> EnableFakeReceipt
    )
    {
        this->EnableFakeReceiptValue = EnableFakeReceipt;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::WithCreateWalletScript(
        const TSharedPtr<Model::FScriptSetting> CreateWalletScript
    )
    {
        this->CreateWalletScriptValue = CreateWalletScript;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::WithDepositScript(
        const TSharedPtr<Model::FScriptSetting> DepositScript
    )
    {
        this->DepositScriptValue = DepositScript;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::WithWithdrawScript(
        const TSharedPtr<Model::FScriptSetting> WithdrawScript
    )
    {
        this->WithdrawScriptValue = WithdrawScript;
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

    TOptional<FString> FUpdateNamespaceRequest::GetPriority() const
    {
        return PriorityValue;
    }

    TOptional<FString> FUpdateNamespaceRequest::GetAppleKey() const
    {
        return AppleKeyValue;
    }

    TOptional<FString> FUpdateNamespaceRequest::GetGoogleKey() const
    {
        return GoogleKeyValue;
    }

    TOptional<bool> FUpdateNamespaceRequest::GetEnableFakeReceipt() const
    {
        return EnableFakeReceiptValue;
    }

    FString FUpdateNamespaceRequest::GetEnableFakeReceiptString() const
    {
        if (!EnableFakeReceiptValue.IsSet())
        {
            return FString("null");
        }
        return FString(EnableFakeReceiptValue.GetValue() ? "true" : "false");
    }

    TSharedPtr<Model::FScriptSetting> FUpdateNamespaceRequest::GetCreateWalletScript() const
    {
        if (!CreateWalletScriptValue.IsValid())
        {
            return nullptr;
        }
        return CreateWalletScriptValue;
    }

    TSharedPtr<Model::FScriptSetting> FUpdateNamespaceRequest::GetDepositScript() const
    {
        if (!DepositScriptValue.IsValid())
        {
            return nullptr;
        }
        return DepositScriptValue;
    }

    TSharedPtr<Model::FScriptSetting> FUpdateNamespaceRequest::GetWithdrawScript() const
    {
        if (!WithdrawScriptValue.IsValid())
        {
            return nullptr;
        }
        return WithdrawScriptValue;
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
            ->WithPriority(Data->HasField(ANSI_TO_TCHAR("priority")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("priority"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithAppleKey(Data->HasField(ANSI_TO_TCHAR("appleKey")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("appleKey"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithGoogleKey(Data->HasField(ANSI_TO_TCHAR("googleKey")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("googleKey"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithEnableFakeReceipt(Data->HasField(ANSI_TO_TCHAR("enableFakeReceipt")) ? [Data]() -> TOptional<bool>
              {
                  bool v;
                    if (Data->TryGetBoolField(ANSI_TO_TCHAR("enableFakeReceipt"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<bool>();
              }() : TOptional<bool>())
          ->WithCreateWalletScript(Data->HasField(ANSI_TO_TCHAR("createWalletScript")) ? [Data]() -> Model::FScriptSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("createWalletScript")))
                  {
                      return nullptr;
                  }
                  return Model::FScriptSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("createWalletScript")));
              }() : nullptr)
          ->WithDepositScript(Data->HasField(ANSI_TO_TCHAR("depositScript")) ? [Data]() -> Model::FScriptSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("depositScript")))
                  {
                      return nullptr;
                  }
                  return Model::FScriptSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("depositScript")));
              }() : nullptr)
          ->WithWithdrawScript(Data->HasField(ANSI_TO_TCHAR("withdrawScript")) ? [Data]() -> Model::FScriptSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("withdrawScript")))
                  {
                      return nullptr;
                  }
                  return Model::FScriptSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("withdrawScript")));
              }() : nullptr)
          ->WithLogSetting(Data->HasField(ANSI_TO_TCHAR("logSetting")) ? [Data]() -> Model::FLogSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("logSetting")))
                  {
                      return nullptr;
                  }
                  return Model::FLogSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("logSetting")));
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
        if (PriorityValue.IsSet())
        {
            JsonRootObject->SetStringField("priority", PriorityValue.GetValue());
        }
        if (AppleKeyValue.IsSet())
        {
            JsonRootObject->SetStringField("appleKey", AppleKeyValue.GetValue());
        }
        if (GoogleKeyValue.IsSet())
        {
            JsonRootObject->SetStringField("googleKey", GoogleKeyValue.GetValue());
        }
        if (EnableFakeReceiptValue.IsSet())
        {
            JsonRootObject->SetBoolField("enableFakeReceipt", EnableFakeReceiptValue.GetValue());
        }
        if (CreateWalletScriptValue != nullptr && CreateWalletScriptValue.IsValid())
        {
            JsonRootObject->SetObjectField("createWalletScript", CreateWalletScriptValue->ToJson());
        }
        if (DepositScriptValue != nullptr && DepositScriptValue.IsValid())
        {
            JsonRootObject->SetObjectField("depositScript", DepositScriptValue->ToJson());
        }
        if (WithdrawScriptValue != nullptr && WithdrawScriptValue.IsValid())
        {
            JsonRootObject->SetObjectField("withdrawScript", WithdrawScriptValue->ToJson());
        }
        if (LogSettingValue != nullptr && LogSettingValue.IsValid())
        {
            JsonRootObject->SetObjectField("logSetting", LogSettingValue->ToJson());
        }
        return JsonRootObject;
    }
}