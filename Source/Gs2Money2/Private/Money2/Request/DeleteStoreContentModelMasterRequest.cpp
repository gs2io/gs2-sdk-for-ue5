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

#include "Money2/Request/DeleteStoreContentModelMasterRequest.h"

namespace Gs2::Money2::Request
{
    FDeleteStoreContentModelMasterRequest::FDeleteStoreContentModelMasterRequest():
        NamespaceNameValue(TOptional<FString>()),
        ContentNameValue(TOptional<FString>())
    {
    }

    FDeleteStoreContentModelMasterRequest::FDeleteStoreContentModelMasterRequest(
        const FDeleteStoreContentModelMasterRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        ContentNameValue(From.ContentNameValue)
    {
    }

    TSharedPtr<FDeleteStoreContentModelMasterRequest> FDeleteStoreContentModelMasterRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FDeleteStoreContentModelMasterRequest> FDeleteStoreContentModelMasterRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FDeleteStoreContentModelMasterRequest> FDeleteStoreContentModelMasterRequest::WithContentName(
        const TOptional<FString> ContentName
    )
    {
        this->ContentNameValue = ContentName;
        return SharedThis(this);
    }

    TOptional<FString> FDeleteStoreContentModelMasterRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FDeleteStoreContentModelMasterRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FDeleteStoreContentModelMasterRequest::GetContentName() const
    {
        return ContentNameValue;
    }

    TSharedPtr<FDeleteStoreContentModelMasterRequest> FDeleteStoreContentModelMasterRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FDeleteStoreContentModelMasterRequest>()
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
            ->WithContentName(Data->HasField(ANSI_TO_TCHAR("contentName")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("contentName"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FDeleteStoreContentModelMasterRequest::ToJson() const
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
        if (ContentNameValue.IsSet())
        {
            JsonRootObject->SetStringField("contentName", ContentNameValue.GetValue());
        }
        return JsonRootObject;
    }
}