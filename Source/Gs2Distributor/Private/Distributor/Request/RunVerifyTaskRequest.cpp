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

#include "Distributor/Request/RunVerifyTaskRequest.h"

namespace Gs2::Distributor::Request
{
    FRunVerifyTaskRequest::FRunVerifyTaskRequest():
        NamespaceNameValue(TOptional<FString>()),
        VerifyTaskValue(TOptional<FString>()),
        KeyIdValue(TOptional<FString>())
    {
    }

    FRunVerifyTaskRequest::FRunVerifyTaskRequest(
        const FRunVerifyTaskRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        VerifyTaskValue(From.VerifyTaskValue),
        KeyIdValue(From.KeyIdValue)
    {
    }

    TSharedPtr<FRunVerifyTaskRequest> FRunVerifyTaskRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FRunVerifyTaskRequest> FRunVerifyTaskRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FRunVerifyTaskRequest> FRunVerifyTaskRequest::WithVerifyTask(
        const TOptional<FString> VerifyTask
    )
    {
        this->VerifyTaskValue = VerifyTask;
        return SharedThis(this);
    }

    TSharedPtr<FRunVerifyTaskRequest> FRunVerifyTaskRequest::WithKeyId(
        const TOptional<FString> KeyId
    )
    {
        this->KeyIdValue = KeyId;
        return SharedThis(this);
    }

    TOptional<FString> FRunVerifyTaskRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FRunVerifyTaskRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FRunVerifyTaskRequest::GetVerifyTask() const
    {
        return VerifyTaskValue;
    }

    TOptional<FString> FRunVerifyTaskRequest::GetKeyId() const
    {
        return KeyIdValue;
    }

    TSharedPtr<FRunVerifyTaskRequest> FRunVerifyTaskRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FRunVerifyTaskRequest>()
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
            ->WithVerifyTask(Data->HasField(ANSI_TO_TCHAR("verifyTask")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("verifyTask"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithKeyId(Data->HasField(ANSI_TO_TCHAR("keyId")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("keyId"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FRunVerifyTaskRequest::ToJson() const
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
        if (VerifyTaskValue.IsSet())
        {
            JsonRootObject->SetStringField("verifyTask", VerifyTaskValue.GetValue());
        }
        if (KeyIdValue.IsSet())
        {
            JsonRootObject->SetStringField("keyId", KeyIdValue.GetValue());
        }
        return JsonRootObject;
    }
}