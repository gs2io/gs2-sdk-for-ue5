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

#include "Distributor/Request/RunStampTaskRequest.h"

namespace Gs2::Distributor::Request
{
    FRunStampTaskRequest::FRunStampTaskRequest():
        NamespaceNameValue(TOptional<FString>()),
        StampTaskValue(TOptional<FString>()),
        KeyIdValue(TOptional<FString>())
    {
    }

    FRunStampTaskRequest::FRunStampTaskRequest(
        const FRunStampTaskRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        StampTaskValue(From.StampTaskValue),
        KeyIdValue(From.KeyIdValue)
    {
    }

    TSharedPtr<FRunStampTaskRequest> FRunStampTaskRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FRunStampTaskRequest> FRunStampTaskRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FRunStampTaskRequest> FRunStampTaskRequest::WithStampTask(
        const TOptional<FString> StampTask
    )
    {
        this->StampTaskValue = StampTask;
        return SharedThis(this);
    }

    TSharedPtr<FRunStampTaskRequest> FRunStampTaskRequest::WithKeyId(
        const TOptional<FString> KeyId
    )
    {
        this->KeyIdValue = KeyId;
        return SharedThis(this);
    }

    TOptional<FString> FRunStampTaskRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FRunStampTaskRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FRunStampTaskRequest::GetStampTask() const
    {
        return StampTaskValue;
    }

    TOptional<FString> FRunStampTaskRequest::GetKeyId() const
    {
        return KeyIdValue;
    }

    TSharedPtr<FRunStampTaskRequest> FRunStampTaskRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FRunStampTaskRequest>()
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
            ->WithStampTask(Data->HasField("stampTask") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("stampTask", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithKeyId(Data->HasField("keyId") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("keyId", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FRunStampTaskRequest::ToJson() const
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
        if (StampTaskValue.IsSet())
        {
            JsonRootObject->SetStringField("stampTask", StampTaskValue.GetValue());
        }
        if (KeyIdValue.IsSet())
        {
            JsonRootObject->SetStringField("keyId", KeyIdValue.GetValue());
        }
        return JsonRootObject;
    }
}