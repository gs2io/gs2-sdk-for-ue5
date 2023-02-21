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

#include "Friend/Request/UpdateNamespaceRequest.h"

namespace Gs2::Friend::Request
{
    FUpdateNamespaceRequest::FUpdateNamespaceRequest():
        NamespaceNameValue(TOptional<FString>()),
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

    FUpdateNamespaceRequest::FUpdateNamespaceRequest(
        const FUpdateNamespaceRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
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

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::WithFollowScript(
        const TSharedPtr<Model::FScriptSetting> FollowScript
    )
    {
        this->FollowScriptValue = FollowScript;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::WithUnfollowScript(
        const TSharedPtr<Model::FScriptSetting> UnfollowScript
    )
    {
        this->UnfollowScriptValue = UnfollowScript;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::WithSendRequestScript(
        const TSharedPtr<Model::FScriptSetting> SendRequestScript
    )
    {
        this->SendRequestScriptValue = SendRequestScript;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::WithCancelRequestScript(
        const TSharedPtr<Model::FScriptSetting> CancelRequestScript
    )
    {
        this->CancelRequestScriptValue = CancelRequestScript;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::WithAcceptRequestScript(
        const TSharedPtr<Model::FScriptSetting> AcceptRequestScript
    )
    {
        this->AcceptRequestScriptValue = AcceptRequestScript;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::WithRejectRequestScript(
        const TSharedPtr<Model::FScriptSetting> RejectRequestScript
    )
    {
        this->RejectRequestScriptValue = RejectRequestScript;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::WithDeleteFriendScript(
        const TSharedPtr<Model::FScriptSetting> DeleteFriendScript
    )
    {
        this->DeleteFriendScriptValue = DeleteFriendScript;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::WithUpdateProfileScript(
        const TSharedPtr<Model::FScriptSetting> UpdateProfileScript
    )
    {
        this->UpdateProfileScriptValue = UpdateProfileScript;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::WithFollowNotification(
        const TSharedPtr<Model::FNotificationSetting> FollowNotification
    )
    {
        this->FollowNotificationValue = FollowNotification;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::WithReceiveRequestNotification(
        const TSharedPtr<Model::FNotificationSetting> ReceiveRequestNotification
    )
    {
        this->ReceiveRequestNotificationValue = ReceiveRequestNotification;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::WithAcceptRequestNotification(
        const TSharedPtr<Model::FNotificationSetting> AcceptRequestNotification
    )
    {
        this->AcceptRequestNotificationValue = AcceptRequestNotification;
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

    TSharedPtr<Model::FScriptSetting> FUpdateNamespaceRequest::GetFollowScript() const
    {
        if (!FollowScriptValue.IsValid())
        {
            return nullptr;
        }
        return FollowScriptValue;
    }

    TSharedPtr<Model::FScriptSetting> FUpdateNamespaceRequest::GetUnfollowScript() const
    {
        if (!UnfollowScriptValue.IsValid())
        {
            return nullptr;
        }
        return UnfollowScriptValue;
    }

    TSharedPtr<Model::FScriptSetting> FUpdateNamespaceRequest::GetSendRequestScript() const
    {
        if (!SendRequestScriptValue.IsValid())
        {
            return nullptr;
        }
        return SendRequestScriptValue;
    }

    TSharedPtr<Model::FScriptSetting> FUpdateNamespaceRequest::GetCancelRequestScript() const
    {
        if (!CancelRequestScriptValue.IsValid())
        {
            return nullptr;
        }
        return CancelRequestScriptValue;
    }

    TSharedPtr<Model::FScriptSetting> FUpdateNamespaceRequest::GetAcceptRequestScript() const
    {
        if (!AcceptRequestScriptValue.IsValid())
        {
            return nullptr;
        }
        return AcceptRequestScriptValue;
    }

    TSharedPtr<Model::FScriptSetting> FUpdateNamespaceRequest::GetRejectRequestScript() const
    {
        if (!RejectRequestScriptValue.IsValid())
        {
            return nullptr;
        }
        return RejectRequestScriptValue;
    }

    TSharedPtr<Model::FScriptSetting> FUpdateNamespaceRequest::GetDeleteFriendScript() const
    {
        if (!DeleteFriendScriptValue.IsValid())
        {
            return nullptr;
        }
        return DeleteFriendScriptValue;
    }

    TSharedPtr<Model::FScriptSetting> FUpdateNamespaceRequest::GetUpdateProfileScript() const
    {
        if (!UpdateProfileScriptValue.IsValid())
        {
            return nullptr;
        }
        return UpdateProfileScriptValue;
    }

    TSharedPtr<Model::FNotificationSetting> FUpdateNamespaceRequest::GetFollowNotification() const
    {
        if (!FollowNotificationValue.IsValid())
        {
            return nullptr;
        }
        return FollowNotificationValue;
    }

    TSharedPtr<Model::FNotificationSetting> FUpdateNamespaceRequest::GetReceiveRequestNotification() const
    {
        if (!ReceiveRequestNotificationValue.IsValid())
        {
            return nullptr;
        }
        return ReceiveRequestNotificationValue;
    }

    TSharedPtr<Model::FNotificationSetting> FUpdateNamespaceRequest::GetAcceptRequestNotification() const
    {
        if (!AcceptRequestNotificationValue.IsValid())
        {
            return nullptr;
        }
        return AcceptRequestNotificationValue;
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
          ->WithFollowScript(Data->HasField("followScript") ? [Data]() -> Model::FScriptSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>("followScript"))
                  {
                      return nullptr;
                  }
                  return Model::FScriptSetting::FromJson(Data->GetObjectField("followScript"));
             }() : nullptr)
          ->WithUnfollowScript(Data->HasField("unfollowScript") ? [Data]() -> Model::FScriptSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>("unfollowScript"))
                  {
                      return nullptr;
                  }
                  return Model::FScriptSetting::FromJson(Data->GetObjectField("unfollowScript"));
             }() : nullptr)
          ->WithSendRequestScript(Data->HasField("sendRequestScript") ? [Data]() -> Model::FScriptSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>("sendRequestScript"))
                  {
                      return nullptr;
                  }
                  return Model::FScriptSetting::FromJson(Data->GetObjectField("sendRequestScript"));
             }() : nullptr)
          ->WithCancelRequestScript(Data->HasField("cancelRequestScript") ? [Data]() -> Model::FScriptSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>("cancelRequestScript"))
                  {
                      return nullptr;
                  }
                  return Model::FScriptSetting::FromJson(Data->GetObjectField("cancelRequestScript"));
             }() : nullptr)
          ->WithAcceptRequestScript(Data->HasField("acceptRequestScript") ? [Data]() -> Model::FScriptSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>("acceptRequestScript"))
                  {
                      return nullptr;
                  }
                  return Model::FScriptSetting::FromJson(Data->GetObjectField("acceptRequestScript"));
             }() : nullptr)
          ->WithRejectRequestScript(Data->HasField("rejectRequestScript") ? [Data]() -> Model::FScriptSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>("rejectRequestScript"))
                  {
                      return nullptr;
                  }
                  return Model::FScriptSetting::FromJson(Data->GetObjectField("rejectRequestScript"));
             }() : nullptr)
          ->WithDeleteFriendScript(Data->HasField("deleteFriendScript") ? [Data]() -> Model::FScriptSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>("deleteFriendScript"))
                  {
                      return nullptr;
                  }
                  return Model::FScriptSetting::FromJson(Data->GetObjectField("deleteFriendScript"));
             }() : nullptr)
          ->WithUpdateProfileScript(Data->HasField("updateProfileScript") ? [Data]() -> Model::FScriptSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>("updateProfileScript"))
                  {
                      return nullptr;
                  }
                  return Model::FScriptSetting::FromJson(Data->GetObjectField("updateProfileScript"));
             }() : nullptr)
          ->WithFollowNotification(Data->HasField("followNotification") ? [Data]() -> Model::FNotificationSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>("followNotification"))
                  {
                      return nullptr;
                  }
                  return Model::FNotificationSetting::FromJson(Data->GetObjectField("followNotification"));
             }() : nullptr)
          ->WithReceiveRequestNotification(Data->HasField("receiveRequestNotification") ? [Data]() -> Model::FNotificationSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>("receiveRequestNotification"))
                  {
                      return nullptr;
                  }
                  return Model::FNotificationSetting::FromJson(Data->GetObjectField("receiveRequestNotification"));
             }() : nullptr)
          ->WithAcceptRequestNotification(Data->HasField("acceptRequestNotification") ? [Data]() -> Model::FNotificationSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>("acceptRequestNotification"))
                  {
                      return nullptr;
                  }
                  return Model::FNotificationSetting::FromJson(Data->GetObjectField("acceptRequestNotification"));
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