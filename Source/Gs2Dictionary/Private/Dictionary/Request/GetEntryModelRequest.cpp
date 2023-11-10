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

#include "Dictionary/Request/GetEntryModelRequest.h"

namespace Gs2::Dictionary::Request
{
    FGetEntryModelRequest::FGetEntryModelRequest():
        NamespaceNameValue(TOptional<FString>()),
        EntryNameValue(TOptional<FString>())
    {
    }

    FGetEntryModelRequest::FGetEntryModelRequest(
        const FGetEntryModelRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        EntryNameValue(From.EntryNameValue)
    {
    }

    TSharedPtr<FGetEntryModelRequest> FGetEntryModelRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FGetEntryModelRequest> FGetEntryModelRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FGetEntryModelRequest> FGetEntryModelRequest::WithEntryName(
        const TOptional<FString> EntryName
    )
    {
        this->EntryNameValue = EntryName;
        return SharedThis(this);
    }

    TOptional<FString> FGetEntryModelRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FGetEntryModelRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FGetEntryModelRequest::GetEntryName() const
    {
        return EntryNameValue;
    }

    TSharedPtr<FGetEntryModelRequest> FGetEntryModelRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FGetEntryModelRequest>()
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
            ->WithEntryName(Data->HasField("entryName") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("entryName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FGetEntryModelRequest::ToJson() const
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
        if (EntryNameValue.IsSet())
        {
            JsonRootObject->SetStringField("entryName", EntryNameValue.GetValue());
        }
        return JsonRootObject;
    }
}