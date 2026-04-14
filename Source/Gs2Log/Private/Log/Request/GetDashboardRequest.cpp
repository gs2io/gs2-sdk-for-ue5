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

#include "Log/Request/GetDashboardRequest.h"

namespace Gs2::Log::Request
{
    FGetDashboardRequest::FGetDashboardRequest():
        NamespaceNameValue(TOptional<FString>()),
        DashboardNameValue(TOptional<FString>())
    {
    }

    FGetDashboardRequest::FGetDashboardRequest(
        const FGetDashboardRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        DashboardNameValue(From.DashboardNameValue)
    {
    }

    TSharedPtr<FGetDashboardRequest> FGetDashboardRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FGetDashboardRequest> FGetDashboardRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FGetDashboardRequest> FGetDashboardRequest::WithDashboardName(
        const TOptional<FString> DashboardName
    )
    {
        this->DashboardNameValue = DashboardName;
        return SharedThis(this);
    }

    TOptional<FString> FGetDashboardRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FGetDashboardRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FGetDashboardRequest::GetDashboardName() const
    {
        return DashboardNameValue;
    }

    TSharedPtr<FGetDashboardRequest> FGetDashboardRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FGetDashboardRequest>()
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

    TSharedPtr<FJsonObject> FGetDashboardRequest::ToJson() const
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