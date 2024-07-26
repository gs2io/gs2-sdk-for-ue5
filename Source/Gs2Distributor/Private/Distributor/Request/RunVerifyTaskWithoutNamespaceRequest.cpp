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

#include "Distributor/Request/RunVerifyTaskWithoutNamespaceRequest.h"

namespace Gs2::Distributor::Request
{
    FRunVerifyTaskWithoutNamespaceRequest::FRunVerifyTaskWithoutNamespaceRequest():
        VerifyTaskValue(TOptional<FString>()),
        KeyIdValue(TOptional<FString>())
    {
    }

    FRunVerifyTaskWithoutNamespaceRequest::FRunVerifyTaskWithoutNamespaceRequest(
        const FRunVerifyTaskWithoutNamespaceRequest& From
    ):
        VerifyTaskValue(From.VerifyTaskValue),
        KeyIdValue(From.KeyIdValue)
    {
    }

    TSharedPtr<FRunVerifyTaskWithoutNamespaceRequest> FRunVerifyTaskWithoutNamespaceRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FRunVerifyTaskWithoutNamespaceRequest> FRunVerifyTaskWithoutNamespaceRequest::WithVerifyTask(
        const TOptional<FString> VerifyTask
    )
    {
        this->VerifyTaskValue = VerifyTask;
        return SharedThis(this);
    }

    TSharedPtr<FRunVerifyTaskWithoutNamespaceRequest> FRunVerifyTaskWithoutNamespaceRequest::WithKeyId(
        const TOptional<FString> KeyId
    )
    {
        this->KeyIdValue = KeyId;
        return SharedThis(this);
    }

    TOptional<FString> FRunVerifyTaskWithoutNamespaceRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FRunVerifyTaskWithoutNamespaceRequest::GetVerifyTask() const
    {
        return VerifyTaskValue;
    }

    TOptional<FString> FRunVerifyTaskWithoutNamespaceRequest::GetKeyId() const
    {
        return KeyIdValue;
    }

    TSharedPtr<FRunVerifyTaskWithoutNamespaceRequest> FRunVerifyTaskWithoutNamespaceRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FRunVerifyTaskWithoutNamespaceRequest>()
            ->WithContextStack(Data->HasField(ANSI_TO_TCHAR("contextStack")) ? TOptional<FString>(Data->GetStringField(ANSI_TO_TCHAR("contextStack"))) : TOptional<FString>())
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

    TSharedPtr<FJsonObject> FRunVerifyTaskWithoutNamespaceRequest::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ContextStackValue.IsSet())
        {
            JsonRootObject->SetStringField("contextStack", ContextStackValue.GetValue());
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