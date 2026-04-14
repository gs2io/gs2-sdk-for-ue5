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

#include "Log/Request/DeleteFacetModelRequest.h"

namespace Gs2::Log::Request
{
    FDeleteFacetModelRequest::FDeleteFacetModelRequest():
        NamespaceNameValue(TOptional<FString>()),
        FieldValue(TOptional<FString>())
    {
    }

    FDeleteFacetModelRequest::FDeleteFacetModelRequest(
        const FDeleteFacetModelRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        FieldValue(From.FieldValue)
    {
    }

    TSharedPtr<FDeleteFacetModelRequest> FDeleteFacetModelRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FDeleteFacetModelRequest> FDeleteFacetModelRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FDeleteFacetModelRequest> FDeleteFacetModelRequest::WithField(
        const TOptional<FString> Field
    )
    {
        this->FieldValue = Field;
        return SharedThis(this);
    }

    TOptional<FString> FDeleteFacetModelRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FDeleteFacetModelRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FDeleteFacetModelRequest::GetField() const
    {
        return FieldValue;
    }

    TSharedPtr<FDeleteFacetModelRequest> FDeleteFacetModelRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FDeleteFacetModelRequest>()
            ->WithContextStack(Data->HasField(ANSI_TO_TCHAR("contextStack")) ? TOptional<FString>(Data->GetStringField(ANSI_TO_TCHAR("contextStack"))) : TOptional<FString>())
            ->WithNamespaceName(Data->HasField(ANSI_TO_TCHAR("namespaceName")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("namespaceName"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithField(Data->HasField(ANSI_TO_TCHAR("field")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("field"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FDeleteFacetModelRequest::ToJson() const
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
        if (FieldValue.IsSet())
        {
            JsonRootObject->SetStringField("field", FieldValue.GetValue());
        }
        return JsonRootObject;
    }
}