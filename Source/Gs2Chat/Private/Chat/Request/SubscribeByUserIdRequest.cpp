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

#include "Chat/Request/SubscribeByUserIdRequest.h"

namespace Gs2::Chat::Request
{
    FSubscribeByUserIdRequest::FSubscribeByUserIdRequest():
        NamespaceNameValue(TOptional<FString>()),
        RoomNameValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        NotificationTypesValue(nullptr)
    {
    }

    FSubscribeByUserIdRequest::FSubscribeByUserIdRequest(
        const FSubscribeByUserIdRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        RoomNameValue(From.RoomNameValue),
        UserIdValue(From.UserIdValue),
        NotificationTypesValue(From.NotificationTypesValue)
    {
    }

    TSharedPtr<FSubscribeByUserIdRequest> FSubscribeByUserIdRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FSubscribeByUserIdRequest> FSubscribeByUserIdRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FSubscribeByUserIdRequest> FSubscribeByUserIdRequest::WithRoomName(
        const TOptional<FString> RoomName
    )
    {
        this->RoomNameValue = RoomName;
        return SharedThis(this);
    }

    TSharedPtr<FSubscribeByUserIdRequest> FSubscribeByUserIdRequest::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FSubscribeByUserIdRequest> FSubscribeByUserIdRequest::WithNotificationTypes(
        const TSharedPtr<TArray<TSharedPtr<Model::FNotificationType>>> NotificationTypes
    )
    {
        this->NotificationTypesValue = NotificationTypes;
        return SharedThis(this);
    }

    TSharedPtr<FSubscribeByUserIdRequest> FSubscribeByUserIdRequest::WithDuplicationAvoider(
        const TOptional<FString> DuplicationAvoider
    )
    {
        this->DuplicationAvoiderValue = DuplicationAvoider;
        return SharedThis(this);
    }

    TOptional<FString> FSubscribeByUserIdRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FSubscribeByUserIdRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FSubscribeByUserIdRequest::GetRoomName() const
    {
        return RoomNameValue;
    }

    TOptional<FString> FSubscribeByUserIdRequest::GetUserId() const
    {
        return UserIdValue;
    }

    TSharedPtr<TArray<TSharedPtr<Model::FNotificationType>>> FSubscribeByUserIdRequest::GetNotificationTypes() const
    {
        if (!NotificationTypesValue.IsValid())
        {
            return nullptr;
        }
        return NotificationTypesValue;
    }

    TOptional<FString> FSubscribeByUserIdRequest::GetDuplicationAvoider() const
    {
        return DuplicationAvoiderValue;
    }

    TSharedPtr<FSubscribeByUserIdRequest> FSubscribeByUserIdRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FSubscribeByUserIdRequest>()
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
            ->WithRoomName(Data->HasField("roomName") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("roomName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithUserId(Data->HasField("userId") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("userId", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
          ->WithNotificationTypes(Data->HasField("notificationTypes") ? [Data]() -> TSharedPtr<TArray<Model::FNotificationTypePtr>>
              {
                  auto v = MakeShared<TArray<Model::FNotificationTypePtr>>();
                  if (!Data->HasTypedField<EJson::Null>("notificationTypes") && Data->HasTypedField<EJson::Array>("notificationTypes"))
                  {
                      for (auto JsonObjectValue : Data->GetArrayField("notificationTypes"))
                      {
                          v->Add(Model::FNotificationType::FromJson(JsonObjectValue->AsObject()));
                      }
                  }
                  return v;
             }() : nullptr)
          ->WithDuplicationAvoider(Data->HasField("duplicationAvoider") ? TOptional<FString>(Data->GetStringField("duplicationAvoider")) : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FSubscribeByUserIdRequest::ToJson() const
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
        if (RoomNameValue.IsSet())
        {
            JsonRootObject->SetStringField("roomName", RoomNameValue.GetValue());
        }
        if (UserIdValue.IsSet())
        {
            JsonRootObject->SetStringField("userId", UserIdValue.GetValue());
        }
        if (NotificationTypesValue != nullptr && NotificationTypesValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *NotificationTypesValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("notificationTypes", v);
        }
        if (DuplicationAvoiderValue.IsSet())
        {
            JsonRootObject->SetStringField("duplicationAvoider", DuplicationAvoiderValue.GetValue());
        }
        return JsonRootObject;
    }
}