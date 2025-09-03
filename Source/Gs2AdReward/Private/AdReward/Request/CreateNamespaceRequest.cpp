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

#include "AdReward/Request/CreateNamespaceRequest.h"

namespace Gs2::AdReward::Request
{
    FCreateNamespaceRequest::FCreateNamespaceRequest():
        NameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        TransactionSettingValue(nullptr),
        AdmobValue(nullptr),
        UnityAdValue(nullptr),
        AppLovinMaxesValue(nullptr),
        AcquirePointScriptValue(nullptr),
        ConsumePointScriptValue(nullptr),
        ChangePointNotificationValue(nullptr),
        LogSettingValue(nullptr)
    {
    }

    FCreateNamespaceRequest::FCreateNamespaceRequest(
        const FCreateNamespaceRequest& From
    ):
        NameValue(From.NameValue),
        DescriptionValue(From.DescriptionValue),
        TransactionSettingValue(From.TransactionSettingValue),
        AdmobValue(From.AdmobValue),
        UnityAdValue(From.UnityAdValue),
        AppLovinMaxesValue(From.AppLovinMaxesValue),
        AcquirePointScriptValue(From.AcquirePointScriptValue),
        ConsumePointScriptValue(From.ConsumePointScriptValue),
        ChangePointNotificationValue(From.ChangePointNotificationValue),
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

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithAdmob(
        const TSharedPtr<Model::FAdMob> Admob
    )
    {
        this->AdmobValue = Admob;
        return SharedThis(this);
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithUnityAd(
        const TSharedPtr<Model::FUnityAd> UnityAd
    )
    {
        this->UnityAdValue = UnityAd;
        return SharedThis(this);
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithAppLovinMaxes(
        const TSharedPtr<TArray<TSharedPtr<Model::FAppLovinMax>>> AppLovinMaxes
    )
    {
        this->AppLovinMaxesValue = AppLovinMaxes;
        return SharedThis(this);
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithAcquirePointScript(
        const TSharedPtr<Model::FScriptSetting> AcquirePointScript
    )
    {
        this->AcquirePointScriptValue = AcquirePointScript;
        return SharedThis(this);
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithConsumePointScript(
        const TSharedPtr<Model::FScriptSetting> ConsumePointScript
    )
    {
        this->ConsumePointScriptValue = ConsumePointScript;
        return SharedThis(this);
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithChangePointNotification(
        const TSharedPtr<Model::FNotificationSetting> ChangePointNotification
    )
    {
        this->ChangePointNotificationValue = ChangePointNotification;
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

    TSharedPtr<Model::FAdMob> FCreateNamespaceRequest::GetAdmob() const
    {
        if (!AdmobValue.IsValid())
        {
            return nullptr;
        }
        return AdmobValue;
    }

    TSharedPtr<Model::FUnityAd> FCreateNamespaceRequest::GetUnityAd() const
    {
        if (!UnityAdValue.IsValid())
        {
            return nullptr;
        }
        return UnityAdValue;
    }

    TSharedPtr<TArray<TSharedPtr<Model::FAppLovinMax>>> FCreateNamespaceRequest::GetAppLovinMaxes() const
    {
        if (!AppLovinMaxesValue.IsValid())
        {
            return nullptr;
        }
        return AppLovinMaxesValue;
    }

    TSharedPtr<Model::FScriptSetting> FCreateNamespaceRequest::GetAcquirePointScript() const
    {
        if (!AcquirePointScriptValue.IsValid())
        {
            return nullptr;
        }
        return AcquirePointScriptValue;
    }

    TSharedPtr<Model::FScriptSetting> FCreateNamespaceRequest::GetConsumePointScript() const
    {
        if (!ConsumePointScriptValue.IsValid())
        {
            return nullptr;
        }
        return ConsumePointScriptValue;
    }

    TSharedPtr<Model::FNotificationSetting> FCreateNamespaceRequest::GetChangePointNotification() const
    {
        if (!ChangePointNotificationValue.IsValid())
        {
            return nullptr;
        }
        return ChangePointNotificationValue;
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
          ->WithAdmob(Data->HasField(ANSI_TO_TCHAR("admob")) ? [Data]() -> Model::FAdMobPtr
              {
                  if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("admob")))
                  {
                      return nullptr;
                  }
                  return Model::FAdMob::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("admob")));
              }() : nullptr)
          ->WithUnityAd(Data->HasField(ANSI_TO_TCHAR("unityAd")) ? [Data]() -> Model::FUnityAdPtr
              {
                  if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("unityAd")))
                  {
                      return nullptr;
                  }
                  return Model::FUnityAd::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("unityAd")));
              }() : nullptr)
          ->WithAppLovinMaxes(Data->HasField(ANSI_TO_TCHAR("appLovinMaxes")) ? [Data]() -> TSharedPtr<TArray<Model::FAppLovinMaxPtr>>
              {
                  auto v = MakeShared<TArray<Model::FAppLovinMaxPtr>>();
                  if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("appLovinMaxes")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("appLovinMaxes")))
                  {
                      for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("appLovinMaxes")))
                      {
                          v->Add(Model::FAppLovinMax::FromJson(JsonObjectValue->AsObject()));
                      }
                  }
                  return v;
              }() : MakeShared<TArray<Model::FAppLovinMaxPtr>>())
          ->WithAcquirePointScript(Data->HasField(ANSI_TO_TCHAR("acquirePointScript")) ? [Data]() -> Model::FScriptSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("acquirePointScript")))
                  {
                      return nullptr;
                  }
                  return Model::FScriptSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("acquirePointScript")));
              }() : nullptr)
          ->WithConsumePointScript(Data->HasField(ANSI_TO_TCHAR("consumePointScript")) ? [Data]() -> Model::FScriptSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("consumePointScript")))
                  {
                      return nullptr;
                  }
                  return Model::FScriptSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("consumePointScript")));
              }() : nullptr)
          ->WithChangePointNotification(Data->HasField(ANSI_TO_TCHAR("changePointNotification")) ? [Data]() -> Model::FNotificationSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("changePointNotification")))
                  {
                      return nullptr;
                  }
                  return Model::FNotificationSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("changePointNotification")));
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
        if (AdmobValue != nullptr && AdmobValue.IsValid())
        {
            JsonRootObject->SetObjectField("admob", AdmobValue->ToJson());
        }
        if (UnityAdValue != nullptr && UnityAdValue.IsValid())
        {
            JsonRootObject->SetObjectField("unityAd", UnityAdValue->ToJson());
        }
        if (AppLovinMaxesValue != nullptr && AppLovinMaxesValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *AppLovinMaxesValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("appLovinMaxes", v);
        }
        if (AcquirePointScriptValue != nullptr && AcquirePointScriptValue.IsValid())
        {
            JsonRootObject->SetObjectField("acquirePointScript", AcquirePointScriptValue->ToJson());
        }
        if (ConsumePointScriptValue != nullptr && ConsumePointScriptValue.IsValid())
        {
            JsonRootObject->SetObjectField("consumePointScript", ConsumePointScriptValue->ToJson());
        }
        if (ChangePointNotificationValue != nullptr && ChangePointNotificationValue.IsValid())
        {
            JsonRootObject->SetObjectField("changePointNotification", ChangePointNotificationValue->ToJson());
        }
        if (LogSettingValue != nullptr && LogSettingValue.IsValid())
        {
            JsonRootObject->SetObjectField("logSetting", LogSettingValue->ToJson());
        }
        return JsonRootObject;
    }
}