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

#include "Log/Request/CreateFacetModelRequest.h"

namespace Gs2::Log::Request
{
    FCreateFacetModelRequest::FCreateFacetModelRequest():
        NamespaceNameValue(TOptional<FString>()),
        FieldValue(TOptional<FString>()),
        TypeValue(TOptional<FString>()),
        DisplayNameValue(TOptional<FString>()),
        OrderValue(TOptional<int32>())
    {
    }

    FCreateFacetModelRequest::FCreateFacetModelRequest(
        const FCreateFacetModelRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        FieldValue(From.FieldValue),
        TypeValue(From.TypeValue),
        DisplayNameValue(From.DisplayNameValue),
        OrderValue(From.OrderValue)
    {
    }

    TSharedPtr<FCreateFacetModelRequest> FCreateFacetModelRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FCreateFacetModelRequest> FCreateFacetModelRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FCreateFacetModelRequest> FCreateFacetModelRequest::WithField(
        const TOptional<FString> Field
    )
    {
        this->FieldValue = Field;
        return SharedThis(this);
    }

    TSharedPtr<FCreateFacetModelRequest> FCreateFacetModelRequest::WithType(
        const TOptional<FString> Type
    )
    {
        this->TypeValue = Type;
        return SharedThis(this);
    }

    TSharedPtr<FCreateFacetModelRequest> FCreateFacetModelRequest::WithDisplayName(
        const TOptional<FString> DisplayName
    )
    {
        this->DisplayNameValue = DisplayName;
        return SharedThis(this);
    }

    TSharedPtr<FCreateFacetModelRequest> FCreateFacetModelRequest::WithOrder(
        const TOptional<int32> Order
    )
    {
        this->OrderValue = Order;
        return SharedThis(this);
    }

    TOptional<FString> FCreateFacetModelRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FCreateFacetModelRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FCreateFacetModelRequest::GetField() const
    {
        return FieldValue;
    }

    TOptional<FString> FCreateFacetModelRequest::GetType() const
    {
        return TypeValue;
    }

    TOptional<FString> FCreateFacetModelRequest::GetDisplayName() const
    {
        return DisplayNameValue;
    }

    TOptional<int32> FCreateFacetModelRequest::GetOrder() const
    {
        return OrderValue;
    }

    FString FCreateFacetModelRequest::GetOrderString() const
    {
        if (!OrderValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), OrderValue.GetValue());
    }

    TSharedPtr<FCreateFacetModelRequest> FCreateFacetModelRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FCreateFacetModelRequest>()
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
            ->WithField(Data->HasField(ANSI_TO_TCHAR("field")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("field"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithType(Data->HasField(ANSI_TO_TCHAR("type")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("type"), v))
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
            ->WithOrder(Data->HasField(ANSI_TO_TCHAR("order")) ? [Data]() -> TOptional<int32>
              {
                  int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("order"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int32>();
              }() : TOptional<int32>());
    }

    TSharedPtr<FJsonObject> FCreateFacetModelRequest::ToJson() const
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
        if (FieldValue.IsSet())
        {
            JsonRootObject->SetStringField("field", FieldValue.GetValue());
        }
        if (TypeValue.IsSet())
        {
            JsonRootObject->SetStringField("type", TypeValue.GetValue());
        }
        if (DisplayNameValue.IsSet())
        {
            JsonRootObject->SetStringField("displayName", DisplayNameValue.GetValue());
        }
        if (OrderValue.IsSet())
        {
            JsonRootObject->SetNumberField("order", OrderValue.GetValue());
        }
        return JsonRootObject;
    }
}