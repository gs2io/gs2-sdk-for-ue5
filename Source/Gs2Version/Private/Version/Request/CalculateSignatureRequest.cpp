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

#include "Version/Request/CalculateSignatureRequest.h"

namespace Gs2::Version::Request
{
    FCalculateSignatureRequest::FCalculateSignatureRequest():
        NamespaceNameValue(TOptional<FString>()),
        VersionNameValue(TOptional<FString>()),
        VersionValue(nullptr)
    {
    }

    FCalculateSignatureRequest::FCalculateSignatureRequest(
        const FCalculateSignatureRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        VersionNameValue(From.VersionNameValue),
        VersionValue(From.VersionValue)
    {
    }

    TSharedPtr<FCalculateSignatureRequest> FCalculateSignatureRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FCalculateSignatureRequest> FCalculateSignatureRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FCalculateSignatureRequest> FCalculateSignatureRequest::WithVersionName(
        const TOptional<FString> VersionName
    )
    {
        this->VersionNameValue = VersionName;
        return SharedThis(this);
    }

    TSharedPtr<FCalculateSignatureRequest> FCalculateSignatureRequest::WithVersion(
        const TSharedPtr<Model::FVersion> Version
    )
    {
        this->VersionValue = Version;
        return SharedThis(this);
    }

    TOptional<FString> FCalculateSignatureRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FCalculateSignatureRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FCalculateSignatureRequest::GetVersionName() const
    {
        return VersionNameValue;
    }

    TSharedPtr<Model::FVersion> FCalculateSignatureRequest::GetVersion() const
    {
        if (!VersionValue.IsValid())
        {
            return nullptr;
        }
        return VersionValue;
    }

    TSharedPtr<FCalculateSignatureRequest> FCalculateSignatureRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FCalculateSignatureRequest>()
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
            ->WithVersionName(Data->HasField(ANSI_TO_TCHAR("versionName")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("versionName"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
          ->WithVersion(Data->HasField(ANSI_TO_TCHAR("version")) ? [Data]() -> Model::FVersionPtr
              {
                  if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("version")))
                  {
                      return nullptr;
                  }
                  return Model::FVersion::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("version")));
              }() : nullptr);
    }

    TSharedPtr<FJsonObject> FCalculateSignatureRequest::ToJson() const
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
        if (VersionNameValue.IsSet())
        {
            JsonRootObject->SetStringField("versionName", VersionNameValue.GetValue());
        }
        if (VersionValue != nullptr && VersionValue.IsValid())
        {
            JsonRootObject->SetObjectField("version", VersionValue->ToJson());
        }
        return JsonRootObject;
    }
}