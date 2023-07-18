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

#include "Showcase/Request/DescribeRandomDisplayItemsRequest.h"

namespace Gs2::Showcase::Request
{
    FDescribeRandomDisplayItemsRequest::FDescribeRandomDisplayItemsRequest():
        NamespaceNameValue(TOptional<FString>()),
        ShowcaseNameValue(TOptional<FString>()),
        AccessTokenValue(TOptional<FString>())
    {
    }

    FDescribeRandomDisplayItemsRequest::FDescribeRandomDisplayItemsRequest(
        const FDescribeRandomDisplayItemsRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        ShowcaseNameValue(From.ShowcaseNameValue),
        AccessTokenValue(From.AccessTokenValue)
    {
    }

    TSharedPtr<FDescribeRandomDisplayItemsRequest> FDescribeRandomDisplayItemsRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FDescribeRandomDisplayItemsRequest> FDescribeRandomDisplayItemsRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FDescribeRandomDisplayItemsRequest> FDescribeRandomDisplayItemsRequest::WithShowcaseName(
        const TOptional<FString> ShowcaseName
    )
    {
        this->ShowcaseNameValue = ShowcaseName;
        return SharedThis(this);
    }

    TSharedPtr<FDescribeRandomDisplayItemsRequest> FDescribeRandomDisplayItemsRequest::WithAccessToken(
        const TOptional<FString> AccessToken
    )
    {
        this->AccessTokenValue = AccessToken;
        return SharedThis(this);
    }

    TOptional<FString> FDescribeRandomDisplayItemsRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FDescribeRandomDisplayItemsRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FDescribeRandomDisplayItemsRequest::GetShowcaseName() const
    {
        return ShowcaseNameValue;
    }

    TOptional<FString> FDescribeRandomDisplayItemsRequest::GetAccessToken() const
    {
        return AccessTokenValue;
    }

    TSharedPtr<FDescribeRandomDisplayItemsRequest> FDescribeRandomDisplayItemsRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FDescribeRandomDisplayItemsRequest>()
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
              }() : TOptional<FString>())
            ->WithAccessToken(Data->HasField("xGs2AccessToken") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("xGs2AccessToken", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FDescribeRandomDisplayItemsRequest::ToJson() const
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
        if (AccessTokenValue.IsSet())
        {
            JsonRootObject->SetStringField("xGs2AccessToken", AccessTokenValue.GetValue());
        }
        return JsonRootObject;
    }
}