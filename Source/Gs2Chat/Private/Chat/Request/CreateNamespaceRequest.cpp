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

#include "Chat/Request/CreateNamespaceRequest.h"

namespace Gs2::Chat::Request
{
    FCreateNamespaceRequest::FCreateNamespaceRequest():
        NameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        AllowCreateRoomValue(TOptional<bool>()),
        PostMessageScriptValue(nullptr),
        CreateRoomScriptValue(nullptr),
        DeleteRoomScriptValue(nullptr),
        SubscribeRoomScriptValue(nullptr),
        UnsubscribeRoomScriptValue(nullptr),
        PostNotificationValue(nullptr),
        LogSettingValue(nullptr)
    {
    }

    FCreateNamespaceRequest::FCreateNamespaceRequest(
        const FCreateNamespaceRequest& From
    ):
        NameValue(From.NameValue),
        DescriptionValue(From.DescriptionValue),
        AllowCreateRoomValue(From.AllowCreateRoomValue),
        PostMessageScriptValue(From.PostMessageScriptValue),
        CreateRoomScriptValue(From.CreateRoomScriptValue),
        DeleteRoomScriptValue(From.DeleteRoomScriptValue),
        SubscribeRoomScriptValue(From.SubscribeRoomScriptValue),
        UnsubscribeRoomScriptValue(From.UnsubscribeRoomScriptValue),
        PostNotificationValue(From.PostNotificationValue),
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

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithAllowCreateRoom(
        const TOptional<bool> AllowCreateRoom
    )
    {
        this->AllowCreateRoomValue = AllowCreateRoom;
        return SharedThis(this);
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithPostMessageScript(
        const TSharedPtr<Model::FScriptSetting> PostMessageScript
    )
    {
        this->PostMessageScriptValue = PostMessageScript;
        return SharedThis(this);
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithCreateRoomScript(
        const TSharedPtr<Model::FScriptSetting> CreateRoomScript
    )
    {
        this->CreateRoomScriptValue = CreateRoomScript;
        return SharedThis(this);
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithDeleteRoomScript(
        const TSharedPtr<Model::FScriptSetting> DeleteRoomScript
    )
    {
        this->DeleteRoomScriptValue = DeleteRoomScript;
        return SharedThis(this);
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithSubscribeRoomScript(
        const TSharedPtr<Model::FScriptSetting> SubscribeRoomScript
    )
    {
        this->SubscribeRoomScriptValue = SubscribeRoomScript;
        return SharedThis(this);
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithUnsubscribeRoomScript(
        const TSharedPtr<Model::FScriptSetting> UnsubscribeRoomScript
    )
    {
        this->UnsubscribeRoomScriptValue = UnsubscribeRoomScript;
        return SharedThis(this);
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithPostNotification(
        const TSharedPtr<Model::FNotificationSetting> PostNotification
    )
    {
        this->PostNotificationValue = PostNotification;
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

    TOptional<bool> FCreateNamespaceRequest::GetAllowCreateRoom() const
    {
        return AllowCreateRoomValue;
    }

    FString FCreateNamespaceRequest::GetAllowCreateRoomString() const
    {
        if (!AllowCreateRoomValue.IsSet())
        {
            return FString("null");
        }
        return FString(AllowCreateRoomValue.GetValue() ? "true" : "false");
    }

    TSharedPtr<Model::FScriptSetting> FCreateNamespaceRequest::GetPostMessageScript() const
    {
        if (!PostMessageScriptValue.IsValid())
        {
            return nullptr;
        }
        return PostMessageScriptValue;
    }

    TSharedPtr<Model::FScriptSetting> FCreateNamespaceRequest::GetCreateRoomScript() const
    {
        if (!CreateRoomScriptValue.IsValid())
        {
            return nullptr;
        }
        return CreateRoomScriptValue;
    }

    TSharedPtr<Model::FScriptSetting> FCreateNamespaceRequest::GetDeleteRoomScript() const
    {
        if (!DeleteRoomScriptValue.IsValid())
        {
            return nullptr;
        }
        return DeleteRoomScriptValue;
    }

    TSharedPtr<Model::FScriptSetting> FCreateNamespaceRequest::GetSubscribeRoomScript() const
    {
        if (!SubscribeRoomScriptValue.IsValid())
        {
            return nullptr;
        }
        return SubscribeRoomScriptValue;
    }

    TSharedPtr<Model::FScriptSetting> FCreateNamespaceRequest::GetUnsubscribeRoomScript() const
    {
        if (!UnsubscribeRoomScriptValue.IsValid())
        {
            return nullptr;
        }
        return UnsubscribeRoomScriptValue;
    }

    TSharedPtr<Model::FNotificationSetting> FCreateNamespaceRequest::GetPostNotification() const
    {
        if (!PostNotificationValue.IsValid())
        {
            return nullptr;
        }
        return PostNotificationValue;
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
            ->WithAllowCreateRoom(Data->HasField("allowCreateRoom") ? [Data]() -> TOptional<bool>
              {
                  bool v;
                    if (Data->TryGetBoolField("allowCreateRoom", v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<bool>();
              }() : TOptional<bool>())
          ->WithPostMessageScript(Data->HasField("postMessageScript") ? [Data]() -> Model::FScriptSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>("postMessageScript"))
                  {
                      return nullptr;
                  }
                  return Model::FScriptSetting::FromJson(Data->GetObjectField("postMessageScript"));
              }() : nullptr)
          ->WithCreateRoomScript(Data->HasField("createRoomScript") ? [Data]() -> Model::FScriptSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>("createRoomScript"))
                  {
                      return nullptr;
                  }
                  return Model::FScriptSetting::FromJson(Data->GetObjectField("createRoomScript"));
              }() : nullptr)
          ->WithDeleteRoomScript(Data->HasField("deleteRoomScript") ? [Data]() -> Model::FScriptSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>("deleteRoomScript"))
                  {
                      return nullptr;
                  }
                  return Model::FScriptSetting::FromJson(Data->GetObjectField("deleteRoomScript"));
              }() : nullptr)
          ->WithSubscribeRoomScript(Data->HasField("subscribeRoomScript") ? [Data]() -> Model::FScriptSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>("subscribeRoomScript"))
                  {
                      return nullptr;
                  }
                  return Model::FScriptSetting::FromJson(Data->GetObjectField("subscribeRoomScript"));
              }() : nullptr)
          ->WithUnsubscribeRoomScript(Data->HasField("unsubscribeRoomScript") ? [Data]() -> Model::FScriptSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>("unsubscribeRoomScript"))
                  {
                      return nullptr;
                  }
                  return Model::FScriptSetting::FromJson(Data->GetObjectField("unsubscribeRoomScript"));
              }() : nullptr)
          ->WithPostNotification(Data->HasField("postNotification") ? [Data]() -> Model::FNotificationSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>("postNotification"))
                  {
                      return nullptr;
                  }
                  return Model::FNotificationSetting::FromJson(Data->GetObjectField("postNotification"));
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
        if (AllowCreateRoomValue.IsSet())
        {
            JsonRootObject->SetBoolField("allowCreateRoom", AllowCreateRoomValue.GetValue());
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