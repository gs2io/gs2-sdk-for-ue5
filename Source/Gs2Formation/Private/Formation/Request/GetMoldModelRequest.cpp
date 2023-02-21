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

#include "Formation/Request/GetMoldModelRequest.h"

namespace Gs2::Formation::Request
{
    FGetMoldModelRequest::FGetMoldModelRequest():
        NamespaceNameValue(TOptional<FString>()),
        MoldNameValue(TOptional<FString>())
    {
    }

    FGetMoldModelRequest::FGetMoldModelRequest(
        const FGetMoldModelRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        MoldNameValue(From.MoldNameValue)
    {
    }

    TSharedPtr<FGetMoldModelRequest> FGetMoldModelRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FGetMoldModelRequest> FGetMoldModelRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FGetMoldModelRequest> FGetMoldModelRequest::WithMoldName(
        const TOptional<FString> MoldName
    )
    {
        this->MoldNameValue = MoldName;
        return SharedThis(this);
    }

    TOptional<FString> FGetMoldModelRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FGetMoldModelRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FGetMoldModelRequest::GetMoldName() const
    {
        return MoldNameValue;
    }

    TSharedPtr<FGetMoldModelRequest> FGetMoldModelRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FGetMoldModelRequest>()
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
            ->WithMoldName(Data->HasField("moldName") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("moldName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FGetMoldModelRequest::ToJson() const
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
        if (MoldNameValue.IsSet())
        {
            JsonRootObject->SetStringField("moldName", MoldNameValue.GetValue());
        }
        return JsonRootObject;
    }
}