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

#include "Limit/Request/GetLimitModelRequest.h"

namespace Gs2::Limit::Request
{
    FGetLimitModelRequest::FGetLimitModelRequest():
        NamespaceNameValue(TOptional<FString>()),
        LimitNameValue(TOptional<FString>())
    {
    }

    FGetLimitModelRequest::FGetLimitModelRequest(
        const FGetLimitModelRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        LimitNameValue(From.LimitNameValue)
    {
    }

    TSharedPtr<FGetLimitModelRequest> FGetLimitModelRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FGetLimitModelRequest> FGetLimitModelRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FGetLimitModelRequest> FGetLimitModelRequest::WithLimitName(
        const TOptional<FString> LimitName
    )
    {
        this->LimitNameValue = LimitName;
        return SharedThis(this);
    }

    TOptional<FString> FGetLimitModelRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FGetLimitModelRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FGetLimitModelRequest::GetLimitName() const
    {
        return LimitNameValue;
    }

    TSharedPtr<FGetLimitModelRequest> FGetLimitModelRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FGetLimitModelRequest>()
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
            ->WithLimitName(Data->HasField("limitName") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("limitName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FGetLimitModelRequest::ToJson() const
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
        if (LimitNameValue.IsSet())
        {
            JsonRootObject->SetStringField("limitName", LimitNameValue.GetValue());
        }
        return JsonRootObject;
    }
}