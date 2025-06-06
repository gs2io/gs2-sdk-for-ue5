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

#include "Money2/Request/UpdateNamespaceRequest.h"

namespace Gs2::Money2::Request
{
    FUpdateNamespaceRequest::FUpdateNamespaceRequest():
        NamespaceNameValue(TOptional<FString>()),
        CurrencyUsagePriorityValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        PlatformSettingValue(nullptr),
        DepositBalanceScriptValue(nullptr),
        WithdrawBalanceScriptValue(nullptr),
        SubscribeScriptValue(TOptional<FString>()),
        RenewScriptValue(TOptional<FString>()),
        UnsubscribeScriptValue(TOptional<FString>()),
        TakeOverScriptValue(nullptr),
        ChangeSubscriptionStatusNotificationValue(nullptr),
        LogSettingValue(nullptr)
    {
    }

    FUpdateNamespaceRequest::FUpdateNamespaceRequest(
        const FUpdateNamespaceRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        CurrencyUsagePriorityValue(From.CurrencyUsagePriorityValue),
        DescriptionValue(From.DescriptionValue),
        PlatformSettingValue(From.PlatformSettingValue),
        DepositBalanceScriptValue(From.DepositBalanceScriptValue),
        WithdrawBalanceScriptValue(From.WithdrawBalanceScriptValue),
        SubscribeScriptValue(From.SubscribeScriptValue),
        RenewScriptValue(From.RenewScriptValue),
        UnsubscribeScriptValue(From.UnsubscribeScriptValue),
        TakeOverScriptValue(From.TakeOverScriptValue),
        ChangeSubscriptionStatusNotificationValue(From.ChangeSubscriptionStatusNotificationValue),
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

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::WithCurrencyUsagePriority(
        const TOptional<FString> CurrencyUsagePriority
    )
    {
        this->CurrencyUsagePriorityValue = CurrencyUsagePriority;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::WithPlatformSetting(
        const TSharedPtr<Model::FPlatformSetting> PlatformSetting
    )
    {
        this->PlatformSettingValue = PlatformSetting;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::WithDepositBalanceScript(
        const TSharedPtr<Model::FScriptSetting> DepositBalanceScript
    )
    {
        this->DepositBalanceScriptValue = DepositBalanceScript;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::WithWithdrawBalanceScript(
        const TSharedPtr<Model::FScriptSetting> WithdrawBalanceScript
    )
    {
        this->WithdrawBalanceScriptValue = WithdrawBalanceScript;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::WithSubscribeScript(
        const TOptional<FString> SubscribeScript
    )
    {
        this->SubscribeScriptValue = SubscribeScript;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::WithRenewScript(
        const TOptional<FString> RenewScript
    )
    {
        this->RenewScriptValue = RenewScript;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::WithUnsubscribeScript(
        const TOptional<FString> UnsubscribeScript
    )
    {
        this->UnsubscribeScriptValue = UnsubscribeScript;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::WithTakeOverScript(
        const TSharedPtr<Model::FScriptSetting> TakeOverScript
    )
    {
        this->TakeOverScriptValue = TakeOverScript;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::WithChangeSubscriptionStatusNotification(
        const TSharedPtr<Model::FNotificationSetting> ChangeSubscriptionStatusNotification
    )
    {
        this->ChangeSubscriptionStatusNotificationValue = ChangeSubscriptionStatusNotification;
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

    TOptional<FString> FUpdateNamespaceRequest::GetCurrencyUsagePriority() const
    {
        return CurrencyUsagePriorityValue;
    }

    TOptional<FString> FUpdateNamespaceRequest::GetDescription() const
    {
        return DescriptionValue;
    }

    TSharedPtr<Model::FPlatformSetting> FUpdateNamespaceRequest::GetPlatformSetting() const
    {
        if (!PlatformSettingValue.IsValid())
        {
            return nullptr;
        }
        return PlatformSettingValue;
    }

    TSharedPtr<Model::FScriptSetting> FUpdateNamespaceRequest::GetDepositBalanceScript() const
    {
        if (!DepositBalanceScriptValue.IsValid())
        {
            return nullptr;
        }
        return DepositBalanceScriptValue;
    }

    TSharedPtr<Model::FScriptSetting> FUpdateNamespaceRequest::GetWithdrawBalanceScript() const
    {
        if (!WithdrawBalanceScriptValue.IsValid())
        {
            return nullptr;
        }
        return WithdrawBalanceScriptValue;
    }

    TOptional<FString> FUpdateNamespaceRequest::GetSubscribeScript() const
    {
        return SubscribeScriptValue;
    }

    TOptional<FString> FUpdateNamespaceRequest::GetRenewScript() const
    {
        return RenewScriptValue;
    }

    TOptional<FString> FUpdateNamespaceRequest::GetUnsubscribeScript() const
    {
        return UnsubscribeScriptValue;
    }

    TSharedPtr<Model::FScriptSetting> FUpdateNamespaceRequest::GetTakeOverScript() const
    {
        if (!TakeOverScriptValue.IsValid())
        {
            return nullptr;
        }
        return TakeOverScriptValue;
    }

    TSharedPtr<Model::FNotificationSetting> FUpdateNamespaceRequest::GetChangeSubscriptionStatusNotification() const
    {
        if (!ChangeSubscriptionStatusNotificationValue.IsValid())
        {
            return nullptr;
        }
        return ChangeSubscriptionStatusNotificationValue;
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
        if (CurrencyUsagePriorityValue.IsSet())
        {
            JsonRootObject->SetStringField("currencyUsagePriority", CurrencyUsagePriorityValue.GetValue());
        }
        if (DescriptionValue.IsSet())
        {
            JsonRootObject->SetStringField("description", DescriptionValue.GetValue());
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