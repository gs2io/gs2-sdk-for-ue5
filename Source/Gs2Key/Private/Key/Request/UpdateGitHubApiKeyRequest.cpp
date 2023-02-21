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

#include "Key/Request/UpdateGitHubApiKeyRequest.h"

namespace Gs2::Key::Request
{
    FUpdateGitHubApiKeyRequest::FUpdateGitHubApiKeyRequest():
        NamespaceNameValue(TOptional<FString>()),
        ApiKeyNameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        ApiKeyValue(TOptional<FString>()),
        EncryptionKeyNameValue(TOptional<FString>())
    {
    }

    FUpdateGitHubApiKeyRequest::FUpdateGitHubApiKeyRequest(
        const FUpdateGitHubApiKeyRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        ApiKeyNameValue(From.ApiKeyNameValue),
        DescriptionValue(From.DescriptionValue),
        ApiKeyValue(From.ApiKeyValue),
        EncryptionKeyNameValue(From.EncryptionKeyNameValue)
    {
    }

    TSharedPtr<FUpdateGitHubApiKeyRequest> FUpdateGitHubApiKeyRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateGitHubApiKeyRequest> FUpdateGitHubApiKeyRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateGitHubApiKeyRequest> FUpdateGitHubApiKeyRequest::WithApiKeyName(
        const TOptional<FString> ApiKeyName
    )
    {
        this->ApiKeyNameValue = ApiKeyName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateGitHubApiKeyRequest> FUpdateGitHubApiKeyRequest::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateGitHubApiKeyRequest> FUpdateGitHubApiKeyRequest::WithApiKey(
        const TOptional<FString> ApiKey
    )
    {
        this->ApiKeyValue = ApiKey;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateGitHubApiKeyRequest> FUpdateGitHubApiKeyRequest::WithEncryptionKeyName(
        const TOptional<FString> EncryptionKeyName
    )
    {
        this->EncryptionKeyNameValue = EncryptionKeyName;
        return SharedThis(this);
    }

    TOptional<FString> FUpdateGitHubApiKeyRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FUpdateGitHubApiKeyRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FUpdateGitHubApiKeyRequest::GetApiKeyName() const
    {
        return ApiKeyNameValue;
    }

    TOptional<FString> FUpdateGitHubApiKeyRequest::GetDescription() const
    {
        return DescriptionValue;
    }

    TOptional<FString> FUpdateGitHubApiKeyRequest::GetApiKey() const
    {
        return ApiKeyValue;
    }

    TOptional<FString> FUpdateGitHubApiKeyRequest::GetEncryptionKeyName() const
    {
        return EncryptionKeyNameValue;
    }

    TSharedPtr<FUpdateGitHubApiKeyRequest> FUpdateGitHubApiKeyRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FUpdateGitHubApiKeyRequest>()
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
            ->WithApiKeyName(Data->HasField("apiKeyName") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("apiKeyName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithDescription(Data->HasField("description") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("description", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithApiKey(Data->HasField("apiKey") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("apiKey", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithEncryptionKeyName(Data->HasField("encryptionKeyName") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("encryptionKeyName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FUpdateGitHubApiKeyRequest::ToJson() const
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
        if (DescriptionValue.IsSet())
        {
            JsonRootObject->SetStringField("description", DescriptionValue.GetValue());
        }
        if (ApiKeyValue.IsSet())
        {
            JsonRootObject->SetStringField("apiKey", ApiKeyValue.GetValue());
        }
        if (EncryptionKeyNameValue.IsSet())
        {
            JsonRootObject->SetStringField("encryptionKeyName", EncryptionKeyNameValue.GetValue());
        }
        return JsonRootObject;
    }
}