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

#include "Chat/Request/DescribeMessagesByUserIdRequest.h"

namespace Gs2::Chat::Request
{
    FDescribeMessagesByUserIdRequest::FDescribeMessagesByUserIdRequest():
        NamespaceNameValue(TOptional<FString>()),
        RoomNameValue(TOptional<FString>()),
        PasswordValue(TOptional<FString>()),
        CategoryValue(TOptional<int32>()),
        UserIdValue(TOptional<FString>()),
        StartAtValue(TOptional<int64>()),
        LimitValue(TOptional<int32>()),
        TimeOffsetTokenValue(TOptional<FString>())
    {
    }

    FDescribeMessagesByUserIdRequest::FDescribeMessagesByUserIdRequest(
        const FDescribeMessagesByUserIdRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        RoomNameValue(From.RoomNameValue),
        PasswordValue(From.PasswordValue),
        CategoryValue(From.CategoryValue),
        UserIdValue(From.UserIdValue),
        StartAtValue(From.StartAtValue),
        LimitValue(From.LimitValue),
        TimeOffsetTokenValue(From.TimeOffsetTokenValue)
    {
    }

    TSharedPtr<FDescribeMessagesByUserIdRequest> FDescribeMessagesByUserIdRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FDescribeMessagesByUserIdRequest> FDescribeMessagesByUserIdRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FDescribeMessagesByUserIdRequest> FDescribeMessagesByUserIdRequest::WithRoomName(
        const TOptional<FString> RoomName
    )
    {
        this->RoomNameValue = RoomName;
        return SharedThis(this);
    }

    TSharedPtr<FDescribeMessagesByUserIdRequest> FDescribeMessagesByUserIdRequest::WithPassword(
        const TOptional<FString> Password
    )
    {
        this->PasswordValue = Password;
        return SharedThis(this);
    }

    TSharedPtr<FDescribeMessagesByUserIdRequest> FDescribeMessagesByUserIdRequest::WithCategory(
        const TOptional<int32> Category
    )
    {
        this->CategoryValue = Category;
        return SharedThis(this);
    }

    TSharedPtr<FDescribeMessagesByUserIdRequest> FDescribeMessagesByUserIdRequest::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FDescribeMessagesByUserIdRequest> FDescribeMessagesByUserIdRequest::WithStartAt(
        const TOptional<int64> StartAt
    )
    {
        this->StartAtValue = StartAt;
        return SharedThis(this);
    }

    TSharedPtr<FDescribeMessagesByUserIdRequest> FDescribeMessagesByUserIdRequest::WithLimit(
        const TOptional<int32> Limit
    )
    {
        this->LimitValue = Limit;
        return SharedThis(this);
    }

    TSharedPtr<FDescribeMessagesByUserIdRequest> FDescribeMessagesByUserIdRequest::WithTimeOffsetToken(
        const TOptional<FString> TimeOffsetToken
    )
    {
        this->TimeOffsetTokenValue = TimeOffsetToken;
        return SharedThis(this);
    }

    TOptional<FString> FDescribeMessagesByUserIdRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FDescribeMessagesByUserIdRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FDescribeMessagesByUserIdRequest::GetRoomName() const
    {
        return RoomNameValue;
    }

    TOptional<FString> FDescribeMessagesByUserIdRequest::GetPassword() const
    {
        return PasswordValue;
    }

    TOptional<int32> FDescribeMessagesByUserIdRequest::GetCategory() const
    {
        return CategoryValue;
    }

    FString FDescribeMessagesByUserIdRequest::GetCategoryString() const
    {
        if (!CategoryValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), CategoryValue.GetValue());
    }

    TOptional<FString> FDescribeMessagesByUserIdRequest::GetUserId() const
    {
        return UserIdValue;
    }

    TOptional<int64> FDescribeMessagesByUserIdRequest::GetStartAt() const
    {
        return StartAtValue;
    }

    FString FDescribeMessagesByUserIdRequest::GetStartAtString() const
    {
        if (!StartAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), StartAtValue.GetValue());
    }

    TOptional<int32> FDescribeMessagesByUserIdRequest::GetLimit() const
    {
        return LimitValue;
    }

    FString FDescribeMessagesByUserIdRequest::GetLimitString() const
    {
        if (!LimitValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), LimitValue.GetValue());
    }

    TOptional<FString> FDescribeMessagesByUserIdRequest::GetTimeOffsetToken() const
    {
        return TimeOffsetTokenValue;
    }

    TSharedPtr<FDescribeMessagesByUserIdRequest> FDescribeMessagesByUserIdRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FDescribeMessagesByUserIdRequest>()
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
            ->WithRoomName(Data->HasField(ANSI_TO_TCHAR("roomName")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("roomName"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithPassword(Data->HasField(ANSI_TO_TCHAR("password")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("password"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithCategory(Data->HasField(ANSI_TO_TCHAR("category")) ? [Data]() -> TOptional<int32>
              {
                  int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("category"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int32>();
              }() : TOptional<int32>())
            ->WithUserId(Data->HasField(ANSI_TO_TCHAR("userId")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("userId"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithStartAt(Data->HasField(ANSI_TO_TCHAR("startAt")) ? [Data]() -> TOptional<int64>
              {
                  int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("startAt"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int64>();
              }() : TOptional<int64>())
            ->WithLimit(Data->HasField(ANSI_TO_TCHAR("limit")) ? [Data]() -> TOptional<int32>
              {
                  int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("limit"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int32>();
              }() : TOptional<int32>())
            ->WithTimeOffsetToken(Data->HasField(ANSI_TO_TCHAR("timeOffsetToken")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("timeOffsetToken"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FDescribeMessagesByUserIdRequest::ToJson() const
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
        if (CategoryValue.IsSet())
        {
            JsonRootObject->SetNumberField("category", CategoryValue.GetValue());
        }
        if (UserIdValue.IsSet())
        {
            JsonRootObject->SetStringField("userId", UserIdValue.GetValue());
        }
        if (StartAtValue.IsSet())
        {
            JsonRootObject->SetStringField("startAt", FString::Printf(TEXT("%lld"), StartAtValue.GetValue()));
        }
        if (LimitValue.IsSet())
        {
            JsonRootObject->SetNumberField("limit", LimitValue.GetValue());
        }
        if (TimeOffsetTokenValue.IsSet())
        {
            JsonRootObject->SetStringField("timeOffsetToken", TimeOffsetTokenValue.GetValue());
        }
        return JsonRootObject;
    }
}