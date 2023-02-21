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

#include "Chat/Request/DescribeMessagesRequest.h"

namespace Gs2::Chat::Request
{
    FDescribeMessagesRequest::FDescribeMessagesRequest():
        NamespaceNameValue(TOptional<FString>()),
        RoomNameValue(TOptional<FString>()),
        PasswordValue(TOptional<FString>()),
        AccessTokenValue(TOptional<FString>()),
        StartAtValue(TOptional<int64>()),
        LimitValue(TOptional<int32>())
    {
    }

    FDescribeMessagesRequest::FDescribeMessagesRequest(
        const FDescribeMessagesRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        RoomNameValue(From.RoomNameValue),
        PasswordValue(From.PasswordValue),
        AccessTokenValue(From.AccessTokenValue),
        StartAtValue(From.StartAtValue),
        LimitValue(From.LimitValue)
    {
    }

    TSharedPtr<FDescribeMessagesRequest> FDescribeMessagesRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FDescribeMessagesRequest> FDescribeMessagesRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FDescribeMessagesRequest> FDescribeMessagesRequest::WithRoomName(
        const TOptional<FString> RoomName
    )
    {
        this->RoomNameValue = RoomName;
        return SharedThis(this);
    }

    TSharedPtr<FDescribeMessagesRequest> FDescribeMessagesRequest::WithPassword(
        const TOptional<FString> Password
    )
    {
        this->PasswordValue = Password;
        return SharedThis(this);
    }

    TSharedPtr<FDescribeMessagesRequest> FDescribeMessagesRequest::WithAccessToken(
        const TOptional<FString> AccessToken
    )
    {
        this->AccessTokenValue = AccessToken;
        return SharedThis(this);
    }

    TSharedPtr<FDescribeMessagesRequest> FDescribeMessagesRequest::WithStartAt(
        const TOptional<int64> StartAt
    )
    {
        this->StartAtValue = StartAt;
        return SharedThis(this);
    }

    TSharedPtr<FDescribeMessagesRequest> FDescribeMessagesRequest::WithLimit(
        const TOptional<int32> Limit
    )
    {
        this->LimitValue = Limit;
        return SharedThis(this);
    }

    TOptional<FString> FDescribeMessagesRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FDescribeMessagesRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FDescribeMessagesRequest::GetRoomName() const
    {
        return RoomNameValue;
    }

    TOptional<FString> FDescribeMessagesRequest::GetPassword() const
    {
        return PasswordValue;
    }

    TOptional<FString> FDescribeMessagesRequest::GetAccessToken() const
    {
        return AccessTokenValue;
    }

    TOptional<int64> FDescribeMessagesRequest::GetStartAt() const
    {
        return StartAtValue;
    }

    FString FDescribeMessagesRequest::GetStartAtString() const
    {
        if (!StartAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), StartAtValue.GetValue());
    }

    TOptional<int32> FDescribeMessagesRequest::GetLimit() const
    {
        return LimitValue;
    }

    FString FDescribeMessagesRequest::GetLimitString() const
    {
        if (!LimitValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%ld"), LimitValue.GetValue());
    }

    TSharedPtr<FDescribeMessagesRequest> FDescribeMessagesRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FDescribeMessagesRequest>()
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
            ->WithPassword(Data->HasField("password") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("password", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithAccessToken(Data->HasField("xGs2AccessToken") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("xGs2AccessToken", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithStartAt(Data->HasField("startAt") ? [Data]() -> TOptional<int64>
              {
                  int64 v;
                    if (Data->TryGetNumberField("startAt", v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int64>();
              }() : TOptional<int64>())
            ->WithLimit(Data->HasField("limit") ? [Data]() -> TOptional<int32>
              {
                  int32 v;
                    if (Data->TryGetNumberField("limit", v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int32>();
              }() : TOptional<int32>());
    }

    TSharedPtr<FJsonObject> FDescribeMessagesRequest::ToJson() const
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
        if (PasswordValue.IsSet())
        {
            JsonRootObject->SetStringField("password", PasswordValue.GetValue());
        }
        if (AccessTokenValue.IsSet())
        {
            JsonRootObject->SetStringField("xGs2AccessToken", AccessTokenValue.GetValue());
        }
        if (StartAtValue.IsSet())
        {
            JsonRootObject->SetStringField("startAt", FString::Printf(TEXT("%lld"), StartAtValue.GetValue()));
        }
        if (LimitValue.IsSet())
        {
            JsonRootObject->SetNumberField("limit", LimitValue.GetValue());
        }
        return JsonRootObject;
    }
}