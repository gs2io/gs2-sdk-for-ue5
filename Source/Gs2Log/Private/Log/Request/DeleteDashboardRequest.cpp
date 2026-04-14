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

#include "Log/Request/DeleteDashboardRequest.h"

namespace Gs2::Log::Request
{
    FDeleteDashboardRequest::FDeleteDashboardRequest():
        NamespaceNameValue(TOptional<FString>()),
        DashboardNameValue(TOptional<FString>())
    {
    }

    FDeleteDashboardRequest::FDeleteDashboardRequest(
        const FDeleteDashboardRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        DashboardNameValue(From.DashboardNameValue)
    {
    }

    TSharedPtr<FDeleteDashboardRequest> FDeleteDashboardRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FDeleteDashboardRequest> FDeleteDashboardRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FDeleteDashboardRequest> FDeleteDashboardRequest::WithDashboardName(
        const TOptional<FString> DashboardName
    )
    {
        this->DashboardNameValue = DashboardName;
        return SharedThis(this);
    }

    TOptional<FString> FDeleteDashboardRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FDeleteDashboardRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FDeleteDashboardRequest::GetDashboardName() const
    {
        return DashboardNameValue;
    }

    TSharedPtr<FDeleteDashboardRequest> FDeleteDashboardRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FDeleteDashboardRequest>()
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
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FDeleteDashboardRequest::ToJson() const
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
        return JsonRootObject;
    }
}