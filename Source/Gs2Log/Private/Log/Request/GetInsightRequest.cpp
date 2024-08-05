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

#include "Log/Request/GetInsightRequest.h"

namespace Gs2::Log::Request
{
    FGetInsightRequest::FGetInsightRequest():
        NamespaceNameValue(TOptional<FString>()),
        InsightNameValue(TOptional<FString>())
    {
    }

    FGetInsightRequest::FGetInsightRequest(
        const FGetInsightRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        InsightNameValue(From.InsightNameValue)
    {
    }

    TSharedPtr<FGetInsightRequest> FGetInsightRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FGetInsightRequest> FGetInsightRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FGetInsightRequest> FGetInsightRequest::WithInsightName(
        const TOptional<FString> InsightName
    )
    {
        this->InsightNameValue = InsightName;
        return SharedThis(this);
    }

    TOptional<FString> FGetInsightRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FGetInsightRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FGetInsightRequest::GetInsightName() const
    {
        return InsightNameValue;
    }

    TSharedPtr<FGetInsightRequest> FGetInsightRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FGetInsightRequest>()
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
            ->WithInsightName(Data->HasField(ANSI_TO_TCHAR("insightName")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("insightName"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FGetInsightRequest::ToJson() const
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
        if (InsightNameValue.IsSet())
        {
            JsonRootObject->SetStringField("insightName", InsightNameValue.GetValue());
        }
        return JsonRootObject;
    }
}