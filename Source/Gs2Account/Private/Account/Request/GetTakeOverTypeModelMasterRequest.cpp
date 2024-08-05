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

#include "Account/Request/GetTakeOverTypeModelMasterRequest.h"

namespace Gs2::Account::Request
{
    FGetTakeOverTypeModelMasterRequest::FGetTakeOverTypeModelMasterRequest():
        NamespaceNameValue(TOptional<FString>()),
        TypeValue(TOptional<int32>())
    {
    }

    FGetTakeOverTypeModelMasterRequest::FGetTakeOverTypeModelMasterRequest(
        const FGetTakeOverTypeModelMasterRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        TypeValue(From.TypeValue)
    {
    }

    TSharedPtr<FGetTakeOverTypeModelMasterRequest> FGetTakeOverTypeModelMasterRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FGetTakeOverTypeModelMasterRequest> FGetTakeOverTypeModelMasterRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FGetTakeOverTypeModelMasterRequest> FGetTakeOverTypeModelMasterRequest::WithType(
        const TOptional<int32> Type
    )
    {
        this->TypeValue = Type;
        return SharedThis(this);
    }

    TOptional<FString> FGetTakeOverTypeModelMasterRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FGetTakeOverTypeModelMasterRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<int32> FGetTakeOverTypeModelMasterRequest::GetType() const
    {
        return TypeValue;
    }

    FString FGetTakeOverTypeModelMasterRequest::GetTypeString() const
    {
        if (!TypeValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), TypeValue.GetValue());
    }

    TSharedPtr<FGetTakeOverTypeModelMasterRequest> FGetTakeOverTypeModelMasterRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FGetTakeOverTypeModelMasterRequest>()
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
            ->WithType(Data->HasField(ANSI_TO_TCHAR("type")) ? [Data]() -> TOptional<int32>
              {
                  int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("type"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int32>();
              }() : TOptional<int32>());
    }

    TSharedPtr<FJsonObject> FGetTakeOverTypeModelMasterRequest::ToJson() const
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
        if (TypeValue.IsSet())
        {
            JsonRootObject->SetNumberField("type", TypeValue.GetValue());
        }
        return JsonRootObject;
    }
}