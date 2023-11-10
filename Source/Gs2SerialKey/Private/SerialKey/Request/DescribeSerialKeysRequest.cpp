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

#include "SerialKey/Request/DescribeSerialKeysRequest.h"

namespace Gs2::SerialKey::Request
{
    FDescribeSerialKeysRequest::FDescribeSerialKeysRequest():
        NamespaceNameValue(TOptional<FString>()),
        CampaignModelNameValue(TOptional<FString>()),
        IssueJobNameValue(TOptional<FString>()),
        PageTokenValue(TOptional<FString>()),
        LimitValue(TOptional<int32>())
    {
    }

    FDescribeSerialKeysRequest::FDescribeSerialKeysRequest(
        const FDescribeSerialKeysRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        CampaignModelNameValue(From.CampaignModelNameValue),
        IssueJobNameValue(From.IssueJobNameValue),
        PageTokenValue(From.PageTokenValue),
        LimitValue(From.LimitValue)
    {
    }

    TSharedPtr<FDescribeSerialKeysRequest> FDescribeSerialKeysRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FDescribeSerialKeysRequest> FDescribeSerialKeysRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FDescribeSerialKeysRequest> FDescribeSerialKeysRequest::WithCampaignModelName(
        const TOptional<FString> CampaignModelName
    )
    {
        this->CampaignModelNameValue = CampaignModelName;
        return SharedThis(this);
    }

    TSharedPtr<FDescribeSerialKeysRequest> FDescribeSerialKeysRequest::WithIssueJobName(
        const TOptional<FString> IssueJobName
    )
    {
        this->IssueJobNameValue = IssueJobName;
        return SharedThis(this);
    }

    TSharedPtr<FDescribeSerialKeysRequest> FDescribeSerialKeysRequest::WithPageToken(
        const TOptional<FString> PageToken
    )
    {
        this->PageTokenValue = PageToken;
        return SharedThis(this);
    }

    TSharedPtr<FDescribeSerialKeysRequest> FDescribeSerialKeysRequest::WithLimit(
        const TOptional<int32> Limit
    )
    {
        this->LimitValue = Limit;
        return SharedThis(this);
    }

    TOptional<FString> FDescribeSerialKeysRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FDescribeSerialKeysRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FDescribeSerialKeysRequest::GetCampaignModelName() const
    {
        return CampaignModelNameValue;
    }

    TOptional<FString> FDescribeSerialKeysRequest::GetIssueJobName() const
    {
        return IssueJobNameValue;
    }

    TOptional<FString> FDescribeSerialKeysRequest::GetPageToken() const
    {
        return PageTokenValue;
    }

    TOptional<int32> FDescribeSerialKeysRequest::GetLimit() const
    {
        return LimitValue;
    }

    FString FDescribeSerialKeysRequest::GetLimitString() const
    {
        if (!LimitValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), LimitValue.GetValue());
    }

    TSharedPtr<FDescribeSerialKeysRequest> FDescribeSerialKeysRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FDescribeSerialKeysRequest>()
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
            ->WithCampaignModelName(Data->HasField("campaignModelName") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("campaignModelName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithIssueJobName(Data->HasField("issueJobName") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("issueJobName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
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
              }() : TOptional<int32>());
    }

    TSharedPtr<FJsonObject> FDescribeSerialKeysRequest::ToJson() const
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
        if (CampaignModelNameValue.IsSet())
        {
            JsonRootObject->SetStringField("campaignModelName", CampaignModelNameValue.GetValue());
        }
        if (IssueJobNameValue.IsSet())
        {
            JsonRootObject->SetStringField("issueJobName", IssueJobNameValue.GetValue());
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