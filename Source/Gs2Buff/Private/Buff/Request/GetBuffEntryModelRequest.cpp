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

#include "Buff/Request/GetBuffEntryModelRequest.h"

namespace Gs2::Buff::Request
{
    FGetBuffEntryModelRequest::FGetBuffEntryModelRequest():
        NamespaceNameValue(TOptional<FString>()),
        BuffEntryNameValue(TOptional<FString>())
    {
    }

    FGetBuffEntryModelRequest::FGetBuffEntryModelRequest(
        const FGetBuffEntryModelRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        BuffEntryNameValue(From.BuffEntryNameValue)
    {
    }

    TSharedPtr<FGetBuffEntryModelRequest> FGetBuffEntryModelRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FGetBuffEntryModelRequest> FGetBuffEntryModelRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FGetBuffEntryModelRequest> FGetBuffEntryModelRequest::WithBuffEntryName(
        const TOptional<FString> BuffEntryName
    )
    {
        this->BuffEntryNameValue = BuffEntryName;
        return SharedThis(this);
    }

    TOptional<FString> FGetBuffEntryModelRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FGetBuffEntryModelRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FGetBuffEntryModelRequest::GetBuffEntryName() const
    {
        return BuffEntryNameValue;
    }

    TSharedPtr<FGetBuffEntryModelRequest> FGetBuffEntryModelRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FGetBuffEntryModelRequest>()
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
            ->WithBuffEntryName(Data->HasField(ANSI_TO_TCHAR("buffEntryName")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("buffEntryName"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FGetBuffEntryModelRequest::ToJson() const
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
        if (BuffEntryNameValue.IsSet())
        {
            JsonRootObject->SetStringField("buffEntryName", BuffEntryNameValue.GetValue());
        }
        return JsonRootObject;
    }
}