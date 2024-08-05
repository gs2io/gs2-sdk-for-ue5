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

#include "Log/Request/CountExecuteStampSheetLogRequest.h"

namespace Gs2::Log::Request
{
    FCountExecuteStampSheetLogRequest::FCountExecuteStampSheetLogRequest():
        NamespaceNameValue(TOptional<FString>()),
        ServiceValue(TOptional<bool>()),
        MethodValue(TOptional<bool>()),
        UserIdValue(TOptional<bool>()),
        ActionValue(TOptional<bool>()),
        BeginValue(TOptional<int64>()),
        EndValue(TOptional<int64>()),
        LongTermValue(TOptional<bool>()),
        PageTokenValue(TOptional<FString>()),
        LimitValue(TOptional<int32>()),
        TimeOffsetTokenValue(TOptional<FString>())
    {
    }

    FCountExecuteStampSheetLogRequest::FCountExecuteStampSheetLogRequest(
        const FCountExecuteStampSheetLogRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        ServiceValue(From.ServiceValue),
        MethodValue(From.MethodValue),
        UserIdValue(From.UserIdValue),
        ActionValue(From.ActionValue),
        BeginValue(From.BeginValue),
        EndValue(From.EndValue),
        LongTermValue(From.LongTermValue),
        PageTokenValue(From.PageTokenValue),
        LimitValue(From.LimitValue),
        TimeOffsetTokenValue(From.TimeOffsetTokenValue)
    {
    }

    TSharedPtr<FCountExecuteStampSheetLogRequest> FCountExecuteStampSheetLogRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FCountExecuteStampSheetLogRequest> FCountExecuteStampSheetLogRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FCountExecuteStampSheetLogRequest> FCountExecuteStampSheetLogRequest::WithService(
        const TOptional<bool> Service
    )
    {
        this->ServiceValue = Service;
        return SharedThis(this);
    }

    TSharedPtr<FCountExecuteStampSheetLogRequest> FCountExecuteStampSheetLogRequest::WithMethod(
        const TOptional<bool> Method
    )
    {
        this->MethodValue = Method;
        return SharedThis(this);
    }

    TSharedPtr<FCountExecuteStampSheetLogRequest> FCountExecuteStampSheetLogRequest::WithUserId(
        const TOptional<bool> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FCountExecuteStampSheetLogRequest> FCountExecuteStampSheetLogRequest::WithAction(
        const TOptional<bool> Action
    )
    {
        this->ActionValue = Action;
        return SharedThis(this);
    }

    TSharedPtr<FCountExecuteStampSheetLogRequest> FCountExecuteStampSheetLogRequest::WithBegin(
        const TOptional<int64> Begin
    )
    {
        this->BeginValue = Begin;
        return SharedThis(this);
    }

    TSharedPtr<FCountExecuteStampSheetLogRequest> FCountExecuteStampSheetLogRequest::WithEnd(
        const TOptional<int64> End
    )
    {
        this->EndValue = End;
        return SharedThis(this);
    }

    TSharedPtr<FCountExecuteStampSheetLogRequest> FCountExecuteStampSheetLogRequest::WithLongTerm(
        const TOptional<bool> LongTerm
    )
    {
        this->LongTermValue = LongTerm;
        return SharedThis(this);
    }

    TSharedPtr<FCountExecuteStampSheetLogRequest> FCountExecuteStampSheetLogRequest::WithPageToken(
        const TOptional<FString> PageToken
    )
    {
        this->PageTokenValue = PageToken;
        return SharedThis(this);
    }

    TSharedPtr<FCountExecuteStampSheetLogRequest> FCountExecuteStampSheetLogRequest::WithLimit(
        const TOptional<int32> Limit
    )
    {
        this->LimitValue = Limit;
        return SharedThis(this);
    }

    TSharedPtr<FCountExecuteStampSheetLogRequest> FCountExecuteStampSheetLogRequest::WithTimeOffsetToken(
        const TOptional<FString> TimeOffsetToken
    )
    {
        this->TimeOffsetTokenValue = TimeOffsetToken;
        return SharedThis(this);
    }

    TOptional<FString> FCountExecuteStampSheetLogRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FCountExecuteStampSheetLogRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<bool> FCountExecuteStampSheetLogRequest::GetService() const
    {
        return ServiceValue;
    }

    FString FCountExecuteStampSheetLogRequest::GetServiceString() const
    {
        if (!ServiceValue.IsSet())
        {
            return FString("null");
        }
        return FString(ServiceValue.GetValue() ? "true" : "false");
    }

    TOptional<bool> FCountExecuteStampSheetLogRequest::GetMethod() const
    {
        return MethodValue;
    }

    FString FCountExecuteStampSheetLogRequest::GetMethodString() const
    {
        if (!MethodValue.IsSet())
        {
            return FString("null");
        }
        return FString(MethodValue.GetValue() ? "true" : "false");
    }

    TOptional<bool> FCountExecuteStampSheetLogRequest::GetUserId() const
    {
        return UserIdValue;
    }

    FString FCountExecuteStampSheetLogRequest::GetUserIdString() const
    {
        if (!UserIdValue.IsSet())
        {
            return FString("null");
        }
        return FString(UserIdValue.GetValue() ? "true" : "false");
    }

    TOptional<bool> FCountExecuteStampSheetLogRequest::GetAction() const
    {
        return ActionValue;
    }

    FString FCountExecuteStampSheetLogRequest::GetActionString() const
    {
        if (!ActionValue.IsSet())
        {
            return FString("null");
        }
        return FString(ActionValue.GetValue() ? "true" : "false");
    }

    TOptional<int64> FCountExecuteStampSheetLogRequest::GetBegin() const
    {
        return BeginValue;
    }

    FString FCountExecuteStampSheetLogRequest::GetBeginString() const
    {
        if (!BeginValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), BeginValue.GetValue());
    }

    TOptional<int64> FCountExecuteStampSheetLogRequest::GetEnd() const
    {
        return EndValue;
    }

    FString FCountExecuteStampSheetLogRequest::GetEndString() const
    {
        if (!EndValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), EndValue.GetValue());
    }

