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

#include "JobQueue/Request/GetJobByUserIdRequest.h"

namespace Gs2::JobQueue::Request
{
    FGetJobByUserIdRequest::FGetJobByUserIdRequest():
        NamespaceNameValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        JobNameValue(TOptional<FString>()),
        TimeOffsetTokenValue(TOptional<FString>())
    {
    }

    FGetJobByUserIdRequest::FGetJobByUserIdRequest(
        const FGetJobByUserIdRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        UserIdValue(From.UserIdValue),
        JobNameValue(From.JobNameValue),
        TimeOffsetTokenValue(From.TimeOffsetTokenValue)
    {
    }

    TSharedPtr<FGetJobByUserIdRequest> FGetJobByUserIdRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FGetJobByUserIdRequest> FGetJobByUserIdRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FGetJobByUserIdRequest> FGetJobByUserIdRequest::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FGetJobByUserIdRequest> FGetJobByUserIdRequest::WithJobName(
        const TOptional<FString> JobName
    )
    {
        this->JobNameValue = JobName;
        return SharedThis(this);
    }

    TSharedPtr<FGetJobByUserIdRequest> FGetJobByUserIdRequest::WithTimeOffsetToken(
        const TOptional<FString> TimeOffsetToken
    )
    {
        this->TimeOffsetTokenValue = TimeOffsetToken;
        return SharedThis(this);
    }

    TOptional<FString> FGetJobByUserIdRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FGetJobByUserIdRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FGetJobByUserIdRequest::GetUserId() const
    {
        return UserIdValue;
    }

    TOptional<FString> FGetJobByUserIdRequest::GetJobName() const
    {
        return JobNameValue;
    }

    TOptional<FString> FGetJobByUserIdRequest::GetTimeOffsetToken() const
    {
        return TimeOffsetTokenValue;
    }

    TSharedPtr<FGetJobByUserIdRequest> FGetJobByUserIdRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FGetJobByUserIdRequest>()
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
            ->WithUserId(Data->HasField(ANSI_TO_TCHAR("userId")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("userId"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithJobName(Data->HasField(ANSI_TO_TCHAR("jobName")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("jobName"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithTimeOffsetToken(Data->HasField(ANSI_TO_TCHAR("timeOffsetToken")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("timeOffsetToken"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FGetJobByUserIdRequest::ToJson() const
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
        if (JobNameValue.IsSet())
        {
            JsonRootObject->SetStringField("jobName", JobNameValue.GetValue());
        }
        if (TimeOffsetTokenValue.IsSet())
        {
            JsonRootObject->SetStringField("timeOffsetToken", TimeOffsetTokenValue.GetValue());
        }
        return JsonRootObject;
    }
}