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

#include "Guild/Request/CreateNamespaceRequest.h"

namespace Gs2::Guild::Request
{
    FCreateNamespaceRequest::FCreateNamespaceRequest():
        NameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        JoinNotificationValue(nullptr),
        LeaveNotificationValue(nullptr),
        ChangeMemberNotificationValue(nullptr),
        ReceiveRequestNotificationValue(nullptr),
        RemoveRequestNotificationValue(nullptr),
        LogSettingValue(nullptr)
    {
    }

    FCreateNamespaceRequest::FCreateNamespaceRequest(
        const FCreateNamespaceRequest& From
    ):
        NameValue(From.NameValue),
        DescriptionValue(From.DescriptionValue),
        JoinNotificationValue(From.JoinNotificationValue),
        LeaveNotificationValue(From.LeaveNotificationValue),
        ChangeMemberNotificationValue(From.ChangeMemberNotificationValue),
        ReceiveRequestNotificationValue(From.ReceiveRequestNotificationValue),
        RemoveRequestNotificationValue(From.RemoveRequestNotificationValue),
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

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithJoinNotification(
        const TSharedPtr<Model::FNotificationSetting> JoinNotification
    )
    {
        this->JoinNotificationValue = JoinNotification;
        return SharedThis(this);
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithLeaveNotification(
        const TSharedPtr<Model::FNotificationSetting> LeaveNotification
    )
    {
        this->LeaveNotificationValue = LeaveNotification;
        return SharedThis(this);
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithChangeMemberNotification(
        const TSharedPtr<Model::FNotificationSetting> ChangeMemberNotification
    )
    {
        this->ChangeMemberNotificationValue = ChangeMemberNotification;
        return SharedThis(this);
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithReceiveRequestNotification(
        const TSharedPtr<Model::FNotificationSetting> ReceiveRequestNotification
    )
    {
        this->ReceiveRequestNotificationValue = ReceiveRequestNotification;
        return SharedThis(this);
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithRemoveRequestNotification(
        const TSharedPtr<Model::FNotificationSetting> RemoveRequestNotification
    )
    {
        this->RemoveRequestNotificationValue = RemoveRequestNotification;
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

    TSharedPtr<Model::FNotificationSetting> FCreateNamespaceRequest::GetJoinNotification() const
    {
        if (!JoinNotificationValue.IsValid())
        {
            return nullptr;
        }
        return JoinNotificationValue;
    }

    TSharedPtr<Model::FNotificationSetting> FCreateNamespaceRequest::GetLeaveNotification() const
    {
        if (!LeaveNotificationValue.IsValid())
        {
            return nullptr;
        }
        return LeaveNotificationValue;
    }

    TSharedPtr<Model::FNotificationSetting> FCreateNamespaceRequest::GetChangeMemberNotification() const
    {
        if (!ChangeMemberNotificationValue.IsValid())
        {
            return nullptr;
        }
        return ChangeMemberNotificationValue;
    }

    TSharedPtr<Model::FNotificationSetting> FCreateNamespaceRequest::GetReceiveRequestNotification() const
    {
        if (!ReceiveRequestNotificationValue.IsValid())
        {
            return nullptr;
        }
        return ReceiveRequestNotificationValue;
    }

    TSharedPtr<Model::FNotificationSetting> FCreateNamespaceRequest::GetRemoveRequestNotification() const
    {
        if (!RemoveRequestNotificationValue.IsValid())
        {
            return nullptr;
        }
        return RemoveRequestNotificationValue;
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
                  FString v("");
                    if (Data->TryGetStringField("name", v))
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
          ->WithJoinNotification(Data->HasField("joinNotification") ? [Data]() -> Model::FNotificationSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>("joinNotification"))
                  {
                      return nullptr;
                  }
                  return Model::FNotificationSetting::FromJson(Data->GetObjectField("joinNotification"));
              }() : nullptr)
          ->WithLeaveNotification(Data->HasField("leaveNotification") ? [Data]() -> Model::FNotificationSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>("leaveNotification"))
                  {
                      return nullptr;
                  }
                  return Model::FNotificationSetting::FromJson(Data->GetObjectField("leaveNotification"));
              }() : nullptr)
          ->WithChangeMemberNotification(Data->HasField("changeMemberNotification") ? [Data]() -> Model::FNotificationSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>("changeMemberNotification"))
                  {
                      return nullptr;
                  }
                  return Model::FNotificationSetting::FromJson(Data->GetObjectField("changeMemberNotification"));
              }() : nullptr)
          ->WithReceiveRequestNotification(Data->HasField("receiveRequestNotification") ? [Data]() -> Model::FNotificationSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>("receiveRequestNotification"))
                  {
                      return nullptr;
                  }
                  return Model::FNotificationSetting::FromJson(Data->GetObjectField("receiveRequestNotification"));
              }() : nullptr)
          ->WithRemoveRequestNotification(Data->HasField("removeRequestNotification") ? [Data]() -> Model::FNotificationSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>("removeRequestNotification"))
                  {
                      return nullptr;
                  }
                  return Model::FNotificationSetting::FromJson(Data->GetObjectField("removeRequestNotification"));
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
        if (DescriptionValue.IsSet())
        {
            JsonRootObject->SetStringField("description", DescriptionValue.GetValue());
        }
        if (JoinNotificationValue != nullptr && JoinNotificationValue.IsValid())
        {
            JsonRootObject->SetObjectField("joinNotification", JoinNotificationValue->ToJson());
        }
        if (LeaveNotificationValue != nullptr && LeaveNotificationValue.IsValid())
        {
            JsonRootObject->SetObjectField("leaveNotification", LeaveNotificationValue->ToJson());
        }
        if (ChangeMemberNotificationValue != nullptr && ChangeMemberNotificationValue.IsValid())
        {
            JsonRootObject->SetObjectField("changeMemberNotification", ChangeMemberNotificationValue->ToJson());
        }
        if (ReceiveRequestNotificationValue != nullptr && ReceiveRequestNotificationValue.IsValid())
        {
            JsonRootObject->SetObjectField("receiveRequestNotification", ReceiveRequestNotificationValue->ToJson());
        }
        if (RemoveRequestNotificationValue != nullptr && RemoveRequestNotificationValue.IsValid())
        {
            JsonRootObject->SetObjectField("removeRequestNotification", RemoveRequestNotificationValue->ToJson());
        }
        if (LogSettingValue != nullptr && LogSettingValue.IsValid())
        {
            JsonRootObject->SetObjectField("logSetting", LogSettingValue->ToJson());
        }
        return JsonRootObject;
    }
}