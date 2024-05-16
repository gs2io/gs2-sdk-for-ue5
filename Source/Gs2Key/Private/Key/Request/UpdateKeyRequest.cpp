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

#include "Key/Request/UpdateKeyRequest.h"

namespace Gs2::Key::Request
{
    FUpdateKeyRequest::FUpdateKeyRequest():
        NamespaceNameValue(TOptional<FString>()),
        KeyNameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>())
    {
    }

    FUpdateKeyRequest::FUpdateKeyRequest(
        const FUpdateKeyRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        KeyNameValue(From.KeyNameValue),
        DescriptionValue(From.DescriptionValue)
    {
    }

    TSharedPtr<FUpdateKeyRequest> FUpdateKeyRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateKeyRequest> FUpdateKeyRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateKeyRequest> FUpdateKeyRequest::WithKeyName(
        const TOptional<FString> KeyName
    )
    {
        this->KeyNameValue = KeyName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateKeyRequest> FUpdateKeyRequest::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
        return SharedThis(this);
    }

    TOptional<FString> FUpdateKeyRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FUpdateKeyRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FUpdateKeyRequest::GetKeyName() const
    {
        return KeyNameValue;
    }

    TOptional<FString> FUpdateKeyRequest::GetDescription() const
    {
        return DescriptionValue;
    }

    TSharedPtr<FUpdateKeyRequest> FUpdateKeyRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FUpdateKeyRequest>()
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
            ->WithKeyName(Data->HasField(ANSI_TO_TCHAR("keyName")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("keyName"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithDescription(Data->HasField(ANSI_TO_TCHAR("description")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("description"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FUpdateKeyRequest::ToJson() const
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
        if (DescriptionValue.IsSet())
        {
            JsonRootObject->SetStringField("description", DescriptionValue.GetValue());
        }
        return JsonRootObject;
    }
}