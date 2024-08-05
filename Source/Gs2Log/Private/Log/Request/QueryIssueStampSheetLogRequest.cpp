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

#include "Log/Request/QueryIssueStampSheetLogRequest.h"

namespace Gs2::Log::Request
{
    FQueryIssueStampSheetLogRequest::FQueryIssueStampSheetLogRequest():
        NamespaceNameValue(TOptional<FString>()),
        ServiceValue(TOptional<FString>()),
        MethodValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        ActionValue(TOptional<FString>()),
        BeginValue(TOptional<int64>()),
        EndValue(TOptional<int64>()),
        LongTermValue(TOptional<bool>()),
        PageTokenValue(TOptional<FString>()),
        LimitValue(TOptional<int32>()),
        TimeOffsetTokenValue(TOptional<FString>())
    {
    }

    FQueryIssueStampSheetLogRequest::FQueryIssueStampSheetLogRequest(
        const FQueryIssueStampSheetLogRequest& From
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

    TSharedPtr<FQueryIssueStampSheetLogRequest> FQueryIssueStampSheetLogRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FQueryIssueStampSheetLogRequest> FQueryIssueStampSheetLogRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FQueryIssueStampSheetLogRequest> FQueryIssueStampSheetLogRequest::WithService(
        const TOptional<FString> Service
    )
    {
        this->ServiceValue = Service;
        return SharedThis(this);
    }

    TSharedPtr<FQueryIssueStampSheetLogRequest> FQueryIssueStampSheetLogRequest::WithMethod(
        const TOptional<FString> Method
    )
    {
        this->MethodValue = Method;
        return SharedThis(this);
    }

    TSharedPtr<FQueryIssueStampSheetLogRequest> FQueryIssueStampSheetLogRequest::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FQueryIssueStampSheetLogRequest> FQueryIssueStampSheetLogRequest::WithAction(
        const TOptional<FString> Action
    )
    {
        this->ActionValue = Action;
        return SharedThis(this);
    }

    TSharedPtr<FQueryIssueStampSheetLogRequest> FQueryIssueStampSheetLogRequest::WithBegin(
        const TOptional<int64> Begin
    )
    {
        this->BeginValue = Begin;
        return SharedThis(this);
    }

    TSharedPtr<FQueryIssueStampSheetLogRequest> FQueryIssueStampSheetLogRequest::WithEnd(
        const TOptional<int64> End
    )
    {
        this->EndValue = End;
        return SharedThis(this);
    }

    TSharedPtr<FQueryIssueStampSheetLogRequest> FQueryIssueStampSheetLogRequest::WithLongTerm(
        const TOptional<bool> LongTerm
    )
    {
        this->LongTermValue = LongTerm;
        return SharedThis(this);
    }

    TSharedPtr<FQueryIssueStampSheetLogRequest> FQueryIssueStampSheetLogRequest::WithPageToken(
        const TOptional<FString> PageToken
    )
    {
        this->PageTokenValue = PageToken;
        return SharedThis(this);
    }

    TSharedPtr<FQueryIssueStampSheetLogRequest> FQueryIssueStampSheetLogRequest::WithLimit(
        const TOptional<int32> Limit
    )
    {
        this->LimitValue = Limit;
        return SharedThis(this);
    }

    TSharedPtr<FQueryIssueStampSheetLogRequest> FQueryIssueStampSheetLogRequest::WithTimeOffsetToken(
        const TOptional<FString> TimeOffsetToken
    )
    {
        this->TimeOffsetTokenValue = TimeOffsetToken;
        return SharedThis(this);
    }

    TSharedPtr<FQueryIssueStampSheetLogRequest> FQueryIssueStampSheetLogRequest::WithDuplicationAvoider(
        const TOptional<FString> DuplicationAvoider
    )
    {
        this->DuplicationAvoiderValue = DuplicationAvoider;
        return SharedThis(this);
    }

    TOptional<FString> FQueryIssueStampSheetLogRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FQueryIssueStampSheetLogRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FQueryIssueStampSheetLogRequest::GetService() const
    {
        return ServiceValue;
    }

    TOptional<FString> FQueryIssueStampSheetLogRequest::GetMethod() const
    {
        return MethodValue;
    }

    TOptional<FString> FQueryIssueStampSheetLogRequest::GetUserId() const
    {
        return UserIdValue;
    }

    TOptional<FString> FQueryIssueStampSheetLogRequest::GetAction() const
    {
        return ActionValue;
    }

    TOptional<int64> FQueryIssueStampSheetLogRequest::GetBegin() const
    {
        return BeginValue;
    }

    FString FQueryIssueStampSheetLogRequest::GetBeginString() const
    {
        if (!BeginValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), BeginValue.GetValue());
    }

    TOptional<int64> FQueryIssueStampSheetLogRequest::GetEnd() const
    {
        return EndValue;
    }

    FString FQueryIssueStampSheetLogRequest::GetEndString() const
    {
        if (!EndValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), EndValue.GetValue());
    }

    TOptional<bool> FQueryIssueStampSheetLogRequest::GetLongTerm() const
    {
        return LongTermValue;
    }

    FString FQueryIssueStampSheetLogRequest::GetLongTermString() const
    {
        if (!LongTermValue.IsSet())
        {
            return FString("null");
        }
        return FString(LongTermValue.GetValue() ? "true" : "false");
    }

    TOptional<FString> FQueryIssueStampSheetLogRequest::GetPageToken() const
    {
        return PageTokenValue;
    }

    TOptional<int32> FQueryIssueStampSheetLogRequest::GetLimit() const
    {
        return LimitValue;
    }

    FString FQueryIssueStampSheetLogRequest::GetLimitString() const
    {
        if (!LimitValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), LimitValue.GetValue());
    }

    TOptional<FString> FQueryIssueStampSheetLogRequest::GetTimeOffsetToken() const
    {
        return TimeOffsetTokenValue;
    }

    TOptional<FString> FQueryIssueStampSheetLogRequest::GetDuplicationAvoider() const
    {
        return DuplicationAvoiderValue;
    }

    TSharedPtr<FQueryIssueStampSheetLogRequest> FQueryIssueStampSheetLogRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FQueryIssueStampSheetLogRequest>()
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
            ->WithService(Data->HasField(ANSI_TO_TCHAR("service")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("service"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithMethod(Data->HasField(ANSI_TO_TCHAR("method")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("method"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithUserId(Data->HasField(ANSI_TO_TCHAR("userId")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("userId"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithAction(Data->HasField(ANSI_TO_TCHAR("action")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("action"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
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
              }() : TOptional<FString>())
          ->WithDuplicationAvoider(Data->HasField(ANSI_TO_TCHAR("duplicationAvoider")) ? TOptional<FString>(Data->GetStringField(ANSI_TO_TCHAR("duplicationAvoider"))) : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FQueryIssueStampSheetLogRequest::ToJson() const
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
            JsonRootObject->SetStringField("service", ServiceValue.GetValue());
        }
        if (MethodValue.IsSet())
        {
            JsonRootObject->SetStringField("method", MethodValue.GetValue());
        }
        if (UserIdValue.IsSet())
        {
            JsonRootObject->SetStringField("userId", UserIdValue.GetValue());
        }
        if (ActionValue.IsSet())
        {
            JsonRootObject->SetStringField("action", ActionValue.GetValue());
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
        if (DuplicationAvoiderValue.IsSet())
        {
            JsonRootObject->SetStringField("duplicationAvoider", DuplicationAvoiderValue.GetValue());
        }
        return JsonRootObject;
    }
}