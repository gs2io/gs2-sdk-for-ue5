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

#include "Deploy/Request/GetEventRequest.h"

namespace Gs2::Deploy::Request
{
    FGetEventRequest::FGetEventRequest():
        StackNameValue(TOptional<FString>()),
        EventNameValue(TOptional<FString>())
    {
    }

    FGetEventRequest::FGetEventRequest(
        const FGetEventRequest& From
    ):
        StackNameValue(From.StackNameValue),
        EventNameValue(From.EventNameValue)
    {
    }

    TSharedPtr<FGetEventRequest> FGetEventRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FGetEventRequest> FGetEventRequest::WithStackName(
        const TOptional<FString> StackName
    )
    {
        this->StackNameValue = StackName;
        return SharedThis(this);
    }

    TSharedPtr<FGetEventRequest> FGetEventRequest::WithEventName(
        const TOptional<FString> EventName
    )
    {
        this->EventNameValue = EventName;
        return SharedThis(this);
    }

    TOptional<FString> FGetEventRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FGetEventRequest::GetStackName() const
    {
        return StackNameValue;
    }

    TOptional<FString> FGetEventRequest::GetEventName() const
    {
        return EventNameValue;
    }

    TSharedPtr<FGetEventRequest> FGetEventRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FGetEventRequest>()
            ->WithContextStack(Data->HasField("contextStack") ? TOptional<FString>(Data->GetStringField("contextStack")) : TOptional<FString>())
            ->WithStackName(Data->HasField("stackName") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("stackName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithEventName(Data->HasField("eventName") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("eventName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FGetEventRequest::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ContextStackValue.IsSet())
        {
            JsonRootObject->SetStringField("contextStack", ContextStackValue.GetValue());
        }
        if (StackNameValue.IsSet())
        {
            JsonRootObject->SetStringField("stackName", StackNameValue.GetValue());
        }
        if (EventNameValue.IsSet())
        {
            JsonRootObject->SetStringField("eventName", EventNameValue.GetValue());
        }
        return JsonRootObject;
    }
}