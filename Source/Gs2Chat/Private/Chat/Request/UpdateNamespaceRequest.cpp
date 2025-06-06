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

#include "Chat/Request/UpdateNamespaceRequest.h"

namespace Gs2::Chat::Request
{
    FUpdateNamespaceRequest::FUpdateNamespaceRequest():
        NamespaceNameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        AllowCreateRoomValue(TOptional<bool>()),
        MessageLifeTimeDaysValue(TOptional<int32>()),
        PostMessageScriptValue(nullptr),
        CreateRoomScriptValue(nullptr),
        DeleteRoomScriptValue(nullptr),
        SubscribeRoomScriptValue(nullptr),
        UnsubscribeRoomScriptValue(nullptr),
        PostNotificationValue(nullptr),
        LogSettingValue(nullptr)
    {
    }

    FUpdateNamespaceRequest::FUpdateNamespaceRequest(
        const FUpdateNamespaceRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        DescriptionValue(From.DescriptionValue),
        AllowCreateRoomValue(From.AllowCreateRoomValue),
        MessageLifeTimeDaysValue(From.MessageLifeTimeDaysValue),
        PostMessageScriptValue(From.PostMessageScriptValue),
        CreateRoomScriptValue(From.CreateRoomScriptValue),
        DeleteRoomScriptValue(From.DeleteRoomScriptValue),
        SubscribeRoomScriptValue(From.SubscribeRoomScriptValue),
        UnsubscribeRoomScriptValue(From.UnsubscribeRoomScriptValue),
        PostNotificationValue(From.PostNotificationValue),
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

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::WithAllowCreateRoom(
        const TOptional<bool> AllowCreateRoom
    )
    {
        this->AllowCreateRoomValue = AllowCreateRoom;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::WithMessageLifeTimeDays(
        const TOptional<int32> MessageLifeTimeDays
    )
    {
        this->MessageLifeTimeDaysValue = MessageLifeTimeDays;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::WithPostMessageScript(
        const TSharedPtr<Model::FScriptSetting> PostMessageScript
    )
    {
        this->PostMessageScriptValue = PostMessageScript;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::WithCreateRoomScript(
        const TSharedPtr<Model::FScriptSetting> CreateRoomScript
    )
    {
        this->CreateRoomScriptValue = CreateRoomScript;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::WithDeleteRoomScript(
        const TSharedPtr<Model::FScriptSetting> DeleteRoomScript
    )
    {
        this->DeleteRoomScriptValue = DeleteRoomScript;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::WithSubscribeRoomScript(
        const TSharedPtr<Model::FScriptSetting> SubscribeRoomScript
    )
    {
        this->SubscribeRoomScriptValue = SubscribeRoomScript;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::WithUnsubscribeRoomScript(
        const TSharedPtr<Model::FScriptSetting> UnsubscribeRoomScript
    )
    {
        this->UnsubscribeRoomScriptValue = UnsubscribeRoomScript;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::WithPostNotification(
        const TSharedPtr<Model::FNotificationSetting> PostNotification
    )
    {
        this->PostNotificationValue = PostNotification;
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

    TOptional<bool> FUpdateNamespaceRequest::GetAllowCreateRoom() const
    {
        return AllowCreateRoomValue;
    }

    FString FUpdateNamespaceRequest::GetAllowCreateRoomString() const
    {
        if (!AllowCreateRoomValue.IsSet())
        {
            return FString("null");
        }
        return FString(AllowCreateRoomValue.GetValue() ? "true" : "false");
    }

    TOptional<int32> FUpdateNamespaceRequest::GetMessageLifeTimeDays() const
    {
        return MessageLifeTimeDaysValue;
    }

    FString FUpdateNamespaceRequest::GetMessageLifeTimeDaysString() const
    {
        if (!MessageLifeTimeDaysValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), MessageLifeTimeDaysValue.GetValue());
    }

    TSharedPtr<Model::FScriptSetting> FUpdateNamespaceRequest::GetPostMessageScript() const
    {
        if (!PostMessageScriptValue.IsValid())
        {
            return nullptr;
        }
        return PostMessageScriptValue;
    }

    TSharedPtr<Model::FScriptSetting> FUpdateNamespaceRequest::GetCreateRoomScript() const
    {
        if (!CreateRoomScriptValue.IsValid())
        {
            return nullptr;
        }
        return CreateRoomScriptValue;
    }

    TSharedPtr<Model::FScriptSetting> FUpdateNamespaceRequest::GetDeleteRoomScript() const
    {
        if (!DeleteRoomScriptValue.IsValid())
        {
            return nullptr;
        }
        return DeleteRoomScriptValue;
    }

    TSharedPtr<Model::FScriptSetting> FUpdateNamespaceRequest::GetSubscribeRoomScript() const
    {
        if (!SubscribeRoomScriptValue.IsValid())
        {
            return nullptr;
        }
        return SubscribeRoomScriptValue;
    }

    TSharedPtr<Model::FScriptSetting> FUpdateNamespaceRequest::GetUnsubscribeRoomScript() const
    {
        if (!UnsubscribeRoomScriptValue.IsValid())
        {
            return nullptr;
        }
        return UnsubscribeRoomScriptValue;
    }

    TSharedPtr<Model::FNotificationSetting> FUpdateNamespaceRequest::GetPostNotification() const
    {
        if (!PostNotificationValue.IsValid())
        {
            return nullptr;
        }
        return PostNotificationValue;
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
            ->WithDescription(Data->HasField(ANSI_TO_TCHAR("description")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("description"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithAllowCreateRoom(Data->HasField(ANSI_TO_TCHAR("allowCreateRoom")) ? [Data]() -> TOptional<bool>
              {
                  bool v;
                    if (Data->TryGetBoolField(ANSI_TO_TCHAR("allowCreateRoom"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<bool>();
              }() : TOptional<bool>())
            ->WithMessageLifeTimeDays(Data->HasField(ANSI_TO_TCHAR("messageLifeTimeDays")) ? [Data]() -> TOptional<int32>
              {
                  int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("messageLifeTimeDays"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int32>();
              }() : TOptional<int32>())
          ->WithPostMessageScript(Data->HasField(ANSI_TO_TCHAR("postMessageScript")) ? [Data]() -> Model::FScriptSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("postMessageScript")))
                  {
                      return nullptr;
                  }
                  return Model::FScriptSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("postMessageScript")));
              }() : nullptr)
          ->WithCreateRoomScript(Data->HasField(ANSI_TO_TCHAR("createRoomScript")) ? [Data]() -> Model::FScriptSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("createRoomScript")))
                  {
                      return nullptr;
                  }
                  return Model::FScriptSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("createRoomScript")));
              }() : nullptr)
          ->WithDeleteRoomScript(Data->HasField(ANSI_TO_TCHAR("deleteRoomScript")) ? [Data]() -> Model::FScriptSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("deleteRoomScript")))
                  {
                      return nullptr;
                  }
                  return Model::FScriptSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("deleteRoomScript")));
              }() : nullptr)
          ->WithSubscribeRoomScript(Data->HasField(ANSI_TO_TCHAR("subscribeRoomScript")) ? [Data]() -> Model::FScriptSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("subscribeRoomScript")))
                  {
                      return nullptr;
                  }
                  return Model::FScriptSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("subscribeRoomScript")));
              }() : nullptr)
          ->WithUnsubscribeRoomScript(Data->HasField(ANSI_TO_TCHAR("unsubscribeRoomScript")) ? [Data]() -> Model::FScriptSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("unsubscribeRoomScript")))
                  {
                      return nullptr;
                  }
                  return Model::FScriptSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("unsubscribeRoomScript")));
              }() : nullptr)
          ->WithPostNotification(Data->HasField(ANSI_TO_TCHAR("postNotification")) ? [Data]() -> Model::FNotificationSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("postNotification")))
                  {
                      return nullptr;
                  }
                  return Model::FNotificationSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("postNotification")));
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
        if (DescriptionValue.IsSet())
        {
            JsonRootObject->SetStringField("description", DescriptionValue.GetValue());
        }
        if (AllowCreateRoomValue.IsSet())
        {
            JsonRootObject->SetBoolField("allowCreateRoom", AllowCreateRoomValue.GetValue());
        }
        if (MessageLifeTimeDaysValue.IsSet())
        {
            JsonRootObject->SetNumberField("messageLifeTimeDays", MessageLifeTimeDaysValue.GetValue());
        }
        if (PostMessageScriptValue != nullptr && PostMessageScriptValue.IsValid())
        {
            JsonRootObject->SetObjectField("postMessageScript", PostMessageScriptValue->ToJson());
        }
        if (CreateRoomScriptValue != nullptr && CreateRoomScriptValue.IsValid())
        {
            JsonRootObject->SetObjectField("createRoomScript", CreateRoomScriptValue->ToJson());
        }
        if (DeleteRoomScriptValue != nullptr && DeleteRoomScriptValue.IsValid())
        {
            JsonRootObject->SetObjectField("deleteRoomScript", DeleteRoomScriptValue->ToJson());
        }
        if (SubscribeRoomScriptValue != nullptr && SubscribeRoomScriptValue.IsValid())
        {
            JsonRootObject->SetObjectField("subscribeRoomScript", SubscribeRoomScriptValue->ToJson());
        }
        if (UnsubscribeRoomScriptValue != nullptr && UnsubscribeRoomScriptValue.IsValid())
        {
            JsonRootObject->SetObjectField("unsubscribeRoomScript", UnsubscribeRoomScriptValue->ToJson());
        }
        if (PostNotificationValue != nullptr && PostNotificationValue.IsValid())
        {
            JsonRootObject->SetObjectField("postNotification", PostNotificationValue->ToJson());
        }
        if (LogSettingValue != nullptr && LogSettingValue.IsValid())
        {
            JsonRootObject->SetObjectField("logSetting", LogSettingValue->ToJson());
        }
        return JsonRootObject;
    }
}