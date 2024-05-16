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

#include "Key/Request/GetGitHubApiKeyRequest.h"

namespace Gs2::Key::Request
{
    FGetGitHubApiKeyRequest::FGetGitHubApiKeyRequest():
        NamespaceNameValue(TOptional<FString>()),
        ApiKeyNameValue(TOptional<FString>())
    {
    }

    FGetGitHubApiKeyRequest::FGetGitHubApiKeyRequest(
        const FGetGitHubApiKeyRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        ApiKeyNameValue(From.ApiKeyNameValue)
    {
    }

    TSharedPtr<FGetGitHubApiKeyRequest> FGetGitHubApiKeyRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FGetGitHubApiKeyRequest> FGetGitHubApiKeyRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FGetGitHubApiKeyRequest> FGetGitHubApiKeyRequest::WithApiKeyName(
        const TOptional<FString> ApiKeyName
    )
    {
        this->ApiKeyNameValue = ApiKeyName;
        return SharedThis(this);
    }

    TOptional<FString> FGetGitHubApiKeyRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FGetGitHubApiKeyRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FGetGitHubApiKeyRequest::GetApiKeyName() const
    {
        return ApiKeyNameValue;
    }

    TSharedPtr<FGetGitHubApiKeyRequest> FGetGitHubApiKeyRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FGetGitHubApiKeyRequest>()
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
            ->WithApiKeyName(Data->HasField(ANSI_TO_TCHAR("apiKeyName")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("apiKeyName"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FGetGitHubApiKeyRequest::ToJson() const
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
        if (ApiKeyNameValue.IsSet())
        {
            JsonRootObject->SetStringField("apiKeyName", ApiKeyNameValue.GetValue());
        }
        return JsonRootObject;
    }
}