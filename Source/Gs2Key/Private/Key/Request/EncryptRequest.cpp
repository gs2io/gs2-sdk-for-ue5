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

#include "Key/Request/EncryptRequest.h"

namespace Gs2::Key::Request
{
    FEncryptRequest::FEncryptRequest():
        NamespaceNameValue(TOptional<FString>()),
        KeyNameValue(TOptional<FString>()),
        DataValue(TOptional<FString>())
    {
    }

    FEncryptRequest::FEncryptRequest(
        const FEncryptRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        KeyNameValue(From.KeyNameValue),
        DataValue(From.DataValue)
    {
    }

    TSharedPtr<FEncryptRequest> FEncryptRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FEncryptRequest> FEncryptRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FEncryptRequest> FEncryptRequest::WithKeyName(
        const TOptional<FString> KeyName
    )
    {
        this->KeyNameValue = KeyName;
        return SharedThis(this);
    }

    TSharedPtr<FEncryptRequest> FEncryptRequest::WithData(
        const TOptional<FString> Data
    )
    {
        this->DataValue = Data;
        return SharedThis(this);
    }

    TOptional<FString> FEncryptRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FEncryptRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FEncryptRequest::GetKeyName() const
    {
        return KeyNameValue;
    }

    TOptional<FString> FEncryptRequest::GetData() const
    {
        return DataValue;
    }

    TSharedPtr<FEncryptRequest> FEncryptRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FEncryptRequest>()
            ->WithContextStack(Data->HasField("contextStack") ? TOptional<FString>(Data->GetStringField("contextStack")) : TOptional<FString>())
            ->WithNamespaceName(Data->HasField("namespaceName") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("namespaceName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithKeyName(Data->HasField("keyName") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("keyName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithData(Data->HasField("data") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("data", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FEncryptRequest::ToJson() const
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