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

#include "Ranking/Request/DescribeSubscribesByCategoryNameAndUserIdRequest.h"

namespace Gs2::Ranking::Request
{
    FDescribeSubscribesByCategoryNameAndUserIdRequest::FDescribeSubscribesByCategoryNameAndUserIdRequest():
        NamespaceNameValue(TOptional<FString>()),
        CategoryNameValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>())
    {
    }

    FDescribeSubscribesByCategoryNameAndUserIdRequest::FDescribeSubscribesByCategoryNameAndUserIdRequest(
        const FDescribeSubscribesByCategoryNameAndUserIdRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        CategoryNameValue(From.CategoryNameValue),
        UserIdValue(From.UserIdValue)
    {
    }

    TSharedPtr<FDescribeSubscribesByCategoryNameAndUserIdRequest> FDescribeSubscribesByCategoryNameAndUserIdRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FDescribeSubscribesByCategoryNameAndUserIdRequest> FDescribeSubscribesByCategoryNameAndUserIdRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FDescribeSubscribesByCategoryNameAndUserIdRequest> FDescribeSubscribesByCategoryNameAndUserIdRequest::WithCategoryName(
        const TOptional<FString> CategoryName
    )
    {
        this->CategoryNameValue = CategoryName;
        return SharedThis(this);
    }

    TSharedPtr<FDescribeSubscribesByCategoryNameAndUserIdRequest> FDescribeSubscribesByCategoryNameAndUserIdRequest::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TOptional<FString> FDescribeSubscribesByCategoryNameAndUserIdRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FDescribeSubscribesByCategoryNameAndUserIdRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FDescribeSubscribesByCategoryNameAndUserIdRequest::GetCategoryName() const
    {
        return CategoryNameValue;
    }

    TOptional<FString> FDescribeSubscribesByCategoryNameAndUserIdRequest::GetUserId() const
    {
        return UserIdValue;
    }

    TSharedPtr<FDescribeSubscribesByCategoryNameAndUserIdRequest> FDescribeSubscribesByCategoryNameAndUserIdRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FDescribeSubscribesByCategoryNameAndUserIdRequest>()
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
            ->WithCategoryName(Data->HasField("categoryName") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("categoryName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithUserId(Data->HasField("userId") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("userId", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FDescribeSubscribesByCategoryNameAndUserIdRequest::ToJson() const
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
        if (CategoryNameValue.IsSet())
        {
            JsonRootObject->SetStringField("categoryName", CategoryNameValue.GetValue());
        }
        if (UserIdValue.IsSet())
        {
            JsonRootObject->SetStringField("userId", UserIdValue.GetValue());
        }
        return JsonRootObject;
    }
}