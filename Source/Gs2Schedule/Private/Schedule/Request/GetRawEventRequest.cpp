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

#include "Schedule/Request/GetRawEventRequest.h"

namespace Gs2::Schedule::Request
{
    FGetRawEventRequest::FGetRawEventRequest():
        NamespaceNameValue(TOptional<FString>()),
        EventNameValue(TOptional<FString>())
    {
    }

    FGetRawEventRequest::FGetRawEventRequest(
        const FGetRawEventRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        EventNameValue(From.EventNameValue)
    {
    }

    TSharedPtr<FGetRawEventRequest> FGetRawEventRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FGetRawEventRequest> FGetRawEventRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FGetRawEventRequest> FGetRawEventRequest::WithEventName(
        const TOptional<FString> EventName
    )
    {
        this->EventNameValue = EventName;
        return SharedThis(this);
    }

    TOptional<FString> FGetRawEventRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FGetRawEventRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FGetRawEventRequest::GetEventName() const
    {
        return EventNameValue;
    }

    TSharedPtr<FGetRawEventRequest> FGetRawEventRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FGetRawEventRequest>()
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
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FGetRawEventRequest::ToJson() const
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
        return JsonRootObject;
    }
}