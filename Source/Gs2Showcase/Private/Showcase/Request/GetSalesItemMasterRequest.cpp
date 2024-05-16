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

#include "Showcase/Request/GetSalesItemMasterRequest.h"

namespace Gs2::Showcase::Request
{
    FGetSalesItemMasterRequest::FGetSalesItemMasterRequest():
        NamespaceNameValue(TOptional<FString>()),
        SalesItemNameValue(TOptional<FString>())
    {
    }

    FGetSalesItemMasterRequest::FGetSalesItemMasterRequest(
        const FGetSalesItemMasterRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        SalesItemNameValue(From.SalesItemNameValue)
    {
    }

    TSharedPtr<FGetSalesItemMasterRequest> FGetSalesItemMasterRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FGetSalesItemMasterRequest> FGetSalesItemMasterRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FGetSalesItemMasterRequest> FGetSalesItemMasterRequest::WithSalesItemName(
        const TOptional<FString> SalesItemName
    )
    {
        this->SalesItemNameValue = SalesItemName;
        return SharedThis(this);
    }

    TOptional<FString> FGetSalesItemMasterRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FGetSalesItemMasterRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FGetSalesItemMasterRequest::GetSalesItemName() const
    {
        return SalesItemNameValue;
    }

    TSharedPtr<FGetSalesItemMasterRequest> FGetSalesItemMasterRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FGetSalesItemMasterRequest>()
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
            ->WithSalesItemName(Data->HasField(ANSI_TO_TCHAR("salesItemName")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("salesItemName"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FGetSalesItemMasterRequest::ToJson() const
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
        if (SalesItemNameValue.IsSet())
        {
            JsonRootObject->SetStringField("salesItemName", SalesItemNameValue.GetValue());
        }
        return JsonRootObject;
    }
}