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
        AdmobValue(nullptr),
        UnityAdValue(nullptr),
        DescriptionValue(TOptional<FString>()),
        ChangePointNotificationValue(nullptr),
        LogSettingValue(nullptr)
    {
    }

    FCreateNamespaceRequest::FCreateNamespaceRequest(
        const FCreateNamespaceRequest& From
    ):
        NameValue(From.NameValue),
        AdmobValue(From.AdmobValue),
        UnityAdValue(From.UnityAdValue),
        DescriptionValue(From.DescriptionValue),
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

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
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

    TOptional<FString> FCreateNamespaceRequest::GetDescription() const
    {
        return DescriptionValue;
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
            ->WithDescription(Data->HasField("description") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("description", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
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
        if (AdmobValue != nullptr && AdmobValue.IsValid())
        {
            JsonRootObject->SetObjectField("admob", AdmobValue->ToJson());
        }
        if (UnityAdValue != nullptr && UnityAdValue.IsValid())
        {
            JsonRootObject->SetObjectField("unityAd", UnityAdValue->ToJson());
        }
        if (DescriptionValue.IsSet())
        {
            JsonRootObject->SetStringField("description", DescriptionValue.GetValue());
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