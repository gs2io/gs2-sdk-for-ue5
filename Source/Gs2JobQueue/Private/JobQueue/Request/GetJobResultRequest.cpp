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

#include "JobQueue/Request/GetJobResultRequest.h"

namespace Gs2::JobQueue::Request
{
    FGetJobResultRequest::FGetJobResultRequest():
        NamespaceNameValue(TOptional<FString>()),
        AccessTokenValue(TOptional<FString>()),
        JobNameValue(TOptional<FString>()),
        TryNumberValue(TOptional<int32>())
    {
    }

    FGetJobResultRequest::FGetJobResultRequest(
        const FGetJobResultRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        AccessTokenValue(From.AccessTokenValue),
        JobNameValue(From.JobNameValue),
        TryNumberValue(From.TryNumberValue)
    {
    }

    TSharedPtr<FGetJobResultRequest> FGetJobResultRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FGetJobResultRequest> FGetJobResultRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FGetJobResultRequest> FGetJobResultRequest::WithAccessToken(
        const TOptional<FString> AccessToken
    )
    {
        this->AccessTokenValue = AccessToken;
        return SharedThis(this);
    }

    TSharedPtr<FGetJobResultRequest> FGetJobResultRequest::WithJobName(
        const TOptional<FString> JobName
    )
    {
        this->JobNameValue = JobName;
        return SharedThis(this);
    }

    TSharedPtr<FGetJobResultRequest> FGetJobResultRequest::WithTryNumber(
        const TOptional<int32> TryNumber
    )
    {
        this->TryNumberValue = TryNumber;
        return SharedThis(this);
    }

    TOptional<FString> FGetJobResultRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FGetJobResultRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FGetJobResultRequest::GetAccessToken() const
    {
        return AccessTokenValue;
    }

    TOptional<FString> FGetJobResultRequest::GetJobName() const
    {
        return JobNameValue;
    }

    TOptional<int32> FGetJobResultRequest::GetTryNumber() const
    {
        return TryNumberValue;
    }

    FString FGetJobResultRequest::GetTryNumberString() const
    {
        if (!TryNumberValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), TryNumberValue.GetValue());
    }

    TSharedPtr<FGetJobResultRequest> FGetJobResultRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FGetJobResultRequest>()
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
            ->WithAccessToken(Data->HasField("xGs2AccessToken") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("xGs2AccessToken", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithJobName(Data->HasField("jobName") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("jobName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithTryNumber(Data->HasField("tryNumber") ? [Data]() -> TOptional<int32>
              {
                  int32 v;
                    if (Data->TryGetNumberField("tryNumber", v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int32>();
              }() : TOptional<int32>());
    }

    TSharedPtr<FJsonObject> FGetJobResultRequest::ToJson() const
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
        if (AccessTokenValue.IsSet())
        {
            JsonRootObject->SetStringField("xGs2AccessToken", AccessTokenValue.GetValue());
        }
        if (JobNameValue.IsSet())
        {
            JsonRootObject->SetStringField("jobName", JobNameValue.GetValue());
        }
        if (TryNumberValue.IsSet())
        {
            JsonRootObject->SetNumberField("tryNumber", TryNumberValue.GetValue());
        }
        return JsonRootObject;
    }
}