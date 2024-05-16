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

#include "Key/Request/DecryptRequest.h"

namespace Gs2::Key::Request
{
    FDecryptRequest::FDecryptRequest():
        NamespaceNameValue(TOptional<FString>()),
        KeyNameValue(TOptional<FString>()),
        DataValue(TOptional<FString>())
    {
    }

    FDecryptRequest::FDecryptRequest(
        const FDecryptRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        KeyNameValue(From.KeyNameValue),
        DataValue(From.DataValue)
    {
    }

    TSharedPtr<FDecryptRequest> FDecryptRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FDecryptRequest> FDecryptRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FDecryptRequest> FDecryptRequest::WithKeyName(
        const TOptional<FString> KeyName
    )
    {
        this->KeyNameValue = KeyName;
        return SharedThis(this);
    }

    TSharedPtr<FDecryptRequest> FDecryptRequest::WithData(
        const TOptional<FString> Data
    )
    {
        this->DataValue = Data;
        return SharedThis(this);
    }

    TOptional<FString> FDecryptRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FDecryptRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FDecryptRequest::GetKeyName() const
    {
        return KeyNameValue;
    }

    TOptional<FString> FDecryptRequest::GetData() const
    {
        return DataValue;
    }

    TSharedPtr<FDecryptRequest> FDecryptRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FDecryptRequest>()
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
            ->WithData(Data->HasField(ANSI_TO_TCHAR("data")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("data"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FDecryptRequest::ToJson() const
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
        if (DataValue.IsSet())
        {
            JsonRootObject->SetStringField("data", DataValue.GetValue());
        }
        return JsonRootObject;
    }
}