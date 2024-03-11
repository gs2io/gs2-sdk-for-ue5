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

#include "Ranking/Request/DescribeRankingssByUserIdRequest.h"

namespace Gs2::Ranking::Request
{
    FDescribeRankingssByUserIdRequest::FDescribeRankingssByUserIdRequest():
        NamespaceNameValue(TOptional<FString>()),
        CategoryNameValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        AdditionalScopeNameValue(TOptional<FString>()),
        StartIndexValue(TOptional<int64>()),
        PageTokenValue(TOptional<FString>()),
        LimitValue(TOptional<int32>()),
        TimeOffsetTokenValue(TOptional<FString>())
    {
    }

    FDescribeRankingssByUserIdRequest::FDescribeRankingssByUserIdRequest(
        const FDescribeRankingssByUserIdRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        CategoryNameValue(From.CategoryNameValue),
        UserIdValue(From.UserIdValue),
        AdditionalScopeNameValue(From.AdditionalScopeNameValue),
        StartIndexValue(From.StartIndexValue),
        PageTokenValue(From.PageTokenValue),
        LimitValue(From.LimitValue),
        TimeOffsetTokenValue(From.TimeOffsetTokenValue)
    {
    }

    TSharedPtr<FDescribeRankingssByUserIdRequest> FDescribeRankingssByUserIdRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FDescribeRankingssByUserIdRequest> FDescribeRankingssByUserIdRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FDescribeRankingssByUserIdRequest> FDescribeRankingssByUserIdRequest::WithCategoryName(
        const TOptional<FString> CategoryName
    )
    {
        this->CategoryNameValue = CategoryName;
        return SharedThis(this);
    }

    TSharedPtr<FDescribeRankingssByUserIdRequest> FDescribeRankingssByUserIdRequest::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FDescribeRankingssByUserIdRequest> FDescribeRankingssByUserIdRequest::WithAdditionalScopeName(
        const TOptional<FString> AdditionalScopeName
    )
    {
        this->AdditionalScopeNameValue = AdditionalScopeName;
        return SharedThis(this);
    }

    TSharedPtr<FDescribeRankingssByUserIdRequest> FDescribeRankingssByUserIdRequest::WithStartIndex(
        const TOptional<int64> StartIndex
    )
    {
        this->StartIndexValue = StartIndex;
        return SharedThis(this);
    }

    TSharedPtr<FDescribeRankingssByUserIdRequest> FDescribeRankingssByUserIdRequest::WithPageToken(
        const TOptional<FString> PageToken
    )
    {
        this->PageTokenValue = PageToken;
        return SharedThis(this);
    }

    TSharedPtr<FDescribeRankingssByUserIdRequest> FDescribeRankingssByUserIdRequest::WithLimit(
        const TOptional<int32> Limit
    )
    {
        this->LimitValue = Limit;
        return SharedThis(this);
    }

    TSharedPtr<FDescribeRankingssByUserIdRequest> FDescribeRankingssByUserIdRequest::WithTimeOffsetToken(
        const TOptional<FString> TimeOffsetToken
    )
    {
        this->TimeOffsetTokenValue = TimeOffsetToken;
        return SharedThis(this);
    }

    TOptional<FString> FDescribeRankingssByUserIdRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FDescribeRankingssByUserIdRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FDescribeRankingssByUserIdRequest::GetCategoryName() const
    {
        return CategoryNameValue;
    }

    TOptional<FString> FDescribeRankingssByUserIdRequest::GetUserId() const
    {
        return UserIdValue;
    }

    TOptional<FString> FDescribeRankingssByUserIdRequest::GetAdditionalScopeName() const
    {
        return AdditionalScopeNameValue;
    }

    TOptional<int64> FDescribeRankingssByUserIdRequest::GetStartIndex() const
    {
        return StartIndexValue;
    }

    FString FDescribeRankingssByUserIdRequest::GetStartIndexString() const
    {
        if (!StartIndexValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), StartIndexValue.GetValue());
    }

    TOptional<FString> FDescribeRankingssByUserIdRequest::GetPageToken() const
    {
        return PageTokenValue;
    }

    TOptional<int32> FDescribeRankingssByUserIdRequest::GetLimit() const
    {
        return LimitValue;
    }

    FString FDescribeRankingssByUserIdRequest::GetLimitString() const
    {
        if (!LimitValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), LimitValue.GetValue());
    }

    TOptional<FString> FDescribeRankingssByUserIdRequest::GetTimeOffsetToken() const
    {
        return TimeOffsetTokenValue;
    }

    TSharedPtr<FDescribeRankingssByUserIdRequest> FDescribeRankingssByUserIdRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FDescribeRankingssByUserIdRequest>()
            ->WithContextStack(Data->HasField("contextStack") ? TOptional<FString>(Data->GetStringField("contextStack")) : TOptional<FString>())
            ->WithNamespaceName(Data->HasField("namespaceName") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("namespaceName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithCategoryName(Data->HasField("categoryName") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("categoryName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithUserId(Data->HasField("userId") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("userId", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithAdditionalScopeName(Data->HasField("additionalScopeName") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("additionalScopeName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithStartIndex(Data->HasField("startIndex") ? [Data]() -> TOptional<int64>
              {
                  int64 v;
                    if (Data->TryGetNumberField("startIndex", v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int64>();
              }() : TOptional<int64>())
            ->WithPageToken(Data->HasField("pageToken") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
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
              }() : TOptional<int32>())
            ->WithTimeOffsetToken(Data->HasField("timeOffsetToken") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("timeOffsetToken", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FDescribeRankingssByUserIdRequest::ToJson() const
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
        if (AdditionalScopeNameValue.IsSet())
        {
            JsonRootObject->SetStringField("additionalScopeName", AdditionalScopeNameValue.GetValue());
        }
        if (StartIndexValue.IsSet())
        {
            JsonRootObject->SetStringField("startIndex", FString::Printf(TEXT("%lld"), StartIndexValue.GetValue()));
        }
        if (PageTokenValue.IsSet())
        {
            JsonRootObject->SetStringField("pageToken", PageTokenValue.GetValue());
        }
        if (LimitValue.IsSet())
        {
            JsonRootObject->SetNumberField("limit", LimitValue.GetValue());
        }
        if (TimeOffsetTokenValue.IsSet())
        {
            JsonRootObject->SetStringField("timeOffsetToken", TimeOffsetTokenValue.GetValue());
        }
        return JsonRootObject;
    }
}