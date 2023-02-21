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

#include "Version/Request/DeleteVersionModelMasterRequest.h"

namespace Gs2::Version::Request
{
    FDeleteVersionModelMasterRequest::FDeleteVersionModelMasterRequest():
        NamespaceNameValue(TOptional<FString>()),
        VersionNameValue(TOptional<FString>())
    {
    }

    FDeleteVersionModelMasterRequest::FDeleteVersionModelMasterRequest(
        const FDeleteVersionModelMasterRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        VersionNameValue(From.VersionNameValue)
    {
    }

    TSharedPtr<FDeleteVersionModelMasterRequest> FDeleteVersionModelMasterRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FDeleteVersionModelMasterRequest> FDeleteVersionModelMasterRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FDeleteVersionModelMasterRequest> FDeleteVersionModelMasterRequest::WithVersionName(
        const TOptional<FString> VersionName
    )
    {
        this->VersionNameValue = VersionName;
        return SharedThis(this);
    }

    TOptional<FString> FDeleteVersionModelMasterRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FDeleteVersionModelMasterRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FDeleteVersionModelMasterRequest::GetVersionName() const
    {
        return VersionNameValue;
    }

    TSharedPtr<FDeleteVersionModelMasterRequest> FDeleteVersionModelMasterRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FDeleteVersionModelMasterRequest>()
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
            ->WithVersionName(Data->HasField("versionName") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("versionName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FDeleteVersionModelMasterRequest::ToJson() const
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
        return JsonRootObject;
    }
}