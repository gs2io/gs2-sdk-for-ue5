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

#include "Key/Request/DeleteKeyRequest.h"

namespace Gs2::Key::Request
{
    FDeleteKeyRequest::FDeleteKeyRequest():
        NamespaceNameValue(TOptional<FString>()),
        KeyNameValue(TOptional<FString>())
    {
    }

    FDeleteKeyRequest::FDeleteKeyRequest(
        const FDeleteKeyRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        KeyNameValue(From.KeyNameValue)
    {
    }

    TSharedPtr<FDeleteKeyRequest> FDeleteKeyRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FDeleteKeyRequest> FDeleteKeyRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FDeleteKeyRequest> FDeleteKeyRequest::WithKeyName(
        const TOptional<FString> KeyName
    )
    {
        this->KeyNameValue = KeyName;
        return SharedThis(this);
    }

    TOptional<FString> FDeleteKeyRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FDeleteKeyRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FDeleteKeyRequest::GetKeyName() const
    {
        return KeyNameValue;
    }

    TSharedPtr<FDeleteKeyRequest> FDeleteKeyRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FDeleteKeyRequest>()
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
            ->WithKeyName(Data->HasField("keyName") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("keyName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FDeleteKeyRequest::ToJson() const
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
        if (KeyNameValue.IsSet())
        {
            JsonRootObject->SetStringField("keyName", KeyNameValue.GetValue());
        }
        return JsonRootObject;
    }
}