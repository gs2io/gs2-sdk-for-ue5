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

#include "Friend/Request/CreateNamespaceRequest.h"

namespace Gs2::Friend::Request
{
    FCreateNamespaceRequest::FCreateNamespaceRequest():
        NameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        FollowScriptValue(nullptr),
        UnfollowScriptValue(nullptr),
        SendRequestScriptValue(nullptr),
        CancelRequestScriptValue(nullptr),
        AcceptRequestScriptValue(nullptr),
        RejectRequestScriptValue(nullptr),
        DeleteFriendScriptValue(nullptr),
        UpdateProfileScriptValue(nullptr),
        FollowNotificationValue(nullptr),
        ReceiveRequestNotificationValue(nullptr),
        AcceptRequestNotificationValue(nullptr),
        LogSettingValue(nullptr)
    {
    }

    FCreateNamespaceRequest::FCreateNamespaceRequest(
        const FCreateNamespaceRequest& From
    ):
        NameValue(From.NameValue),
        DescriptionValue(From.DescriptionValue),
        FollowScriptValue(From.FollowScriptValue),
        UnfollowScriptValue(From.UnfollowScriptValue),
        SendRequestScriptValue(From.SendRequestScriptValue),
        CancelRequestScriptValue(From.CancelRequestScriptValue),
        AcceptRequestScriptValue(From.AcceptRequestScriptValue),
        RejectRequestScriptValue(From.RejectRequestScriptValue),
        DeleteFriendScriptValue(From.DeleteFriendScriptValue),
        UpdateProfileScriptValue(From.UpdateProfileScriptValue),
        FollowNotificationValue(From.FollowNotificationValue),
        ReceiveRequestNotificationValue(From.ReceiveRequestNotificationValue),
        AcceptRequestNotificationValue(From.AcceptRequestNotificationValue),
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

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithFollowScript(
        const TSharedPtr<Model::FScriptSetting> FollowScript
    )
    {
        this->FollowScriptValue = FollowScript;
        return SharedThis(this);
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithUnfollowScript(
        const TSharedPtr<Model::FScriptSetting> UnfollowScript
    )
    {
        this->UnfollowScriptValue = UnfollowScript;
        return SharedThis(this);
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithSendRequestScript(
        const TSharedPtr<Model::FScriptSetting> SendRequestScript
    )
    {
        this->SendRequestScriptValue = SendRequestScript;
        return SharedThis(this);
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithCancelRequestScript(
        const TSharedPtr<Model::FScriptSetting> CancelRequestScript
    )
    {
        this->CancelRequestScriptValue = CancelRequestScript;
        return SharedThis(this);
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithAcceptRequestScript(
        const TSharedPtr<Model::FScriptSetting> AcceptRequestScript
    )
    {
        this->AcceptRequestScriptValue = AcceptRequestScript;
        return SharedThis(this);
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithRejectRequestScript(
        const TSharedPtr<Model::FScriptSetting> RejectRequestScript
    )
    {
        this->RejectRequestScriptValue = RejectRequestScript;
        return SharedThis(this);
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithDeleteFriendScript(
        const TSharedPtr<Model::FScriptSetting> DeleteFriendScript
    )
    {
        this->DeleteFriendScriptValue = DeleteFriendScript;
        return SharedThis(this);
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithUpdateProfileScript(
        const TSharedPtr<Model::FScriptSetting> UpdateProfileScript
    )
    {
        this->UpdateProfileScriptValue = UpdateProfileScript;
        return SharedThis(this);
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithFollowNotification(
        const TSharedPtr<Model::FNotificationSetting> FollowNotification
    )
    {
        this->FollowNotificationValue = FollowNotification;
        return SharedThis(this);
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithReceiveRequestNotification(
        const TSharedPtr<Model::FNotificationSetting> ReceiveRequestNotification
    )
    {
        this->ReceiveRequestNotificationValue = ReceiveRequestNotification;
        return SharedThis(this);
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithAcceptRequestNotification(
        const TSharedPtr<Model::FNotificationSetting> AcceptRequestNotification
    )
    {
        this->AcceptRequestNotificationValue = AcceptRequestNotification;
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

    TSharedPtr<Model::FScriptSetting> FCreateNamespaceRequest::GetFollowScript() const
    {
        if (!FollowScriptValue.IsValid())
        {
            return nullptr;
        }
        return FollowScriptValue;
    }

    TSharedPtr<Model::FScriptSetting> FCreateNamespaceRequest::GetUnfollowScript() const
    {
        if (!UnfollowScriptValue.IsValid())
        {
            return nullptr;
        }
        return UnfollowScriptValue;
    }

    TSharedPtr<Model::FScriptSetting> FCreateNamespaceRequest::GetSendRequestScript() const
    {
        if (!SendRequestScriptValue.IsValid())
        {
            return nullptr;
        }
        return SendRequestScriptValue;
    }

    TSharedPtr<Model::FScriptSetting> FCreateNamespaceRequest::GetCancelRequestScript() const
    {
        if (!CancelRequestScriptValue.IsValid())
        {
            return nullptr;
        }
        return CancelRequestScriptValue;
    }

    TSharedPtr<Model::FScriptSetting> FCreateNamespaceRequest::GetAcceptRequestScript() const
    {
        if (!AcceptRequestScriptValue.IsValid())
        {
            return nullptr;
        }
        return AcceptRequestScriptValue;
    }

    TSharedPtr<Model::FScriptSetting> FCreateNamespaceRequest::GetRejectRequestScript() const
    {
        if (!RejectRequestScriptValue.IsValid())
        {
            return nullptr;
        }
        return RejectRequestScriptValue;
    }

    TSharedPtr<Model::FScriptSetting> FCreateNamespaceRequest::GetDeleteFriendScript() const
    {
        if (!DeleteFriendScriptValue.IsValid())
        {
            return nullptr;
        }
        return DeleteFriendScriptValue;
    }

    TSharedPtr<Model::FScriptSetting> FCreateNamespaceRequest::GetUpdateProfileScript() const
    {
        if (!UpdateProfileScriptValue.IsValid())
        {
            return nullptr;
        }
        return UpdateProfileScriptValue;
    }

    TSharedPtr<Model::FNotificationSetting> FCreateNamespaceRequest::GetFollowNotification() const
    {
        if (!FollowNotificationValue.IsValid())
        {
            return nullptr;
        }
        return FollowNotificationValue;
    }

    TSharedPtr<Model::FNotificationSetting> FCreateNamespaceRequest::GetReceiveRequestNotification() const
    {
        if (!ReceiveRequestNotificationValue.IsValid())
        {
            return nullptr;
        }
        return ReceiveRequestNotificationValue;
    }

    TSharedPtr<Model::FNotificationSetting> FCreateNamespaceRequest::GetAcceptRequestNotification() const
    {
        if (!AcceptRequestNotificationValue.IsValid())
        {
            return nullptr;
        }
        return AcceptRequestNotificationValue;
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
          ->WithFollowScript(Data->HasField(ANSI_TO_TCHAR("followScript")) ? [Data]() -> Model::FScriptSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("followScript")))
                  {
                      return nullptr;
                  }
                  return Model::FScriptSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("followScript")));
              }() : nullptr)
          ->WithUnfollowScript(Data->HasField(ANSI_TO_TCHAR("unfollowScript")) ? [Data]() -> Model::FScriptSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("unfollowScript")))
                  {
                      return nullptr;
                  }
                  return Model::FScriptSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("unfollowScript")));
              }() : nullptr)
          ->WithSendRequestScript(Data->HasField(ANSI_TO_TCHAR("sendRequestScript")) ? [Data]() -> Model::FScriptSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("sendRequestScript")))
                  {
                      return nullptr;
                  }
                  return Model::FScriptSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("sendRequestScript")));
              }() : nullptr)
          ->WithCancelRequestScript(Data->HasField(ANSI_TO_TCHAR("cancelRequestScript")) ? [Data]() -> Model::FScriptSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("cancelRequestScript")))
                  {
                      return nullptr;
                  }
                  return Model::FScriptSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("cancelRequestScript")));
              }() : nullptr)
          ->WithAcceptRequestScript(Data->HasField(ANSI_TO_TCHAR("acceptRequestScript")) ? [Data]() -> Model::FScriptSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("acceptRequestScript")))
                  {
                      return nullptr;
                  }
                  return Model::FScriptSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("acceptRequestScript")));
              }() : nullptr)
          ->WithRejectRequestScript(Data->HasField(ANSI_TO_TCHAR("rejectRequestScript")) ? [Data]() -> Model::FScriptSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("rejectRequestScript")))
                  {
                      return nullptr;
                  }
                  return Model::FScriptSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("rejectRequestScript")));
              }() : nullptr)
          ->WithDeleteFriendScript(Data->HasField(ANSI_TO_TCHAR("deleteFriendScript")) ? [Data]() -> Model::FScriptSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("deleteFriendScript")))
                  {
                      return nullptr;
                  }
                  return Model::FScriptSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("deleteFriendScript")));
              }() : nullptr)
          ->WithUpdateProfileScript(Data->HasField(ANSI_TO_TCHAR("updateProfileScript")) ? [Data]() -> Model::FScriptSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("updateProfileScript")))
                  {
                      return nullptr;
                  }
                  return Model::FScriptSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("updateProfileScript")));
              }() : nullptr)
          ->WithFollowNotification(Data->HasField(ANSI_TO_TCHAR("followNotification")) ? [Data]() -> Model::FNotificationSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("followNotification")))
                  {
                      return nullptr;
                  }
                  return Model::FNotificationSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("followNotification")));
              }() : nullptr)
          ->WithReceiveRequestNotification(Data->HasField(ANSI_TO_TCHAR("receiveRequestNotification")) ? [Data]() -> Model::FNotificationSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("receiveRequestNotification")))
                  {
                      return nullptr;
                  }
                  return Model::FNotificationSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("receiveRequestNotification")));
              }() : nullptr)
          ->WithAcceptRequestNotification(Data->HasField(ANSI_TO_TCHAR("acceptRequestNotification")) ? [Data]() -> Model::FNotificationSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("acceptRequestNotification")))
                  {
                      return nullptr;
                  }
                  return Model::FNotificationSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("acceptRequestNotification")));
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
        if (FollowScriptValue != nullptr && FollowScriptValue.IsValid())
        {
            JsonRootObject->SetObjectField("followScript", FollowScriptValue->ToJson());
        }
        if (UnfollowScriptValue != nullptr && UnfollowScriptValue.IsValid())
        {
            JsonRootObject->SetObjectField("unfollowScript", UnfollowScriptValue->ToJson());
        }
        if (SendRequestScriptValue != nullptr && SendRequestScriptValue.IsValid())
        {
            JsonRootObject->SetObjectField("sendRequestScript", SendRequestScriptValue->ToJson());
        }
        if (CancelRequestScriptValue != nullptr && CancelRequestScriptValue.IsValid())
        {
            JsonRootObject->SetObjectField("cancelRequestScript", CancelRequestScriptValue->ToJson());
        }
        if (AcceptRequestScriptValue != nullptr && AcceptRequestScriptValue.IsValid())
        {
            JsonRootObject->SetObjectField("acceptRequestScript", AcceptRequestScriptValue->ToJson());
        }
        if (RejectRequestScriptValue != nullptr && RejectRequestScriptValue.IsValid())
        {
            JsonRootObject->SetObjectField("rejectRequestScript", RejectRequestScriptValue->ToJson());
        }
        if (DeleteFriendScriptValue != nullptr && DeleteFriendScriptValue.IsValid())
        {
            JsonRootObject->SetObjectField("deleteFriendScript", DeleteFriendScriptValue->ToJson());
        }
        if (UpdateProfileScriptValue != nullptr && UpdateProfileScriptValue.IsValid())
        {
            JsonRootObject->SetObjectField("updateProfileScript", UpdateProfileScriptValue->ToJson());
        }
        if (FollowNotificationValue != nullptr && FollowNotificationValue.IsValid())
        {
            JsonRootObject->SetObjectField("followNotification", FollowNotificationValue->ToJson());
        }
        if (ReceiveRequestNotificationValue != nullptr && ReceiveRequestNotificationValue.IsValid())
        {
            JsonRootObject->SetObjectField("receiveRequestNotification", ReceiveRequestNotificationValue->ToJson());
        }
        if (AcceptRequestNotificationValue != nullptr && AcceptRequestNotificationValue.IsValid())
        {
            JsonRootObject->SetObjectField("acceptRequestNotification", AcceptRequestNotificationValue->ToJson());
        }
        if (LogSettingValue != nullptr && LogSettingValue.IsValid())
        {
            JsonRootObject->SetObjectField("logSetting", LogSettingValue->ToJson());
        }
        return JsonRootObject;
    }
}