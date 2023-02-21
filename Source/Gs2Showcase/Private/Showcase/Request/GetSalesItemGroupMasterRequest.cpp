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

#include "Showcase/Request/GetSalesItemGroupMasterRequest.h"

namespace Gs2::Showcase::Request
{
    FGetSalesItemGroupMasterRequest::FGetSalesItemGroupMasterRequest():
        NamespaceNameValue(TOptional<FString>()),
        SalesItemGroupNameValue(TOptional<FString>())
    {
    }

    FGetSalesItemGroupMasterRequest::FGetSalesItemGroupMasterRequest(
        const FGetSalesItemGroupMasterRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        SalesItemGroupNameValue(From.SalesItemGroupNameValue)
    {
    }

    TSharedPtr<FGetSalesItemGroupMasterRequest> FGetSalesItemGroupMasterRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FGetSalesItemGroupMasterRequest> FGetSalesItemGroupMasterRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FGetSalesItemGroupMasterRequest> FGetSalesItemGroupMasterRequest::WithSalesItemGroupName(
        const TOptional<FString> SalesItemGroupName
    )
    {
        this->SalesItemGroupNameValue = SalesItemGroupName;
        return SharedThis(this);
    }

    TOptional<FString> FGetSalesItemGroupMasterRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FGetSalesItemGroupMasterRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FGetSalesItemGroupMasterRequest::GetSalesItemGroupName() const
    {
        return SalesItemGroupNameValue;
    }

    TSharedPtr<FGetSalesItemGroupMasterRequest> FGetSalesItemGroupMasterRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FGetSalesItemGroupMasterRequest>()
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
            ->WithSalesItemGroupName(Data->HasField("salesItemGroupName") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("salesItemGroupName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FGetSalesItemGroupMasterRequest::ToJson() const
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
        if (SalesItemGroupNameValue.IsSet())
        {
            JsonRootObject->SetStringField("salesItemGroupName", SalesItemGroupNameValue.GetValue());
        }
        return JsonRootObject;
    }
}