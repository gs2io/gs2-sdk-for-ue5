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

#include "Buff/Request/GetBuffEntryModelMasterRequest.h"

namespace Gs2::Buff::Request
{
    FGetBuffEntryModelMasterRequest::FGetBuffEntryModelMasterRequest():
        NamespaceNameValue(TOptional<FString>()),
        BuffEntryNameValue(TOptional<FString>())
    {
    }

    FGetBuffEntryModelMasterRequest::FGetBuffEntryModelMasterRequest(
        const FGetBuffEntryModelMasterRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        BuffEntryNameValue(From.BuffEntryNameValue)
    {
    }

    TSharedPtr<FGetBuffEntryModelMasterRequest> FGetBuffEntryModelMasterRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FGetBuffEntryModelMasterRequest> FGetBuffEntryModelMasterRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FGetBuffEntryModelMasterRequest> FGetBuffEntryModelMasterRequest::WithBuffEntryName(
        const TOptional<FString> BuffEntryName
    )
    {
        this->BuffEntryNameValue = BuffEntryName;
        return SharedThis(this);
    }

    TOptional<FString> FGetBuffEntryModelMasterRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FGetBuffEntryModelMasterRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FGetBuffEntryModelMasterRequest::GetBuffEntryName() const
    {
        return BuffEntryNameValue;
    }

    TSharedPtr<FGetBuffEntryModelMasterRequest> FGetBuffEntryModelMasterRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FGetBuffEntryModelMasterRequest>()
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
            ->WithBuffEntryName(Data->HasField("buffEntryName") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("buffEntryName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FGetBuffEntryModelMasterRequest::ToJson() const
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