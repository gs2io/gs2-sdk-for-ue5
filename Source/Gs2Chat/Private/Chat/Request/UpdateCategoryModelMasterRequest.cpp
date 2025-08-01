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

#include "Chat/Request/UpdateCategoryModelMasterRequest.h"

namespace Gs2::Chat::Request
{
    FUpdateCategoryModelMasterRequest::FUpdateCategoryModelMasterRequest():
        NamespaceNameValue(TOptional<FString>()),
        CategoryValue(TOptional<int32>()),
        DescriptionValue(TOptional<FString>()),
        RejectAccessTokenPostValue(TOptional<FString>())
    {
    }

    FUpdateCategoryModelMasterRequest::FUpdateCategoryModelMasterRequest(
        const FUpdateCategoryModelMasterRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        CategoryValue(From.CategoryValue),
        DescriptionValue(From.DescriptionValue),
        RejectAccessTokenPostValue(From.RejectAccessTokenPostValue)
    {
    }

    TSharedPtr<FUpdateCategoryModelMasterRequest> FUpdateCategoryModelMasterRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateCategoryModelMasterRequest> FUpdateCategoryModelMasterRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateCategoryModelMasterRequest> FUpdateCategoryModelMasterRequest::WithCategory(
        const TOptional<int32> Category
    )
    {
        this->CategoryValue = Category;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateCategoryModelMasterRequest> FUpdateCategoryModelMasterRequest::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateCategoryModelMasterRequest> FUpdateCategoryModelMasterRequest::WithRejectAccessTokenPost(
        const TOptional<FString> RejectAccessTokenPost
    )
    {
        this->RejectAccessTokenPostValue = RejectAccessTokenPost;
        return SharedThis(this);
    }

    TOptional<FString> FUpdateCategoryModelMasterRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FUpdateCategoryModelMasterRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<int32> FUpdateCategoryModelMasterRequest::GetCategory() const
    {
        return CategoryValue;
    }

    FString FUpdateCategoryModelMasterRequest::GetCategoryString() const
    {
        if (!CategoryValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), CategoryValue.GetValue());
    }

    TOptional<FString> FUpdateCategoryModelMasterRequest::GetDescription() const
    {
        return DescriptionValue;
    }

    TOptional<FString> FUpdateCategoryModelMasterRequest::GetRejectAccessTokenPost() const
    {
        return RejectAccessTokenPostValue;
    }

    TSharedPtr<FUpdateCategoryModelMasterRequest> FUpdateCategoryModelMasterRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FUpdateCategoryModelMasterRequest>()
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
            ->WithCategory(Data->HasField(ANSI_TO_TCHAR("category")) ? [Data]() -> TOptional<int32>
              {
                  int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("category"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int32>();
              }() : TOptional<int32>())
            ->WithDescription(Data->HasField(ANSI_TO_TCHAR("description")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("description"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithRejectAccessTokenPost(Data->HasField(ANSI_TO_TCHAR("rejectAccessTokenPost")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("rejectAccessTokenPost"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FUpdateCategoryModelMasterRequest::ToJson() const
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
        if (CategoryValue.IsSet())
        {
            JsonRootObject->SetNumberField("category", CategoryValue.GetValue());
        }
        if (DescriptionValue.IsSet())
        {
            JsonRootObject->SetStringField("description", DescriptionValue.GetValue());
        }
        if (RejectAccessTokenPostValue.IsSet())
        {
            JsonRootObject->SetStringField("rejectAccessTokenPost", RejectAccessTokenPostValue.GetValue());
        }
        return JsonRootObject;
    }
}