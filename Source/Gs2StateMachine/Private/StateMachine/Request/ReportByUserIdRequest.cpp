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

#include "StateMachine/Request/ReportByUserIdRequest.h"

namespace Gs2::StateMachine::Request
{
    FReportByUserIdRequest::FReportByUserIdRequest():
        NamespaceNameValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        StatusNameValue(TOptional<FString>()),
        EventsValue(nullptr)
    {
    }

    FReportByUserIdRequest::FReportByUserIdRequest(
        const FReportByUserIdRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        UserIdValue(From.UserIdValue),
        StatusNameValue(From.StatusNameValue),
        EventsValue(From.EventsValue)
    {
    }

    TSharedPtr<FReportByUserIdRequest> FReportByUserIdRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FReportByUserIdRequest> FReportByUserIdRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FReportByUserIdRequest> FReportByUserIdRequest::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FReportByUserIdRequest> FReportByUserIdRequest::WithStatusName(
        const TOptional<FString> StatusName
    )
    {
        this->StatusNameValue = StatusName;
        return SharedThis(this);
    }

    TSharedPtr<FReportByUserIdRequest> FReportByUserIdRequest::WithEvents(
        const TSharedPtr<TArray<TSharedPtr<Model::FEvent>>> Events
    )
    {
        this->EventsValue = Events;
        return SharedThis(this);
    }

    TSharedPtr<FReportByUserIdRequest> FReportByUserIdRequest::WithDuplicationAvoider(
        const TOptional<FString> DuplicationAvoider
    )
    {
        this->DuplicationAvoiderValue = DuplicationAvoider;
        return SharedThis(this);
    }

    TOptional<FString> FReportByUserIdRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FReportByUserIdRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FReportByUserIdRequest::GetUserId() const
    {
        return UserIdValue;
    }

    TOptional<FString> FReportByUserIdRequest::GetStatusName() const
    {
        return StatusNameValue;
    }

    TSharedPtr<TArray<TSharedPtr<Model::FEvent>>> FReportByUserIdRequest::GetEvents() const
    {
        if (!EventsValue.IsValid())
        {
            return nullptr;
        }
        return EventsValue;
    }

    TOptional<FString> FReportByUserIdRequest::GetDuplicationAvoider() const
    {
        return DuplicationAvoiderValue;
    }

    TSharedPtr<FReportByUserIdRequest> FReportByUserIdRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FReportByUserIdRequest>()
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
            ->WithUserId(Data->HasField("userId") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("userId", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithStatusName(Data->HasField("statusName") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("statusName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
          ->WithEvents(Data->HasField("events") ? [Data]() -> TSharedPtr<TArray<Model::FEventPtr>>
              {
                  auto v = MakeShared<TArray<Model::FEventPtr>>();
                  if (!Data->HasTypedField<EJson::Null>("events") && Data->HasTypedField<EJson::Array>("events"))
                  {
                      for (auto JsonObjectValue : Data->GetArrayField("events"))
                      {
                          v->Add(Model::FEvent::FromJson(JsonObjectValue->AsObject()));
                      }
                  }
                  return v;
              }() : MakeShared<TArray<Model::FEventPtr>>())
          ->WithDuplicationAvoider(Data->HasField("duplicationAvoider") ? TOptional<FString>(Data->GetStringField("duplicationAvoider")) : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FReportByUserIdRequest::ToJson() const
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
        if (UserIdValue.IsSet())
        {
            JsonRootObject->SetStringField("userId", UserIdValue.GetValue());
        }
        if (StatusNameValue.IsSet())
        {
            JsonRootObject->SetStringField("statusName", StatusNameValue.GetValue());
        }
        if (EventsValue != nullptr && EventsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *EventsValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("events", v);
        }
        if (DuplicationAvoiderValue.IsSet())
        {
            JsonRootObject->SetStringField("duplicationAvoider", DuplicationAvoiderValue.GetValue());
        }
        return JsonRootObject;
    }
}