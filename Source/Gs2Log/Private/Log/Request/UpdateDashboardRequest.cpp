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

#include "Log/Request/UpdateDashboardRequest.h"

namespace Gs2::Log::Request
{
    FUpdateDashboardRequest::FUpdateDashboardRequest():
        NamespaceNameValue(TOptional<FString>()),
        DashboardNameValue(TOptional<FString>()),
        DisplayNameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        PayloadValue(TOptional<FString>())
    {
    }

    FUpdateDashboardRequest::FUpdateDashboardRequest(
        const FUpdateDashboardRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        DashboardNameValue(From.DashboardNameValue),
        DisplayNameValue(From.DisplayNameValue),
        DescriptionValue(From.DescriptionValue),
        PayloadValue(From.PayloadValue)
    {
    }

    TSharedPtr<FUpdateDashboardRequest> FUpdateDashboardRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateDashboardRequest> FUpdateDashboardRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateDashboardRequest> FUpdateDashboardRequest::WithDashboardName(
        const TOptional<FString> DashboardName
    )
    {
        this->DashboardNameValue = DashboardName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateDashboardRequest> FUpdateDashboardRequest::WithDisplayName(
        const TOptional<FString> DisplayName
    )
    {
        this->DisplayNameValue = DisplayName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateDashboardRequest> FUpdateDashboardRequest::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateDashboardRequest> FUpdateDashboardRequest::WithPayload(
        const TOptional<FString> Payload
    )
    {
        this->PayloadValue = Payload;
        return SharedThis(this);
    }

    TOptional<FString> FUpdateDashboardRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FUpdateDashboardRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FUpdateDashboardRequest::GetDashboardName() const
    {
        return DashboardNameValue;
    }

    TOptional<FString> FUpdateDashboardRequest::GetDisplayName() const
    {
        return DisplayNameValue;
    }

    TOptional<FString> FUpdateDashboardRequest::GetDescription() const
    {
        return DescriptionValue;
    }

    TOptional<FString> FUpdateDashboardRequest::GetPayload() const
    {
        return PayloadValue;
    }

    TSharedPtr<FUpdateDashboardRequest> FUpdateDashboardRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FUpdateDashboardRequest>()
            ->WithContextStack(Data->HasField(ANSI_TO_TCHAR("contextStack")) ? TOptional<FString>(Data->GetStringField(ANSI_TO_TCHAR("contextStack"))) : TOptional<FString>())
            ->WithNamespaceName(Data->HasField(ANSI_TO_TCHAR("namespaceName")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("namespaceName"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithDashboardName(Data->HasField(ANSI_TO_TCHAR("dashboardName")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("dashboardName"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithDisplayName(Data->HasField(ANSI_TO_TCHAR("displayName")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("displayName"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithDescription(Data->HasField(ANSI_TO_TCHAR("description")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("description"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithPayload(Data->HasField(ANSI_TO_TCHAR("payload")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("payload"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FUpdateDashboardRequest::ToJson() const
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
        if (DashboardNameValue.IsSet())
        {
            JsonRootObject->SetStringField("dashboardName", DashboardNameValue.GetValue());
        }
        if (DisplayNameValue.IsSet())
        {
            JsonRootObject->SetStringField("displayName", DisplayNameValue.GetValue());
        }
        if (DescriptionValue.IsSet())
        {
            JsonRootObject->SetStringField("description", DescriptionValue.GetValue());
        }
        if (PayloadValue.IsSet())
        {
            JsonRootObject->SetStringField("payload", PayloadValue.GetValue());
        }
        return JsonRootObject;
    }
}