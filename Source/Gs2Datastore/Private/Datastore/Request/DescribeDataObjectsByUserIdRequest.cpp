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

#include "Datastore/Request/DescribeDataObjectsByUserIdRequest.h"

namespace Gs2::Datastore::Request
{
    FDescribeDataObjectsByUserIdRequest::FDescribeDataObjectsByUserIdRequest():
        NamespaceNameValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        StatusValue(TOptional<FString>()),
        PageTokenValue(TOptional<FString>()),
        LimitValue(TOptional<int32>())
    {
    }

    FDescribeDataObjectsByUserIdRequest::FDescribeDataObjectsByUserIdRequest(
        const FDescribeDataObjectsByUserIdRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        UserIdValue(From.UserIdValue),
        StatusValue(From.StatusValue),
        PageTokenValue(From.PageTokenValue),
        LimitValue(From.LimitValue)
    {
    }

    TSharedPtr<FDescribeDataObjectsByUserIdRequest> FDescribeDataObjectsByUserIdRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FDescribeDataObjectsByUserIdRequest> FDescribeDataObjectsByUserIdRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FDescribeDataObjectsByUserIdRequest> FDescribeDataObjectsByUserIdRequest::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FDescribeDataObjectsByUserIdRequest> FDescribeDataObjectsByUserIdRequest::WithStatus(
        const TOptional<FString> Status
    )
    {
        this->StatusValue = Status;
        return SharedThis(this);
    }

    TSharedPtr<FDescribeDataObjectsByUserIdRequest> FDescribeDataObjectsByUserIdRequest::WithPageToken(
        const TOptional<FString> PageToken
    )
    {
        this->PageTokenValue = PageToken;
        return SharedThis(this);
    }

    TSharedPtr<FDescribeDataObjectsByUserIdRequest> FDescribeDataObjectsByUserIdRequest::WithLimit(
        const TOptional<int32> Limit
    )
    {
        this->LimitValue = Limit;
        return SharedThis(this);
    }

    TOptional<FString> FDescribeDataObjectsByUserIdRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FDescribeDataObjectsByUserIdRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FDescribeDataObjectsByUserIdRequest::GetUserId() const
    {
        return UserIdValue;
    }

    TOptional<FString> FDescribeDataObjectsByUserIdRequest::GetStatus() const
    {
        return StatusValue;
    }

    TOptional<FString> FDescribeDataObjectsByUserIdRequest::GetPageToken() const
    {
        return PageTokenValue;
    }

    TOptional<int32> FDescribeDataObjectsByUserIdRequest::GetLimit() const
    {
        return LimitValue;
    }

    FString FDescribeDataObjectsByUserIdRequest::GetLimitString() const
    {
        if (!LimitValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%ld"), LimitValue.GetValue());
    }

    TSharedPtr<FDescribeDataObjectsByUserIdRequest> FDescribeDataObjectsByUserIdRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FDescribeDataObjectsByUserIdRequest>()
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
            ->WithUserId(Data->HasField("userId") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("userId", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithStatus(Data->HasField("status") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("status", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithPageToken(Data->HasField("pageToken") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("pageToken", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithLimit(Data->HasField("limit") ? [Data]() -> TOptional<int32>
              {
                  int32 v;
                    if (Data->TryGetNumberField("limit", v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int32>();
              }() : TOptional<int32>());
    }

    TSharedPtr<FJsonObject> FDescribeDataObjectsByUserIdRequest::ToJson() const
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
        if (UserIdValue.IsSet())
        {
            JsonRootObject->SetStringField("userId", UserIdValue.GetValue());
        }
        if (StatusValue.IsSet())
        {
            JsonRootObject->SetStringField("status", StatusValue.GetValue());
        }
        if (PageTokenValue.IsSet())
        {
            JsonRootObject->SetStringField("pageToken", PageTokenValue.GetValue());
        }
        if (LimitValue.IsSet())
        {
            JsonRootObject->SetNumberField("limit", LimitValue.GetValue());
        }
        return JsonRootObject;
    }
}