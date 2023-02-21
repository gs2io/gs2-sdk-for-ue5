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

#include "SerialKey/Request/GetSerialKeyRequest.h"

namespace Gs2::SerialKey::Request
{
    FGetSerialKeyRequest::FGetSerialKeyRequest():
        NamespaceNameValue(TOptional<FString>()),
        CodeValue(TOptional<FString>())
    {
    }

    FGetSerialKeyRequest::FGetSerialKeyRequest(
        const FGetSerialKeyRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        CodeValue(From.CodeValue)
    {
    }

    TSharedPtr<FGetSerialKeyRequest> FGetSerialKeyRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FGetSerialKeyRequest> FGetSerialKeyRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FGetSerialKeyRequest> FGetSerialKeyRequest::WithCode(
        const TOptional<FString> Code
    )
    {
        this->CodeValue = Code;
        return SharedThis(this);
    }

    TOptional<FString> FGetSerialKeyRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FGetSerialKeyRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FGetSerialKeyRequest::GetCode() const
    {
        return CodeValue;
    }

    TSharedPtr<FGetSerialKeyRequest> FGetSerialKeyRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FGetSerialKeyRequest>()
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
            ->WithCode(Data->HasField("code") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("code", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FGetSerialKeyRequest::ToJson() const
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
        if (CodeValue.IsSet())
        {
            JsonRootObject->SetStringField("code", CodeValue.GetValue());
        }
        return JsonRootObject;
    }
}