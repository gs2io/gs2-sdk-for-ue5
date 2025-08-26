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

#include "Money2/Request/CreateNamespaceRequest.h"

namespace Gs2::Money2::Request
{
    FCreateNamespaceRequest::FCreateNamespaceRequest():
        NameValue(TOptional<FString>()),
        CurrencyUsagePriorityValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        SharedFreeCurrencyValue(TOptional<bool>()),
        PlatformSettingValue(nullptr),
        DepositBalanceScriptValue(nullptr),
        WithdrawBalanceScriptValue(nullptr),
        VerifyReceiptScriptValue(nullptr),
        SubscribeScriptValue(TOptional<FString>()),
        RenewScriptValue(TOptional<FString>()),
        UnsubscribeScriptValue(TOptional<FString>()),
        TakeOverScriptValue(nullptr),
        ChangeSubscriptionStatusNotificationValue(nullptr),
        LogSettingValue(nullptr)
    {
    }

    FCreateNamespaceRequest::FCreateNamespaceRequest(
        const FCreateNamespaceRequest& From
    ):
        NameValue(From.NameValue),
        CurrencyUsagePriorityValue(From.CurrencyUsagePriorityValue),
        DescriptionValue(From.DescriptionValue),
        SharedFreeCurrencyValue(From.SharedFreeCurrencyValue),
        PlatformSettingValue(From.PlatformSettingValue),
        DepositBalanceScriptValue(From.DepositBalanceScriptValue),
        WithdrawBalanceScriptValue(From.WithdrawBalanceScriptValue),
        VerifyReceiptScriptValue(From.VerifyReceiptScriptValue),
        SubscribeScriptValue(From.SubscribeScriptValue),
        RenewScriptValue(From.RenewScriptValue),
        UnsubscribeScriptValue(From.UnsubscribeScriptValue),
        TakeOverScriptValue(From.TakeOverScriptValue),
        ChangeSubscriptionStatusNotificationValue(From.ChangeSubscriptionStatusNotificationValue),
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

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithCurrencyUsagePriority(
        const TOptional<FString> CurrencyUsagePriority
    )
    {
        this->CurrencyUsagePriorityValue = CurrencyUsagePriority;
        return SharedThis(this);
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
        return SharedThis(this);
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithSharedFreeCurrency(
        const TOptional<bool> SharedFreeCurrency
    )
    {
        this->SharedFreeCurrencyValue = SharedFreeCurrency;
        return SharedThis(this);
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithPlatformSetting(
        const TSharedPtr<Model::FPlatformSetting> PlatformSetting
    )
    {
        this->PlatformSettingValue = PlatformSetting;
        return SharedThis(this);
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithDepositBalanceScript(
        const TSharedPtr<Model::FScriptSetting> DepositBalanceScript
    )
    {
        this->DepositBalanceScriptValue = DepositBalanceScript;
        return SharedThis(this);
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithWithdrawBalanceScript(
        const TSharedPtr<Model::FScriptSetting> WithdrawBalanceScript
    )
    {
        this->WithdrawBalanceScriptValue = WithdrawBalanceScript;
        return SharedThis(this);
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithVerifyReceiptScript(
        const TSharedPtr<Model::FScriptSetting> VerifyReceiptScript
    )
    {
        this->VerifyReceiptScriptValue = VerifyReceiptScript;
        return SharedThis(this);
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithSubscribeScript(
        const TOptional<FString> SubscribeScript
    )
    {
        this->SubscribeScriptValue = SubscribeScript;
        return SharedThis(this);
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithRenewScript(
        const TOptional<FString> RenewScript
    )
    {
        this->RenewScriptValue = RenewScript;
        return SharedThis(this);
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithUnsubscribeScript(
        const TOptional<FString> UnsubscribeScript
    )
    {
        this->UnsubscribeScriptValue = UnsubscribeScript;
        return SharedThis(this);
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithTakeOverScript(
        const TSharedPtr<Model::FScriptSetting> TakeOverScript
    )
    {
        this->TakeOverScriptValue = TakeOverScript;
        return SharedThis(this);
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithChangeSubscriptionStatusNotification(
        const TSharedPtr<Model::FNotificationSetting> ChangeSubscriptionStatusNotification
    )
    {
        this->ChangeSubscriptionStatusNotificationValue = ChangeSubscriptionStatusNotification;
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

    TOptional<FString> FCreateNamespaceRequest::GetCurrencyUsagePriority() const
    {
        return CurrencyUsagePriorityValue;
    }

    TOptional<FString> FCreateNamespaceRequest::GetDescription() const
    {
        return DescriptionValue;
    }

    TOptional<bool> FCreateNamespaceRequest::GetSharedFreeCurrency() const
    {
        return SharedFreeCurrencyValue;
    }

    FString FCreateNamespaceRequest::GetSharedFreeCurrencyString() const
    {
        if (!SharedFreeCurrencyValue.IsSet())
        {
            return FString("null");
        }
        return FString(SharedFreeCurrencyValue.GetValue() ? "true" : "false");
    }

    TSharedPtr<Model::FPlatformSetting> FCreateNamespaceRequest::GetPlatformSetting() const
    {
        if (!PlatformSettingValue.IsValid())
        {
            return nullptr;
        }
        return PlatformSettingValue;
    }

    TSharedPtr<Model::FScriptSetting> FCreateNamespaceRequest::GetDepositBalanceScript() const
    {
        if (!DepositBalanceScriptValue.IsValid())
        {
            return nullptr;
        }
        return DepositBalanceScriptValue;
    }

    TSharedPtr<Model::FScriptSetting> FCreateNamespaceRequest::GetWithdrawBalanceScript() const
    {
        if (!WithdrawBalanceScriptValue.IsValid())
        {
            return nullptr;
        }
        return WithdrawBalanceScriptValue;
    }

    TSharedPtr<Model::FScriptSetting> FCreateNamespaceRequest::GetVerifyReceiptScript() const
    {
        if (!VerifyReceiptScriptValue.IsValid())
        {
            return nullptr;
        }
        return VerifyReceiptScriptValue;
    }

    TOptional<FString> FCreateNamespaceRequest::GetSubscribeScript() const
    {
        return SubscribeScriptValue;
    }

    TOptional<FString> FCreateNamespaceRequest::GetRenewScript() const
    {
        return RenewScriptValue;
    }

    TOptional<FString> FCreateNamespaceRequest::GetUnsubscribeScript() const
    {
        return UnsubscribeScriptValue;
    }

    TSharedPtr<Model::FScriptSetting> FCreateNamespaceRequest::GetTakeOverScript() const
    {
        if (!TakeOverScriptValue.IsValid())
        {
            return nullptr;
        }
        return TakeOverScriptValue;
    }

    TSharedPtr<Model::FNotificationSetting> FCreateNamespaceRequest::GetChangeSubscriptionStatusNotification() const
    {
        if (!ChangeSubscriptionStatusNotificationValue.IsValid())
        {
            return nullptr;
        }
        return ChangeSubscriptionStatusNotificationValue;
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
            ->WithCurrencyUsagePriority(Data->HasField(ANSI_TO_TCHAR("currencyUsagePriority")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("currencyUsagePriority"), v))
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
            ->WithSharedFreeCurrency(Data->HasField(ANSI_TO_TCHAR("sharedFreeCurrency")) ? [Data]() -> TOptional<bool>
              {
                  bool v;
                    if (Data->TryGetBoolField(ANSI_TO_TCHAR("sharedFreeCurrency"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<bool>();
              }() : TOptional<bool>())
          ->WithPlatformSetting(Data->HasField(ANSI_TO_TCHAR("platformSetting")) ? [Data]() -> Model::FPlatformSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("platformSetting")))
                  {
                      return nullptr;
                  }
                  return Model::FPlatformSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("platformSetting")));
              }() : nullptr)
          ->WithDepositBalanceScript(Data->HasField(ANSI_TO_TCHAR("depositBalanceScript")) ? [Data]() -> Model::FScriptSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("depositBalanceScript")))
                  {
                      return nullptr;
                  }
                  return Model::FScriptSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("depositBalanceScript")));
              }() : nullptr)
          ->WithWithdrawBalanceScript(Data->HasField(ANSI_TO_TCHAR("withdrawBalanceScript")) ? [Data]() -> Model::FScriptSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("withdrawBalanceScript")))
                  {
                      return nullptr;
                  }
                  return Model::FScriptSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("withdrawBalanceScript")));
              }() : nullptr)
          ->WithVerifyReceiptScript(Data->HasField(ANSI_TO_TCHAR("verifyReceiptScript")) ? [Data]() -> Model::FScriptSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("verifyReceiptScript")))
                  {
                      return nullptr;
                  }
                  return Model::FScriptSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("verifyReceiptScript")));
              }() : nullptr)
            ->WithSubscribeScript(Data->HasField(ANSI_TO_TCHAR("subscribeScript")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("subscribeScript"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithRenewScript(Data->HasField(ANSI_TO_TCHAR("renewScript")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("renewScript"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithUnsubscribeScript(Data->HasField(ANSI_TO_TCHAR("unsubscribeScript")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("unsubscribeScript"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
          ->WithTakeOverScript(Data->HasField(ANSI_TO_TCHAR("takeOverScript")) ? [Data]() -> Model::FScriptSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("takeOverScript")))
                  {
                      return nullptr;
                  }
                  return Model::FScriptSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("takeOverScript")));
              }() : nullptr)
          ->WithChangeSubscriptionStatusNotification(Data->HasField(ANSI_TO_TCHAR("changeSubscriptionStatusNotification")) ? [Data]() -> Model::FNotificationSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("changeSubscriptionStatusNotification")))
                  {
                      return nullptr;
                  }
                  return Model::FNotificationSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("changeSubscriptionStatusNotification")));
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
        if (CurrencyUsagePriorityValue.IsSet())
        {
            JsonRootObject->SetStringField("currencyUsagePriority", CurrencyUsagePriorityValue.GetValue());
        }
        if (DescriptionValue.IsSet())
        {
            JsonRootObject->SetStringField("description", DescriptionValue.GetValue());
        }
        if (SharedFreeCurrencyValue.IsSet())
        {
            JsonRootObject->SetBoolField("sharedFreeCurrency", SharedFreeCurrencyValue.GetValue());
        }
        if (PlatformSettingValue != nullptr && PlatformSettingValue.IsValid())
        {
            JsonRootObject->SetObjectField("platformSetting", PlatformSettingValue->ToJson());
        }
        if (DepositBalanceScriptValue != nullptr && DepositBalanceScriptValue.IsValid())
        {
            JsonRootObject->SetObjectField("depositBalanceScript", DepositBalanceScriptValue->ToJson());
        }
        if (WithdrawBalanceScriptValue != nullptr && WithdrawBalanceScriptValue.IsValid())
        {
            JsonRootObject->SetObjectField("withdrawBalanceScript", WithdrawBalanceScriptValue->ToJson());
        }
        if (VerifyReceiptScriptValue != nullptr && VerifyReceiptScriptValue.IsValid())
        {
            JsonRootObject->SetObjectField("verifyReceiptScript", VerifyReceiptScriptValue->ToJson());
        }
        if (SubscribeScriptValue.IsSet())
        {
            JsonRootObject->SetStringField("subscribeScript", SubscribeScriptValue.GetValue());
        }
        if (RenewScriptValue.IsSet())
        {
            JsonRootObject->SetStringField("renewScript", RenewScriptValue.GetValue());
        }
        if (UnsubscribeScriptValue.IsSet())
        {
            JsonRootObject->SetStringField("unsubscribeScript", UnsubscribeScriptValue.GetValue());
        }
        if (TakeOverScriptValue != nullptr && TakeOverScriptValue.IsValid())
        {
            JsonRootObject->SetObjectField("takeOverScript", TakeOverScriptValue->ToJson());
        }
        if (ChangeSubscriptionStatusNotificationValue != nullptr && ChangeSubscriptionStatusNotificationValue.IsValid())
        {
            JsonRootObject->SetObjectField("changeSubscriptionStatusNotification", ChangeSubscriptionStatusNotificationValue->ToJson());
        }
        if (LogSettingValue != nullptr && LogSettingValue.IsValid())
        {
            JsonRootObject->SetObjectField("logSetting", LogSettingValue->ToJson());
        }
        return JsonRootObject;
    }
}