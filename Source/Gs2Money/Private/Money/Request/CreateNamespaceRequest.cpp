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

#include "Money/Request/CreateNamespaceRequest.h"

namespace Gs2::Money::Request
{
    FCreateNamespaceRequest::FCreateNamespaceRequest():
        NameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        TransactionSettingValue(nullptr),
        PriorityValue(TOptional<FString>()),
        ShareFreeValue(TOptional<bool>()),
        CurrencyValue(TOptional<FString>()),
        AppleKeyValue(TOptional<FString>()),
        GoogleKeyValue(TOptional<FString>()),
        EnableFakeReceiptValue(TOptional<bool>()),
        CreateWalletScriptValue(nullptr),
        DepositScriptValue(nullptr),
        WithdrawScriptValue(nullptr),
        LogSettingValue(nullptr)
    {
    }

    FCreateNamespaceRequest::FCreateNamespaceRequest(
        const FCreateNamespaceRequest& From
    ):
        NameValue(From.NameValue),
        DescriptionValue(From.DescriptionValue),
        TransactionSettingValue(From.TransactionSettingValue),
        PriorityValue(From.PriorityValue),
        ShareFreeValue(From.ShareFreeValue),
        CurrencyValue(From.CurrencyValue),
        AppleKeyValue(From.AppleKeyValue),
        GoogleKeyValue(From.GoogleKeyValue),
        EnableFakeReceiptValue(From.EnableFakeReceiptValue),
        CreateWalletScriptValue(From.CreateWalletScriptValue),
        DepositScriptValue(From.DepositScriptValue),
        WithdrawScriptValue(From.WithdrawScriptValue),
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

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithPriority(
        const TOptional<FString> Priority
    )
    {
        this->PriorityValue = Priority;
        return SharedThis(this);
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithShareFree(
        const TOptional<bool> ShareFree
    )
    {
        this->ShareFreeValue = ShareFree;
        return SharedThis(this);
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithCurrency(
        const TOptional<FString> Currency
    )
    {
        this->CurrencyValue = Currency;
        return SharedThis(this);
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithAppleKey(
        const TOptional<FString> AppleKey
    )
    {
        this->AppleKeyValue = AppleKey;
        return SharedThis(this);
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithGoogleKey(
        const TOptional<FString> GoogleKey
    )
    {
        this->GoogleKeyValue = GoogleKey;
        return SharedThis(this);
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithEnableFakeReceipt(
        const TOptional<bool> EnableFakeReceipt
    )
    {
        this->EnableFakeReceiptValue = EnableFakeReceipt;
        return SharedThis(this);
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithCreateWalletScript(
        const TSharedPtr<Model::FScriptSetting> CreateWalletScript
    )
    {
        this->CreateWalletScriptValue = CreateWalletScript;
        return SharedThis(this);
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithDepositScript(
        const TSharedPtr<Model::FScriptSetting> DepositScript
    )
    {
        this->DepositScriptValue = DepositScript;
        return SharedThis(this);
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithWithdrawScript(
        const TSharedPtr<Model::FScriptSetting> WithdrawScript
    )
    {
        this->WithdrawScriptValue = WithdrawScript;
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

    TOptional<FString> FCreateNamespaceRequest::GetPriority() const
    {
        return PriorityValue;
    }

    TOptional<bool> FCreateNamespaceRequest::GetShareFree() const
    {
        return ShareFreeValue;
    }

    FString FCreateNamespaceRequest::GetShareFreeString() const
    {
        if (!ShareFreeValue.IsSet())
        {
            return FString("null");
        }
        return FString(ShareFreeValue.GetValue() ? "true" : "false");
    }

    TOptional<FString> FCreateNamespaceRequest::GetCurrency() const
    {
        return CurrencyValue;
    }

    TOptional<FString> FCreateNamespaceRequest::GetAppleKey() const
    {
        return AppleKeyValue;
    }

    TOptional<FString> FCreateNamespaceRequest::GetGoogleKey() const
    {
        return GoogleKeyValue;
    }

    TOptional<bool> FCreateNamespaceRequest::GetEnableFakeReceipt() const
    {
        return EnableFakeReceiptValue;
    }

    FString FCreateNamespaceRequest::GetEnableFakeReceiptString() const
    {
        if (!EnableFakeReceiptValue.IsSet())
        {
            return FString("null");
        }
        return FString(EnableFakeReceiptValue.GetValue() ? "true" : "false");
    }

    TSharedPtr<Model::FScriptSetting> FCreateNamespaceRequest::GetCreateWalletScript() const
    {
        if (!CreateWalletScriptValue.IsValid())
        {
            return nullptr;
        }
        return CreateWalletScriptValue;
    }

    TSharedPtr<Model::FScriptSetting> FCreateNamespaceRequest::GetDepositScript() const
    {
        if (!DepositScriptValue.IsValid())
        {
            return nullptr;
        }
        return DepositScriptValue;
    }

    TSharedPtr<Model::FScriptSetting> FCreateNamespaceRequest::GetWithdrawScript() const
    {
        if (!WithdrawScriptValue.IsValid())
        {
            return nullptr;
        }
        return WithdrawScriptValue;
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
            ->WithContextStack(Data->HasField(ANSI_TO_TCHAR("contextStack")) ? TOptional<FString>(Data->GetStringField(ANSI_TO_TCHAR("contextStack"))) : TOptional<FString>())
            ->WithName(Data->HasField(ANSI_TO_TCHAR("name")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("name"), v))
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
            ->WithShareFree(Data->HasField(ANSI_TO_TCHAR("shareFree")) ? [Data]() -> TOptional<bool>
              {
                  bool v;
                    if (Data->TryGetBoolField(ANSI_TO_TCHAR("shareFree"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<bool>();
              }() : TOptional<bool>())
            ->WithCurrency(Data->HasField(ANSI_TO_TCHAR("currency")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("currency"), v))
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
        if (PriorityValue.IsSet())
        {
            JsonRootObject->SetStringField("priority", PriorityValue.GetValue());
        }
        if (ShareFreeValue.IsSet())
        {
            JsonRootObject->SetBoolField("shareFree", ShareFreeValue.GetValue());
        }
        if (CurrencyValue.IsSet())
        {
            JsonRootObject->SetStringField("currency", CurrencyValue.GetValue());
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