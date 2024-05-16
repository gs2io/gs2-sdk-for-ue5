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

#include "Inbox/Request/DeleteGlobalMessageMasterRequest.h"

namespace Gs2::Inbox::Request
{
    FDeleteGlobalMessageMasterRequest::FDeleteGlobalMessageMasterRequest():
        NamespaceNameValue(TOptional<FString>()),
        GlobalMessageNameValue(TOptional<FString>())
    {
    }

    FDeleteGlobalMessageMasterRequest::FDeleteGlobalMessageMasterRequest(
        const FDeleteGlobalMessageMasterRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        GlobalMessageNameValue(From.GlobalMessageNameValue)
    {
    }

    TSharedPtr<FDeleteGlobalMessageMasterRequest> FDeleteGlobalMessageMasterRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FDeleteGlobalMessageMasterRequest> FDeleteGlobalMessageMasterRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FDeleteGlobalMessageMasterRequest> FDeleteGlobalMessageMasterRequest::WithGlobalMessageName(
        const TOptional<FString> GlobalMessageName
    )
    {
        this->GlobalMessageNameValue = GlobalMessageName;
        return SharedThis(this);
    }

    TOptional<FString> FDeleteGlobalMessageMasterRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FDeleteGlobalMessageMasterRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FDeleteGlobalMessageMasterRequest::GetGlobalMessageName() const
    {
        return GlobalMessageNameValue;
    }

    TSharedPtr<FDeleteGlobalMessageMasterRequest> FDeleteGlobalMessageMasterRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FDeleteGlobalMessageMasterRequest>()
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
            ->WithGlobalMessageName(Data->HasField(ANSI_TO_TCHAR("globalMessageName")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("globalMessageName"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FDeleteGlobalMessageMasterRequest::ToJson() const
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
        if (GlobalMessageNameValue.IsSet())
        {
            JsonRootObject->SetStringField("globalMessageName", GlobalMessageNameValue.GetValue());
        }
        return JsonRootObject;
    }
}