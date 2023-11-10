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

#include "SerialKey/Request/GetIssueJobRequest.h"

namespace Gs2::SerialKey::Request
{
    FGetIssueJobRequest::FGetIssueJobRequest():
        NamespaceNameValue(TOptional<FString>()),
        CampaignModelNameValue(TOptional<FString>()),
        IssueJobNameValue(TOptional<FString>())
    {
    }

    FGetIssueJobRequest::FGetIssueJobRequest(
        const FGetIssueJobRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        CampaignModelNameValue(From.CampaignModelNameValue),
        IssueJobNameValue(From.IssueJobNameValue)
    {
    }

    TSharedPtr<FGetIssueJobRequest> FGetIssueJobRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FGetIssueJobRequest> FGetIssueJobRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FGetIssueJobRequest> FGetIssueJobRequest::WithCampaignModelName(
        const TOptional<FString> CampaignModelName
    )
    {
        this->CampaignModelNameValue = CampaignModelName;
        return SharedThis(this);
    }

    TSharedPtr<FGetIssueJobRequest> FGetIssueJobRequest::WithIssueJobName(
        const TOptional<FString> IssueJobName
    )
    {
        this->IssueJobNameValue = IssueJobName;
        return SharedThis(this);
    }

    TOptional<FString> FGetIssueJobRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FGetIssueJobRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FGetIssueJobRequest::GetCampaignModelName() const
    {
        return CampaignModelNameValue;
    }

    TOptional<FString> FGetIssueJobRequest::GetIssueJobName() const
    {
        return IssueJobNameValue;
    }

    TSharedPtr<FGetIssueJobRequest> FGetIssueJobRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FGetIssueJobRequest>()
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
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FGetIssueJobRequest::ToJson() const
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
        return JsonRootObject;
    }
}