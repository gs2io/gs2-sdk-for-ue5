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

#include "AdReward/Request/UpdateNamespaceRequest.h"

namespace Gs2::AdReward::Request
{
    FUpdateNamespaceRequest::FUpdateNamespaceRequest():
        NamespaceNameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        AdmobValue(nullptr),
        UnityAdValue(nullptr),
        ChangePointNotificationValue(nullptr),
        LogSettingValue(nullptr)
    {
    }

    FUpdateNamespaceRequest::FUpdateNamespaceRequest(
        const FUpdateNamespaceRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        DescriptionValue(From.DescriptionValue),
        AdmobValue(From.AdmobValue),
        UnityAdValue(From.UnityAdValue),
        ChangePointNotificationValue(From.ChangePointNotificationValue),
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

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::WithAdmob(
        const TSharedPtr<Model::FAdMob> Admob
    )
    {
        this->AdmobValue = Admob;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::WithUnityAd(
        const TSharedPtr<Model::FUnityAd> UnityAd
    )
    {
        this->UnityAdValue = UnityAd;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::WithChangePointNotification(
        const TSharedPtr<Model::FNotificationSetting> ChangePointNotification
    )
    {
        this->ChangePointNotificationValue = ChangePointNotification;
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

    TSharedPtr<Model::FAdMob> FUpdateNamespaceRequest::GetAdmob() const
    {
        if (!AdmobValue.IsValid())
        {
            return nullptr;
        }
        return AdmobValue;
    }

    TSharedPtr<Model::FUnityAd> FUpdateNamespaceRequest::GetUnityAd() const
    {
        if (!UnityAdValue.IsValid())
        {
            return nullptr;
        }
        return UnityAdValue;
    }

    TSharedPtr<Model::FNotificationSetting> FUpdateNamespaceRequest::GetChangePointNotification() const
    {
        if (!ChangePointNotificationValue.IsValid())
        {
            return nullptr;
        }
        return ChangePointNotificationValue;
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
          ->WithAdmob(Data->HasField("admob") ? [Data]() -> Model::FAdMobPtr
              {
                  if (Data->HasTypedField<EJson::Null>("admob"))
                  {
                      return nullptr;
                  }
                  return Model::FAdMob::FromJson(Data->GetObjectField("admob"));
             }() : nullptr)
          ->WithUnityAd(Data->HasField("unityAd") ? [Data]() -> Model::FUnityAdPtr
              {
                  if (Data->HasTypedField<EJson::Null>("unityAd"))
                  {
                      return nullptr;
                  }
                  return Model::FUnityAd::FromJson(Data->GetObjectField("unityAd"));
             }() : nullptr)
          ->WithChangePointNotification(Data->HasField("changePointNotification") ? [Data]() -> Model::FNotificationSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>("changePointNotification"))
                  {
                      return nullptr;
                  }
                  return Model::FNotificationSetting::FromJson(Data->GetObjectField("changePointNotification"));
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
        if (AdmobValue != nullptr && AdmobValue.IsValid())
        {
            JsonRootObject->SetObjectField("admob", AdmobValue->ToJson());
        }
        if (UnityAdValue != nullptr && UnityAdValue.IsValid())
        {
            JsonRootObject->SetObjectField("unityAd", UnityAdValue->ToJson());
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