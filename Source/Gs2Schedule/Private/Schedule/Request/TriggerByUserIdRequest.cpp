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

#include "Schedule/Request/TriggerByUserIdRequest.h"

namespace Gs2::Schedule::Request
{
    FTriggerByUserIdRequest::FTriggerByUserIdRequest():
        NamespaceNameValue(TOptional<FString>()),
        TriggerNameValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        TriggerStrategyValue(TOptional<FString>()),
        TtlValue(TOptional<int32>()),
        EventIdValue(TOptional<FString>()),
        TimeOffsetTokenValue(TOptional<FString>())
    {
    }

    FTriggerByUserIdRequest::FTriggerByUserIdRequest(
        const FTriggerByUserIdRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        TriggerNameValue(From.TriggerNameValue),
        UserIdValue(From.UserIdValue),
        TriggerStrategyValue(From.TriggerStrategyValue),
        TtlValue(From.TtlValue),
        EventIdValue(From.EventIdValue),
        TimeOffsetTokenValue(From.TimeOffsetTokenValue)
    {
    }

    TSharedPtr<FTriggerByUserIdRequest> FTriggerByUserIdRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FTriggerByUserIdRequest> FTriggerByUserIdRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FTriggerByUserIdRequest> FTriggerByUserIdRequest::WithTriggerName(
        const TOptional<FString> TriggerName
    )
    {
        this->TriggerNameValue = TriggerName;
        return SharedThis(this);
    }

    TSharedPtr<FTriggerByUserIdRequest> FTriggerByUserIdRequest::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FTriggerByUserIdRequest> FTriggerByUserIdRequest::WithTriggerStrategy(
        const TOptional<FString> TriggerStrategy
    )
    {
        this->TriggerStrategyValue = TriggerStrategy;
        return SharedThis(this);
    }

    TSharedPtr<FTriggerByUserIdRequest> FTriggerByUserIdRequest::WithTtl(
        const TOptional<int32> Ttl
    )
    {
        this->TtlValue = Ttl;
        return SharedThis(this);
    }

    TSharedPtr<FTriggerByUserIdRequest> FTriggerByUserIdRequest::WithEventId(
        const TOptional<FString> EventId
    )
    {
        this->EventIdValue = EventId;
        return SharedThis(this);
    }

    TSharedPtr<FTriggerByUserIdRequest> FTriggerByUserIdRequest::WithTimeOffsetToken(
        const TOptional<FString> TimeOffsetToken
    )
    {
        this->TimeOffsetTokenValue = TimeOffsetToken;
        return SharedThis(this);
    }

    TSharedPtr<FTriggerByUserIdRequest> FTriggerByUserIdRequest::WithDuplicationAvoider(
        const TOptional<FString> DuplicationAvoider
    )
    {
        this->DuplicationAvoiderValue = DuplicationAvoider;
        return SharedThis(this);
    }

    TOptional<FString> FTriggerByUserIdRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FTriggerByUserIdRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FTriggerByUserIdRequest::GetTriggerName() const
    {
        return TriggerNameValue;
    }

    TOptional<FString> FTriggerByUserIdRequest::GetUserId() const
    {
        return UserIdValue;
    }

    TOptional<FString> FTriggerByUserIdRequest::GetTriggerStrategy() const
    {
        return TriggerStrategyValue;
    }

    TOptional<int32> FTriggerByUserIdRequest::GetTtl() const
    {
        return TtlValue;
    }

    FString FTriggerByUserIdRequest::GetTtlString() const
    {
        if (!TtlValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), TtlValue.GetValue());
    }

    TOptional<FString> FTriggerByUserIdRequest::GetEventId() const
    {
        return EventIdValue;
    }

    TOptional<FString> FTriggerByUserIdRequest::GetTimeOffsetToken() const
    {
        return TimeOffsetTokenValue;
    }

    TOptional<FString> FTriggerByUserIdRequest::GetDuplicationAvoider() const
    {
        return DuplicationAvoiderValue;
    }

    TSharedPtr<FTriggerByUserIdRequest> FTriggerByUserIdRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FTriggerByUserIdRequest>()
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
            ->WithTriggerName(Data->HasField(ANSI_TO_TCHAR("triggerName")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("triggerName"), v))
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
            ->WithTriggerStrategy(Data->HasField(ANSI_TO_TCHAR("triggerStrategy")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("triggerStrategy"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithTtl(Data->HasField(ANSI_TO_TCHAR("ttl")) ? [Data]() -> TOptional<int32>
              {
                  int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("ttl"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int32>();
              }() : TOptional<int32>())
            ->WithEventId(Data->HasField(ANSI_TO_TCHAR("eventId")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("eventId"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
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

    TSharedPtr<FJsonObject> FTriggerByUserIdRequest::ToJson() const
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
        if (TriggerNameValue.IsSet())
        {
            JsonRootObject->SetStringField("triggerName", TriggerNameValue.GetValue());
        }
        if (UserIdValue.IsSet())
        {
            JsonRootObject->SetStringField("userId", UserIdValue.GetValue());
        }
        if (TriggerStrategyValue.IsSet())
        {
            JsonRootObject->SetStringField("triggerStrategy", TriggerStrategyValue.GetValue());
        }
        if (TtlValue.IsSet())
        {
            JsonRootObject->SetNumberField("ttl", TtlValue.GetValue());
        }
        if (EventIdValue.IsSet())
        {
            JsonRootObject->SetStringField("eventId", EventIdValue.GetValue());
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