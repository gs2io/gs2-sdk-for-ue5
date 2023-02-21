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

#include "Formation/Request/GetPropertyFormRequest.h"

namespace Gs2::Formation::Request
{
    FGetPropertyFormRequest::FGetPropertyFormRequest():
        NamespaceNameValue(TOptional<FString>()),
        AccessTokenValue(TOptional<FString>()),
        FormModelNameValue(TOptional<FString>()),
        PropertyIdValue(TOptional<FString>())
    {
    }

    FGetPropertyFormRequest::FGetPropertyFormRequest(
        const FGetPropertyFormRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        AccessTokenValue(From.AccessTokenValue),
        FormModelNameValue(From.FormModelNameValue),
        PropertyIdValue(From.PropertyIdValue)
    {
    }

    TSharedPtr<FGetPropertyFormRequest> FGetPropertyFormRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FGetPropertyFormRequest> FGetPropertyFormRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FGetPropertyFormRequest> FGetPropertyFormRequest::WithAccessToken(
        const TOptional<FString> AccessToken
    )
    {
        this->AccessTokenValue = AccessToken;
        return SharedThis(this);
    }

    TSharedPtr<FGetPropertyFormRequest> FGetPropertyFormRequest::WithFormModelName(
        const TOptional<FString> FormModelName
    )
    {
        this->FormModelNameValue = FormModelName;
        return SharedThis(this);
    }

    TSharedPtr<FGetPropertyFormRequest> FGetPropertyFormRequest::WithPropertyId(
        const TOptional<FString> PropertyId
    )
    {
        this->PropertyIdValue = PropertyId;
        return SharedThis(this);
    }

    TOptional<FString> FGetPropertyFormRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FGetPropertyFormRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FGetPropertyFormRequest::GetAccessToken() const
    {
        return AccessTokenValue;
    }

    TOptional<FString> FGetPropertyFormRequest::GetFormModelName() const
    {
        return FormModelNameValue;
    }

    TOptional<FString> FGetPropertyFormRequest::GetPropertyId() const
    {
        return PropertyIdValue;
    }

    TSharedPtr<FGetPropertyFormRequest> FGetPropertyFormRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FGetPropertyFormRequest>()
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
            ->WithFormModelName(Data->HasField("formModelName") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("formModelName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithPropertyId(Data->HasField("propertyId") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("propertyId", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FGetPropertyFormRequest::ToJson() const
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
        if (FormModelNameValue.IsSet())
        {
            JsonRootObject->SetStringField("formModelName", FormModelNameValue.GetValue());
        }
        if (PropertyIdValue.IsSet())
        {
            JsonRootObject->SetStringField("propertyId", PropertyIdValue.GetValue());
        }
        return JsonRootObject;
    }
}