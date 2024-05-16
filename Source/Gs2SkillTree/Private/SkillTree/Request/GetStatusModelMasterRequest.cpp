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

#include "SkillTree/Request/GetStatusModelMasterRequest.h"

namespace Gs2::SkillTree::Request
{
    FGetStatusModelMasterRequest::FGetStatusModelMasterRequest():
        NamespaceNameValue(TOptional<FString>()),
        NodeModelNameValue(TOptional<FString>())
    {
    }

    FGetStatusModelMasterRequest::FGetStatusModelMasterRequest(
        const FGetStatusModelMasterRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        NodeModelNameValue(From.NodeModelNameValue)
    {
    }

    TSharedPtr<FGetStatusModelMasterRequest> FGetStatusModelMasterRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FGetStatusModelMasterRequest> FGetStatusModelMasterRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FGetStatusModelMasterRequest> FGetStatusModelMasterRequest::WithNodeModelName(
        const TOptional<FString> NodeModelName
    )
    {
        this->NodeModelNameValue = NodeModelName;
        return SharedThis(this);
    }

    TOptional<FString> FGetStatusModelMasterRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FGetStatusModelMasterRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FGetStatusModelMasterRequest::GetNodeModelName() const
    {
        return NodeModelNameValue;
    }

    TSharedPtr<FGetStatusModelMasterRequest> FGetStatusModelMasterRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FGetStatusModelMasterRequest>()
            ->WithContextStack(Data->HasField(ANSI_TO_TCHAR("contextStack")) ? TOptional<FString>(Data->GetStringField(ANSI_TO_TCHAR("contextStack"))) : TOptional<FString>())
            ->WithNamespaceName(Data->HasField(ANSI_TO_TCHAR("namespaceName")) ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("namespaceName"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithNodeModelName(Data->HasField(ANSI_TO_TCHAR("nodeModelName")) ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("nodeModelName"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FGetStatusModelMasterRequest::ToJson() const
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
        if (NodeModelNameValue.IsSet())
        {
            JsonRootObject->SetStringField("nodeModelName", NodeModelNameValue.GetValue());
        }
        return JsonRootObject;
    }
}