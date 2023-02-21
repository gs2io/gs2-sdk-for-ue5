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

#include "Showcase/Request/GetShowcaseMasterRequest.h"

namespace Gs2::Showcase::Request
{
    FGetShowcaseMasterRequest::FGetShowcaseMasterRequest():
        NamespaceNameValue(TOptional<FString>()),
        ShowcaseNameValue(TOptional<FString>())
    {
    }

    FGetShowcaseMasterRequest::FGetShowcaseMasterRequest(
        const FGetShowcaseMasterRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        ShowcaseNameValue(From.ShowcaseNameValue)
    {
    }

    TSharedPtr<FGetShowcaseMasterRequest> FGetShowcaseMasterRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FGetShowcaseMasterRequest> FGetShowcaseMasterRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FGetShowcaseMasterRequest> FGetShowcaseMasterRequest::WithShowcaseName(
        const TOptional<FString> ShowcaseName
    )
    {
        this->ShowcaseNameValue = ShowcaseName;
        return SharedThis(this);
    }

    TOptional<FString> FGetShowcaseMasterRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FGetShowcaseMasterRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FGetShowcaseMasterRequest::GetShowcaseName() const
    {
        return ShowcaseNameValue;
    }

    TSharedPtr<FGetShowcaseMasterRequest> FGetShowcaseMasterRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FGetShowcaseMasterRequest>()
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
            ->WithShowcaseName(Data->HasField("showcaseName") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("showcaseName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FGetShowcaseMasterRequest::ToJson() const
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
        if (ShowcaseNameValue.IsSet())
        {
            JsonRootObject->SetStringField("showcaseName", ShowcaseNameValue.GetValue());
        }
        return JsonRootObject;
    }
}