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

#include "Identifier/Request/DescribeIdentifiersRequest.h"

namespace Gs2::Identifier::Request
{
    FDescribeIdentifiersRequest::FDescribeIdentifiersRequest():
        UserNameValue(TOptional<FString>()),
        PageTokenValue(TOptional<FString>()),
        LimitValue(TOptional<int32>())
    {
    }

    FDescribeIdentifiersRequest::FDescribeIdentifiersRequest(
        const FDescribeIdentifiersRequest& From
    ):
        UserNameValue(From.UserNameValue),
        PageTokenValue(From.PageTokenValue),
        LimitValue(From.LimitValue)
    {
    }

    TSharedPtr<FDescribeIdentifiersRequest> FDescribeIdentifiersRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FDescribeIdentifiersRequest> FDescribeIdentifiersRequest::WithUserName(
        const TOptional<FString> UserName
    )
    {
        this->UserNameValue = UserName;
        return SharedThis(this);
    }

    TSharedPtr<FDescribeIdentifiersRequest> FDescribeIdentifiersRequest::WithPageToken(
        const TOptional<FString> PageToken
    )
    {
        this->PageTokenValue = PageToken;
        return SharedThis(this);
    }

    TSharedPtr<FDescribeIdentifiersRequest> FDescribeIdentifiersRequest::WithLimit(
        const TOptional<int32> Limit
    )
    {
        this->LimitValue = Limit;
        return SharedThis(this);
    }

    TOptional<FString> FDescribeIdentifiersRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FDescribeIdentifiersRequest::GetUserName() const
    {
        return UserNameValue;
    }

    TOptional<FString> FDescribeIdentifiersRequest::GetPageToken() const
    {
        return PageTokenValue;
    }

    TOptional<int32> FDescribeIdentifiersRequest::GetLimit() const
    {
        return LimitValue;
    }

    FString FDescribeIdentifiersRequest::GetLimitString() const
    {
        if (!LimitValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%ld"), LimitValue.GetValue());
    }

    TSharedPtr<FDescribeIdentifiersRequest> FDescribeIdentifiersRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FDescribeIdentifiersRequest>()
            ->WithContextStack(Data->HasField("contextStack") ? TOptional<FString>(Data->GetStringField("contextStack")) : TOptional<FString>())
            ->WithUserName(Data->HasField("userName") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("userName", v))
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

    TSharedPtr<FJsonObject> FDescribeIdentifiersRequest::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ContextStackValue.IsSet())
        {
            JsonRootObject->SetStringField("contextStack", ContextStackValue.GetValue());
        }
        if (UserNameValue.IsSet())
        {
            JsonRootObject->SetStringField("userName", UserNameValue.GetValue());
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