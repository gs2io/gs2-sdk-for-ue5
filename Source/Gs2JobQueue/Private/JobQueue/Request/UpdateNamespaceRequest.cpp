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

#include "JobQueue/Request/UpdateNamespaceRequest.h"

namespace Gs2::JobQueue::Request
{
    FUpdateNamespaceRequest::FUpdateNamespaceRequest():
        NamespaceNameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        EnableAutoRunValue(TOptional<bool>()),
        PushNotificationValue(nullptr),
        RunNotificationValue(nullptr),
        LogSettingValue(nullptr)
    {
    }

    FUpdateNamespaceRequest::FUpdateNamespaceRequest(
        const FUpdateNamespaceRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        DescriptionValue(From.DescriptionValue),
        EnableAutoRunValue(From.EnableAutoRunValue),
        PushNotificationValue(From.PushNotificationValue),
        RunNotificationValue(From.RunNotificationValue),
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

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::WithEnableAutoRun(
        const TOptional<bool> EnableAutoRun
    )
    {
        this->EnableAutoRunValue = EnableAutoRun;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::WithPushNotification(
        const TSharedPtr<Model::FNotificationSetting> PushNotification
    )
    {
        this->PushNotificationValue = PushNotification;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::WithRunNotification(
        const TSharedPtr<Model::FNotificationSetting> RunNotification
    )
    {
        this->RunNotificationValue = RunNotification;
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

    TOptional<bool> FUpdateNamespaceRequest::GetEnableAutoRun() const
    {
        return EnableAutoRunValue;
    }

    FString FUpdateNamespaceRequest::GetEnableAutoRunString() const
    {
        if (!EnableAutoRunValue.IsSet())
        {
            return FString("null");
        }
        return FString(EnableAutoRunValue.GetValue() ? "true" : "false");
    }

    TSharedPtr<Model::FNotificationSetting> FUpdateNamespaceRequest::GetPushNotification() const
    {
        if (!PushNotificationValue.IsValid())
        {
            return nullptr;
        }
        return PushNotificationValue;
    }

    TSharedPtr<Model::FNotificationSetting> FUpdateNamespaceRequest::GetRunNotification() const
    {
        if (!RunNotificationValue.IsValid())
        {
            return nullptr;
        }
        return RunNotificationValue;
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
                  FString v;
                    if (Data->TryGetStringField("namespaceName", v))
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
            ->WithEnableAutoRun(Data->HasField("enableAutoRun") ? [Data]() -> TOptional<bool>
              {
                  bool v;
                    if (Data->TryGetBoolField("enableAutoRun", v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<bool>();
              }() : TOptional<bool>())
          ->WithPushNotification(Data->HasField("pushNotification") ? [Data]() -> Model::FNotificationSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>("pushNotification"))
                  {
                      return nullptr;
                  }
                  return Model::FNotificationSetting::FromJson(Data->GetObjectField("pushNotification"));
             }() : nullptr)
          ->WithRunNotification(Data->HasField("runNotification") ? [Data]() -> Model::FNotificationSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>("runNotification"))
                  {
                      return nullptr;
                  }
                  return Model::FNotificationSetting::FromJson(Data->GetObjectField("runNotification"));
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
        if (EnableAutoRunValue.IsSet())
        {
            JsonRootObject->SetBoolField("enableAutoRun", EnableAutoRunValue.GetValue());
        }
        if (PushNotificationValue != nullptr && PushNotificationValue.IsValid())
        {
            JsonRootObject->SetObjectField("pushNotification", PushNotificationValue->ToJson());
        }
        if (RunNotificationValue != nullptr && RunNotificationValue.IsValid())
        {
            JsonRootObject->SetObjectField("runNotification", RunNotificationValue->ToJson());
        }
        if (LogSettingValue != nullptr && LogSettingValue.IsValid())
        {
            JsonRootObject->SetObjectField("logSetting", LogSettingValue->ToJson());
        }
        return JsonRootObject;
    }
}