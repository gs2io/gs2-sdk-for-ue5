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

#include "SerialKey/Request/IssueRequest.h"

namespace Gs2::SerialKey::Request
{
    FIssueRequest::FIssueRequest():
        NamespaceNameValue(TOptional<FString>()),
        CampaignModelNameValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        IssueRequestCountValue(TOptional<int32>())
    {
    }

    FIssueRequest::FIssueRequest(
        const FIssueRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        CampaignModelNameValue(From.CampaignModelNameValue),
        MetadataValue(From.MetadataValue),
        IssueRequestCountValue(From.IssueRequestCountValue)
    {
    }

    TSharedPtr<FIssueRequest> FIssueRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FIssueRequest> FIssueRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FIssueRequest> FIssueRequest::WithCampaignModelName(
        const TOptional<FString> CampaignModelName
    )
    {
        this->CampaignModelNameValue = CampaignModelName;
        return SharedThis(this);
    }

    TSharedPtr<FIssueRequest> FIssueRequest::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FIssueRequest> FIssueRequest::WithIssueRequestCount(
        const TOptional<int32> IssueRequestCount
    )
    {
        this->IssueRequestCountValue = IssueRequestCount;
        return SharedThis(this);
    }

    TOptional<FString> FIssueRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FIssueRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FIssueRequest::GetCampaignModelName() const
    {
        return CampaignModelNameValue;
    }

    TOptional<FString> FIssueRequest::GetMetadata() const
    {
        return MetadataValue;
    }

    TOptional<int32> FIssueRequest::GetIssueRequestCount() const
    {
        return IssueRequestCountValue;
    }

    FString FIssueRequest::GetIssueRequestCountString() const
    {
        if (!IssueRequestCountValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), IssueRequestCountValue.GetValue());
    }

    TSharedPtr<FIssueRequest> FIssueRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FIssueRequest>()
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
            ->WithMetadata(Data->HasField("metadata") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("metadata", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithIssueRequestCount(Data->HasField("issueRequestCount") ? [Data]() -> TOptional<int32>
              {
                  int32 v;
                    if (Data->TryGetNumberField("issueRequestCount", v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int32>();
              }() : TOptional<int32>());
    }

    TSharedPtr<FJsonObject> FIssueRequest::ToJson() const
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
        if (MetadataValue.IsSet())
        {
            JsonRootObject->SetStringField("metadata", MetadataValue.GetValue());
        }
        if (IssueRequestCountValue.IsSet())
        {
            JsonRootObject->SetNumberField("issueRequestCount", IssueRequestCountValue.GetValue());
        }
        return JsonRootObject;
    }
}