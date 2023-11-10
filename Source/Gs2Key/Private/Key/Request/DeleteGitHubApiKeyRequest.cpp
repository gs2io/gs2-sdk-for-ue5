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

#include "Key/Request/DeleteGitHubApiKeyRequest.h"

namespace Gs2::Key::Request
{
    FDeleteGitHubApiKeyRequest::FDeleteGitHubApiKeyRequest():
        NamespaceNameValue(TOptional<FString>()),
        ApiKeyNameValue(TOptional<FString>())
    {
    }

    FDeleteGitHubApiKeyRequest::FDeleteGitHubApiKeyRequest(
        const FDeleteGitHubApiKeyRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        ApiKeyNameValue(From.ApiKeyNameValue)
    {
    }

    TSharedPtr<FDeleteGitHubApiKeyRequest> FDeleteGitHubApiKeyRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FDeleteGitHubApiKeyRequest> FDeleteGitHubApiKeyRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FDeleteGitHubApiKeyRequest> FDeleteGitHubApiKeyRequest::WithApiKeyName(
        const TOptional<FString> ApiKeyName
    )
    {
        this->ApiKeyNameValue = ApiKeyName;
        return SharedThis(this);
    }

    TOptional<FString> FDeleteGitHubApiKeyRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FDeleteGitHubApiKeyRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FDeleteGitHubApiKeyRequest::GetApiKeyName() const
    {
        return ApiKeyNameValue;
    }

    TSharedPtr<FDeleteGitHubApiKeyRequest> FDeleteGitHubApiKeyRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FDeleteGitHubApiKeyRequest>()
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
            ->WithApiKeyName(Data->HasField("apiKeyName") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("apiKeyName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FDeleteGitHubApiKeyRequest::ToJson() const
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