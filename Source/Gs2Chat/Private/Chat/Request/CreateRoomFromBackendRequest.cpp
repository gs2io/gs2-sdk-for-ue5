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

#include "Chat/Request/CreateRoomFromBackendRequest.h"

namespace Gs2::Chat::Request
{
    FCreateRoomFromBackendRequest::FCreateRoomFromBackendRequest():
        NamespaceNameValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        PasswordValue(TOptional<FString>()),
        WhiteListUserIdsValue(nullptr)
    {
    }

    FCreateRoomFromBackendRequest::FCreateRoomFromBackendRequest(
        const FCreateRoomFromBackendRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        NameValue(From.NameValue),
        UserIdValue(From.UserIdValue),
        MetadataValue(From.MetadataValue),
        PasswordValue(From.PasswordValue),
        WhiteListUserIdsValue(From.WhiteListUserIdsValue)
    {
    }

    TSharedPtr<FCreateRoomFromBackendRequest> FCreateRoomFromBackendRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FCreateRoomFromBackendRequest> FCreateRoomFromBackendRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FCreateRoomFromBackendRequest> FCreateRoomFromBackendRequest::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FCreateRoomFromBackendRequest> FCreateRoomFromBackendRequest::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FCreateRoomFromBackendRequest> FCreateRoomFromBackendRequest::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FCreateRoomFromBackendRequest> FCreateRoomFromBackendRequest::WithPassword(
        const TOptional<FString> Password
    )
    {
        this->PasswordValue = Password;
        return SharedThis(this);
    }

    TSharedPtr<FCreateRoomFromBackendRequest> FCreateRoomFromBackendRequest::WithWhiteListUserIds(
        const TSharedPtr<TArray<FString>> WhiteListUserIds
    )
    {
        this->WhiteListUserIdsValue = WhiteListUserIds;
        return SharedThis(this);
    }

    TSharedPtr<FCreateRoomFromBackendRequest> FCreateRoomFromBackendRequest::WithDuplicationAvoider(
        const TOptional<FString> DuplicationAvoider
    )
    {
        this->DuplicationAvoiderValue = DuplicationAvoider;
        return SharedThis(this);
    }

    TOptional<FString> FCreateRoomFromBackendRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FCreateRoomFromBackendRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FCreateRoomFromBackendRequest::GetName() const
    {
        return NameValue;
    }

    TOptional<FString> FCreateRoomFromBackendRequest::GetUserId() const
    {
        return UserIdValue;
    }

    TOptional<FString> FCreateRoomFromBackendRequest::GetMetadata() const
    {
        return MetadataValue;
    }

    TOptional<FString> FCreateRoomFromBackendRequest::GetPassword() const
    {
        return PasswordValue;
    }

    TSharedPtr<TArray<FString>> FCreateRoomFromBackendRequest::GetWhiteListUserIds() const
    {
        if (!WhiteListUserIdsValue.IsValid())
        {
            return nullptr;
        }
        return WhiteListUserIdsValue;
    }

    TOptional<FString> FCreateRoomFromBackendRequest::GetDuplicationAvoider() const
    {
        return DuplicationAvoiderValue;
    }

    TSharedPtr<FCreateRoomFromBackendRequest> FCreateRoomFromBackendRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FCreateRoomFromBackendRequest>()
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
            ->WithUserId(Data->HasField("userId") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("userId", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithMetadata(Data->HasField("metadata") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("metadata", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithPassword(Data->HasField("password") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("password", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
          ->WithWhiteListUserIds(Data->HasField("whiteListUserIds") ? [Data]() -> TSharedPtr<TArray<FString>>
              {
                  auto v = MakeShared<TArray<FString>>();
                  if (!Data->HasTypedField<EJson::Null>("whiteListUserIds") && Data->HasTypedField<EJson::Array>("whiteListUserIds"))
                  {
                      for (auto JsonObjectValue : Data->GetArrayField("whiteListUserIds"))
                      {
                          v->Add(JsonObjectValue->AsString());
                      }
                  }
                  return v;
              }() : MakeShared<TArray<FString>>())
          ->WithDuplicationAvoider(Data->HasField("duplicationAvoider") ? TOptional<FString>(Data->GetStringField("duplicationAvoider")) : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FCreateRoomFromBackendRequest::ToJson() const
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
        if (UserIdValue.IsSet())
        {
            JsonRootObject->SetStringField("userId", UserIdValue.GetValue());
        }
        if (MetadataValue.IsSet())
        {
            JsonRootObject->SetStringField("metadata", MetadataValue.GetValue());
        }
        if (PasswordValue.IsSet())
        {
            JsonRootObject->SetStringField("password", PasswordValue.GetValue());
        }
        if (WhiteListUserIdsValue != nullptr && WhiteListUserIdsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *WhiteListUserIdsValue)
            {
                v.Add(MakeShared<FJsonValueString>(JsonObjectValue));
            }
            JsonRootObject->SetArrayField("whiteListUserIds", v);
        }
        if (DuplicationAvoiderValue.IsSet())
        {
            JsonRootObject->SetStringField("duplicationAvoider", DuplicationAvoiderValue.GetValue());
        }
        return JsonRootObject;
    }
}