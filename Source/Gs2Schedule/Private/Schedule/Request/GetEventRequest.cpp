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

#include "Schedule/Request/GetEventRequest.h"

namespace Gs2::Schedule::Request
{
    FGetEventRequest::FGetEventRequest():
        NamespaceNameValue(TOptional<FString>()),
        EventNameValue(TOptional<FString>()),
        AccessTokenValue(TOptional<FString>()),
        IsInScheduleValue(TOptional<bool>())
    {
    }

    FGetEventRequest::FGetEventRequest(
        const FGetEventRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        EventNameValue(From.EventNameValue),
        AccessTokenValue(From.AccessTokenValue),
        IsInScheduleValue(From.IsInScheduleValue)
    {
    }

    TSharedPtr<FGetEventRequest> FGetEventRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FGetEventRequest> FGetEventRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FGetEventRequest> FGetEventRequest::WithEventName(
        const TOptional<FString> EventName
    )
    {
        this->EventNameValue = EventName;
        return SharedThis(this);
    }

    TSharedPtr<FGetEventRequest> FGetEventRequest::WithAccessToken(
        const TOptional<FString> AccessToken
    )
    {
        this->AccessTokenValue = AccessToken;
        return SharedThis(this);
    }

    TSharedPtr<FGetEventRequest> FGetEventRequest::WithIsInSchedule(
        const TOptional<bool> IsInSchedule
    )
    {
        this->IsInScheduleValue = IsInSchedule;
        return SharedThis(this);
    }

    TOptional<FString> FGetEventRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FGetEventRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FGetEventRequest::GetEventName() const
    {
        return EventNameValue;
    }

    TOptional<FString> FGetEventRequest::GetAccessToken() const
    {
        return AccessTokenValue;
    }

    TOptional<bool> FGetEventRequest::GetIsInSchedule() const
    {
        return IsInScheduleValue;
    }

    FString FGetEventRequest::GetIsInScheduleString() const
    {
        if (!IsInScheduleValue.IsSet())
        {
            return FString("null");
        }
        return FString(IsInScheduleValue.GetValue() ? "true" : "false");
    }

    TSharedPtr<FGetEventRequest> FGetEventRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FGetEventRequest>()
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
            ->WithEventName(Data->HasField(ANSI_TO_TCHAR("eventName")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("eventName"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithAccessToken(Data->HasField(ANSI_TO_TCHAR("xGs2AccessToken")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("xGs2AccessToken"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithIsInSchedule(Data->HasField(ANSI_TO_TCHAR("isInSchedule")) ? [Data]() -> TOptional<bool>
              {
                  bool v;
                    if (Data->TryGetBoolField(ANSI_TO_TCHAR("isInSchedule"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<bool>();
              }() : TOptional<bool>());
    }

    TSharedPtr<FJsonObject> FGetEventRequest::ToJson() const
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
        if (EventNameValue.IsSet())
        {
            JsonRootObject->SetStringField("eventName", EventNameValue.GetValue());
        }
        if (AccessTokenValue.IsSet())
        {
            JsonRootObject->SetStringField("xGs2AccessToken", AccessTokenValue.GetValue());
        }
        if (IsInScheduleValue.IsSet())
        {
            JsonRootObject->SetBoolField("isInSchedule", IsInScheduleValue.GetValue());
        }
        return JsonRootObject;
    }
}