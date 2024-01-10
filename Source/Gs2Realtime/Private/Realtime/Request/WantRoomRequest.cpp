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

#include "Realtime/Request/WantRoomRequest.h"

namespace Gs2::Realtime::Request
{
    FWantRoomRequest::FWantRoomRequest():
        NamespaceNameValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
        NotificationUserIdsValue(nullptr)
    {
    }

    FWantRoomRequest::FWantRoomRequest(
        const FWantRoomRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        NameValue(From.NameValue),
        NotificationUserIdsValue(From.NotificationUserIdsValue)
    {
    }

    TSharedPtr<FWantRoomRequest> FWantRoomRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FWantRoomRequest> FWantRoomRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FWantRoomRequest> FWantRoomRequest::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FWantRoomRequest> FWantRoomRequest::WithNotificationUserIds(
        const TSharedPtr<TArray<FString>> NotificationUserIds
    )
    {
        this->NotificationUserIdsValue = NotificationUserIds;
        return SharedThis(this);
    }

    TOptional<FString> FWantRoomRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FWantRoomRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FWantRoomRequest::GetName() const
    {
        return NameValue;
    }

    TSharedPtr<TArray<FString>> FWantRoomRequest::GetNotificationUserIds() const
    {
        if (!NotificationUserIdsValue.IsValid())
        {
            return nullptr;
        }
        return NotificationUserIdsValue;
    }

    TSharedPtr<FWantRoomRequest> FWantRoomRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FWantRoomRequest>()
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
            ->WithName(Data->HasField("name") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("name", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
          ->WithNotificationUserIds(Data->HasField("notificationUserIds") ? [Data]() -> TSharedPtr<TArray<FString>>
              {
                  auto v = MakeShared<TArray<FString>>();
                  if (!Data->HasTypedField<EJson::Null>("notificationUserIds") && Data->HasTypedField<EJson::Array>("notificationUserIds"))
                  {
                      for (auto JsonObjectValue : Data->GetArrayField("notificationUserIds"))
                      {
                          v->Add(JsonObjectValue->AsString());
                      }
                  }
                  return v;
              }() : MakeShared<TArray<FString>>());
    }

    TSharedPtr<FJsonObject> FWantRoomRequest::ToJson() const
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
        if (NameValue.IsSet())
        {
            JsonRootObject->SetStringField("name", NameValue.GetValue());
        }
        if (NotificationUserIdsValue != nullptr && NotificationUserIdsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *NotificationUserIdsValue)
            {
                v.Add(MakeShared<FJsonValueString>(JsonObjectValue));
            }
            JsonRootObject->SetArrayField("notificationUserIds", v);
        }
        return JsonRootObject;
    }
}