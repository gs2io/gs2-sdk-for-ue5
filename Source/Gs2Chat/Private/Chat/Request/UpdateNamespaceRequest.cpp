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