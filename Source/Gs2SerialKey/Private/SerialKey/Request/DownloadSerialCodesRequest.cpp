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

#include "SerialKey/Request/DownloadSerialCodesRequest.h"

namespace Gs2::SerialKey::Request
{
    FDownloadSerialCodesRequest::FDownloadSerialCodesRequest():
        NamespaceNameValue(TOptional<FString>()),
        CampaignModelNameValue(TOptional<FString>()),
        IssueJobNameValue(TOptional<FString>())
    {
    }

    FDownloadSerialCodesRequest::FDownloadSerialCodesRequest(
        const FDownloadSerialCodesRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        CampaignModelNameValue(From.CampaignModelNameValue),
        IssueJobNameValue(From.IssueJobNameValue)
    {
    }

    TSharedPtr<FDownloadSerialCodesRequest> FDownloadSerialCodesRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FDownloadSerialCodesRequest> FDownloadSerialCodesRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FDownloadSerialCodesRequest> FDownloadSerialCodesRequest::WithCampaignModelName(
        const TOptional<FString> CampaignModelName
    )
    {
        this->CampaignModelNameValue = CampaignModelName;
        return SharedThis(this);
    }

    TSharedPtr<FDownloadSerialCodesRequest> FDownloadSerialCodesRequest::WithIssueJobName(
        const TOptional<FString> IssueJobName
    )
    {
        this->IssueJobNameValue = IssueJobName;
        return SharedThis(this);
    }

    TOptional<FString> FDownloadSerialCodesRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FDownloadSerialCodesRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FDownloadSerialCodesRequest::GetCampaignModelName() const
    {
        return CampaignModelNameValue;
    }

    TOptional<FString> FDownloadSerialCodesRequest::GetIssueJobName() const
    {
        return IssueJobNameValue;
    }

    TSharedPtr<FDownloadSerialCodesRequest> FDownloadSerialCodesRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FDownloadSerialCodesRequest>()
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
            ->WithCampaignModelName(Data->HasField(ANSI_TO_TCHAR("campaignModelName")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("campaignModelName"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithIssueJobName(Data->HasField(ANSI_TO_TCHAR("issueJobName")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("issueJobName"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FDownloadSerialCodesRequest::ToJson() const
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