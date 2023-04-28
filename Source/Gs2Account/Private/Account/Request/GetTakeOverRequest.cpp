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

#include "Account/Request/GetTakeOverRequest.h"

namespace Gs2::Account::Request
{
    FGetTakeOverRequest::FGetTakeOverRequest():
        NamespaceNameValue(TOptional<FString>()),
        AccessTokenValue(TOptional<FString>()),
        TypeValue(TOptional<int32>())
    {
    }

    FGetTakeOverRequest::FGetTakeOverRequest(
        const FGetTakeOverRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        AccessTokenValue(From.AccessTokenValue),
        TypeValue(From.TypeValue)
    {
    }

    TSharedPtr<FGetTakeOverRequest> FGetTakeOverRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FGetTakeOverRequest> FGetTakeOverRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FGetTakeOverRequest> FGetTakeOverRequest::WithAccessToken(
        const TOptional<FString> AccessToken
    )
    {
        this->AccessTokenValue = AccessToken;
        return SharedThis(this);
    }

    TSharedPtr<FGetTakeOverRequest> FGetTakeOverRequest::WithType(
        const TOptional<int32> Type
    )
    {
        this->TypeValue = Type;
        return SharedThis(this);
    }

    TOptional<FString> FGetTakeOverRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FGetTakeOverRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FGetTakeOverRequest::GetAccessToken() const
    {
        return AccessTokenValue;
    }

    TOptional<int32> FGetTakeOverRequest::GetType() const
    {
        return TypeValue;
    }

    FString FGetTakeOverRequest::GetTypeString() const
    {
        if (!TypeValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), TypeValue.GetValue());
    }

    TSharedPtr<FGetTakeOverRequest> FGetTakeOverRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FGetTakeOverRequest>()
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
            ->WithAccessToken(Data->HasField("xGs2AccessToken") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("xGs2AccessToken", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithType(Data->HasField("type") ? [Data]() -> TOptional<int32>
              {
                  int32 v;
                    if (Data->TryGetNumberField("type", v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int32>();
              }() : TOptional<int32>());
    }

    TSharedPtr<FJsonObject> FGetTakeOverRequest::ToJson() const
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
        if (AccessTokenValue.IsSet())
        {
            JsonRootObject->SetStringField("xGs2AccessToken", AccessTokenValue.GetValue());
        }
        if (TypeValue.IsSet())
        {
            JsonRootObject->SetNumberField("type", TypeValue.GetValue());
        }
        return JsonRootObject;
    }
}