    TOptional<bool> FCountExecuteStampSheetLogRequest::GetLongTerm() const
    {
        return LongTermValue;
    }

    FString FCountExecuteStampSheetLogRequest::GetLongTermString() const
    {
        if (!LongTermValue.IsSet())
        {
            return FString("null");
        }
        return FString(LongTermValue.GetValue() ? "true" : "false");
    }

    TOptional<FString> FCountExecuteStampSheetLogRequest::GetPageToken() const
    {
        return PageTokenValue;
    }

    TOptional<int32> FCountExecuteStampSheetLogRequest::GetLimit() const
    {
        return LimitValue;
    }

    FString FCountExecuteStampSheetLogRequest::GetLimitString() const
    {
        if (!LimitValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), LimitValue.GetValue());
    }

    TOptional<FString> FCountExecuteStampSheetLogRequest::GetTimeOffsetToken() const
    {
        return TimeOffsetTokenValue;
    }

    TSharedPtr<FCountExecuteStampSheetLogRequest> FCountExecuteStampSheetLogRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FCountExecuteStampSheetLogRequest>()
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
            ->WithService(Data->HasField(ANSI_TO_TCHAR("service")) ? [Data]() -> TOptional<bool>
              {
                  bool v;
                    if (Data->TryGetBoolField(ANSI_TO_TCHAR("service"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<bool>();
              }() : TOptional<bool>())
            ->WithMethod(Data->HasField(ANSI_TO_TCHAR("method")) ? [Data]() -> TOptional<bool>
              {
                  bool v;
                    if (Data->TryGetBoolField(ANSI_TO_TCHAR("method"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<bool>();
              }() : TOptional<bool>())
            ->WithUserId(Data->HasField(ANSI_TO_TCHAR("userId")) ? [Data]() -> TOptional<bool>
              {
                  bool v;
                    if (Data->TryGetBoolField(ANSI_TO_TCHAR("userId"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<bool>();
              }() : TOptional<bool>())
            ->WithAction(Data->HasField(ANSI_TO_TCHAR("action")) ? [Data]() -> TOptional<bool>
              {
                  bool v;
                    if (Data->TryGetBoolField(ANSI_TO_TCHAR("action"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<bool>();
              }() : TOptional<bool>())
            ->WithBegin(Data->HasField(ANSI_TO_TCHAR("begin")) ? [Data]() -> TOptional<int64>
              {
                  int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("begin"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int64>();
              }() : TOptional<int64>())
            ->WithEnd(Data->HasField(ANSI_TO_TCHAR("end")) ? [Data]() -> TOptional<int64>
              {
                  int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("end"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int64>();
              }() : TOptional<int64>())
            ->WithLongTerm(Data->HasField(ANSI_TO_TCHAR("longTerm")) ? [Data]() -> TOptional<bool>
              {
                  bool v;
                    if (Data->TryGetBoolField(ANSI_TO_TCHAR("longTerm"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<bool>();
              }() : TOptional<bool>())
            ->WithPageToken(Data->HasField(ANSI_TO_TCHAR("pageToken")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("pageToken"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
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

    TSharedPtr<FJsonObject> FCountExecuteStampSheetLogRequest::ToJson() const
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
        if (ServiceValue.IsSet())
        {
            JsonRootObject->SetBoolField("service", ServiceValue.GetValue());
        }
        if (MethodValue.IsSet())
        {
            JsonRootObject->SetBoolField("method", MethodValue.GetValue());
        }
        if (UserIdValue.IsSet())
        {
            JsonRootObject->SetBoolField("userId", UserIdValue.GetValue());
        }
        if (ActionValue.IsSet())
        {
            JsonRootObject->SetBoolField("action", ActionValue.GetValue());
        }
        if (BeginValue.IsSet())
        {
            JsonRootObject->SetStringField("begin", FString::Printf(TEXT("%lld"), BeginValue.GetValue()));
        }
        if (EndValue.IsSet())
        {
            JsonRootObject->SetStringField("end", FString::Printf(TEXT("%lld"), EndValue.GetValue()));
        }
        if (LongTermValue.IsSet())
        {
            JsonRootObject->SetBoolField("longTerm", LongTermValue.GetValue());
        }
        if (PageTokenValue.IsSet())
        {
            JsonRootObject->SetStringField("pageToken", PageTokenValue.GetValue());
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