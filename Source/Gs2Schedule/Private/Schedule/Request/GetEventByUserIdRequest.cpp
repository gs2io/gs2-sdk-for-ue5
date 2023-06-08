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

#include "Schedule/Request/GetEventByUserIdRequest.h"

namespace Gs2::Schedule::Request
{
    FGetEventByUserIdRequest::FGetEventByUserIdRequest():
        NamespaceNameValue(TOptional<FString>()),
        EventNameValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        IsInScheduleValue(TOptional<bool>())
    {
    }

    FGetEventByUserIdRequest::FGetEventByUserIdRequest(
        const FGetEventByUserIdRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        EventNameValue(From.EventNameValue),
        UserIdValue(From.UserIdValue),
        IsInScheduleValue(From.IsInScheduleValue)
    {
    }

    TSharedPtr<FGetEventByUserIdRequest> FGetEventByUserIdRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FGetEventByUserIdRequest> FGetEventByUserIdRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FGetEventByUserIdRequest> FGetEventByUserIdRequest::WithEventName(
        const TOptional<FString> EventName
    )
    {
        this->EventNameValue = EventName;
        return SharedThis(this);
    }

    TSharedPtr<FGetEventByUserIdRequest> FGetEventByUserIdRequest::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FGetEventByUserIdRequest> FGetEventByUserIdRequest::WithIsInSchedule(
        const TOptional<bool> IsInSchedule
    )
    {
        this->IsInScheduleValue = IsInSchedule;
        return SharedThis(this);
    }

    TOptional<FString> FGetEventByUserIdRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FGetEventByUserIdRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FGetEventByUserIdRequest::GetEventName() const
    {
        return EventNameValue;
    }

    TOptional<FString> FGetEventByUserIdRequest::GetUserId() const
    {
        return UserIdValue;
    }

    TOptional<bool> FGetEventByUserIdRequest::GetIsInSchedule() const
    {
        return IsInScheduleValue;
    }

    FString FGetEventByUserIdRequest::GetIsInScheduleString() const
    {
        if (!IsInScheduleValue.IsSet())
        {
            return FString("null");
        }
        return FString(IsInScheduleValue.GetValue() ? "true" : "false");
    }

    TSharedPtr<FGetEventByUserIdRequest> FGetEventByUserIdRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FGetEventByUserIdRequest>()
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
            ->WithEventName(Data->HasField("eventName") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("eventName", v))
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
            ->WithIsInSchedule(Data->HasField("isInSchedule") ? [Data]() -> TOptional<bool>
              {
                  bool v;
                    if (Data->TryGetBoolField("isInSchedule", v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<bool>();
              }() : TOptional<bool>());
    }

    TSharedPtr<FJsonObject> FGetEventByUserIdRequest::ToJson() const
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
        if (UserIdValue.IsSet())
        {
            JsonRootObject->SetStringField("userId", UserIdValue.GetValue());
        }
        if (IsInScheduleValue.IsSet())
        {
            JsonRootObject->SetBoolField("isInSchedule", IsInScheduleValue.GetValue());
        }
        return JsonRootObject;
    }
}