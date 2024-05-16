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

#include "Identifier/Request/AttachSecurityPolicyRequest.h"

namespace Gs2::Identifier::Request
{
    FAttachSecurityPolicyRequest::FAttachSecurityPolicyRequest():
        UserNameValue(TOptional<FString>()),
        SecurityPolicyIdValue(TOptional<FString>())
    {
    }

    FAttachSecurityPolicyRequest::FAttachSecurityPolicyRequest(
        const FAttachSecurityPolicyRequest& From
    ):
        UserNameValue(From.UserNameValue),
        SecurityPolicyIdValue(From.SecurityPolicyIdValue)
    {
    }

    TSharedPtr<FAttachSecurityPolicyRequest> FAttachSecurityPolicyRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FAttachSecurityPolicyRequest> FAttachSecurityPolicyRequest::WithUserName(
        const TOptional<FString> UserName
    )
    {
        this->UserNameValue = UserName;
        return SharedThis(this);
    }

    TSharedPtr<FAttachSecurityPolicyRequest> FAttachSecurityPolicyRequest::WithSecurityPolicyId(
        const TOptional<FString> SecurityPolicyId
    )
    {
        this->SecurityPolicyIdValue = SecurityPolicyId;
        return SharedThis(this);
    }

    TOptional<FString> FAttachSecurityPolicyRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FAttachSecurityPolicyRequest::GetUserName() const
    {
        return UserNameValue;
    }

    TOptional<FString> FAttachSecurityPolicyRequest::GetSecurityPolicyId() const
    {
        return SecurityPolicyIdValue;
    }

    TSharedPtr<FAttachSecurityPolicyRequest> FAttachSecurityPolicyRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FAttachSecurityPolicyRequest>()
            ->WithContextStack(Data->HasField(ANSI_TO_TCHAR("contextStack")) ? TOptional<FString>(Data->GetStringField(ANSI_TO_TCHAR("contextStack"))) : TOptional<FString>())
            ->WithUserName(Data->HasField(ANSI_TO_TCHAR("userName")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("userName"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithSecurityPolicyId(Data->HasField(ANSI_TO_TCHAR("securityPolicyId")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("securityPolicyId"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FAttachSecurityPolicyRequest::ToJson() const
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
        if (SecurityPolicyIdValue.IsSet())
        {
            JsonRootObject->SetStringField("securityPolicyId", SecurityPolicyIdValue.GetValue());
        }
        return JsonRootObject;
    }
}