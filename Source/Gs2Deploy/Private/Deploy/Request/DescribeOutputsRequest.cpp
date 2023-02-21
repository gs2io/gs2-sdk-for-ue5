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

#include "Deploy/Request/DescribeOutputsRequest.h"

namespace Gs2::Deploy::Request
{
    FDescribeOutputsRequest::FDescribeOutputsRequest():
        StackNameValue(TOptional<FString>()),
        PageTokenValue(TOptional<FString>()),
        LimitValue(TOptional<int32>())
    {
    }

    FDescribeOutputsRequest::FDescribeOutputsRequest(
        const FDescribeOutputsRequest& From
    ):
        StackNameValue(From.StackNameValue),
        PageTokenValue(From.PageTokenValue),
        LimitValue(From.LimitValue)
    {
    }

    TSharedPtr<FDescribeOutputsRequest> FDescribeOutputsRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FDescribeOutputsRequest> FDescribeOutputsRequest::WithStackName(
        const TOptional<FString> StackName
    )
    {
        this->StackNameValue = StackName;
        return SharedThis(this);
    }

    TSharedPtr<FDescribeOutputsRequest> FDescribeOutputsRequest::WithPageToken(
        const TOptional<FString> PageToken
    )
    {
        this->PageTokenValue = PageToken;
        return SharedThis(this);
    }

    TSharedPtr<FDescribeOutputsRequest> FDescribeOutputsRequest::WithLimit(
        const TOptional<int32> Limit
    )
    {
        this->LimitValue = Limit;
        return SharedThis(this);
    }

    TOptional<FString> FDescribeOutputsRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FDescribeOutputsRequest::GetStackName() const
    {
        return StackNameValue;
    }

    TOptional<FString> FDescribeOutputsRequest::GetPageToken() const
    {
        return PageTokenValue;
    }

    TOptional<int32> FDescribeOutputsRequest::GetLimit() const
    {
        return LimitValue;
    }

    FString FDescribeOutputsRequest::GetLimitString() const
    {
        if (!LimitValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%ld"), LimitValue.GetValue());
    }

    TSharedPtr<FDescribeOutputsRequest> FDescribeOutputsRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FDescribeOutputsRequest>()
            ->WithContextStack(Data->HasField("contextStack") ? TOptional<FString>(Data->GetStringField("contextStack")) : TOptional<FString>())
            ->WithStackName(Data->HasField("stackName") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("stackName", v))
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

    TSharedPtr<FJsonObject> FDescribeOutputsRequest::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ContextStackValue.IsSet())
        {
            JsonRootObject->SetStringField("contextStack", ContextStackValue.GetValue());
        }
        if (StackNameValue.IsSet())
        {
            JsonRootObject->SetStringField("stackName", StackNameValue.GetValue());
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