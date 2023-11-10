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

#include "Key/Request/CreateGitHubApiKeyRequest.h"

namespace Gs2::Key::Request
{
    FCreateGitHubApiKeyRequest::FCreateGitHubApiKeyRequest():
        NamespaceNameValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        ApiKeyValue(TOptional<FString>()),
        EncryptionKeyNameValue(TOptional<FString>())
    {
    }

    FCreateGitHubApiKeyRequest::FCreateGitHubApiKeyRequest(
        const FCreateGitHubApiKeyRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        NameValue(From.NameValue),
        DescriptionValue(From.DescriptionValue),
        ApiKeyValue(From.ApiKeyValue),
        EncryptionKeyNameValue(From.EncryptionKeyNameValue)
    {
    }

    TSharedPtr<FCreateGitHubApiKeyRequest> FCreateGitHubApiKeyRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FCreateGitHubApiKeyRequest> FCreateGitHubApiKeyRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FCreateGitHubApiKeyRequest> FCreateGitHubApiKeyRequest::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FCreateGitHubApiKeyRequest> FCreateGitHubApiKeyRequest::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
        return SharedThis(this);
    }

    TSharedPtr<FCreateGitHubApiKeyRequest> FCreateGitHubApiKeyRequest::WithApiKey(
        const TOptional<FString> ApiKey
    )
    {
        this->ApiKeyValue = ApiKey;
        return SharedThis(this);
    }

    TSharedPtr<FCreateGitHubApiKeyRequest> FCreateGitHubApiKeyRequest::WithEncryptionKeyName(
        const TOptional<FString> EncryptionKeyName
    )
    {
        this->EncryptionKeyNameValue = EncryptionKeyName;
        return SharedThis(this);
    }

    TOptional<FString> FCreateGitHubApiKeyRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FCreateGitHubApiKeyRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FCreateGitHubApiKeyRequest::GetName() const
    {
        return NameValue;
    }

    TOptional<FString> FCreateGitHubApiKeyRequest::GetDescription() const
    {
        return DescriptionValue;
    }

    TOptional<FString> FCreateGitHubApiKeyRequest::GetApiKey() const
    {
        return ApiKeyValue;
    }

    TOptional<FString> FCreateGitHubApiKeyRequest::GetEncryptionKeyName() const
    {
        return EncryptionKeyNameValue;
    }

    TSharedPtr<FCreateGitHubApiKeyRequest> FCreateGitHubApiKeyRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FCreateGitHubApiKeyRequest>()
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
            ->WithName(Data->HasField("name") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("name", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithDescription(Data->HasField("description") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("description", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithApiKey(Data->HasField("apiKey") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("apiKey", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithEncryptionKeyName(Data->HasField("encryptionKeyName") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("encryptionKeyName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FCreateGitHubApiKeyRequest::ToJson() const
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
        if (NameValue.IsSet())
        {
            JsonRootObject->SetStringField("name", NameValue.GetValue());
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