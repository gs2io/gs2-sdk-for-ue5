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

#include "Identifier/Request/DetachSecurityPolicyRequest.h"

namespace Gs2::Identifier::Request
{
    FDetachSecurityPolicyRequest::FDetachSecurityPolicyRequest():
        UserNameValue(TOptional<FString>()),
        SecurityPolicyIdValue(TOptional<FString>())
    {
    }

    FDetachSecurityPolicyRequest::FDetachSecurityPolicyRequest(
        const FDetachSecurityPolicyRequest& From
    ):
        UserNameValue(From.UserNameValue),
        SecurityPolicyIdValue(From.SecurityPolicyIdValue)
    {
    }

    TSharedPtr<FDetachSecurityPolicyRequest> FDetachSecurityPolicyRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FDetachSecurityPolicyRequest> FDetachSecurityPolicyRequest::WithUserName(
        const TOptional<FString> UserName
    )
    {
        this->UserNameValue = UserName;
        return SharedThis(this);
    }

    TSharedPtr<FDetachSecurityPolicyRequest> FDetachSecurityPolicyRequest::WithSecurityPolicyId(
        const TOptional<FString> SecurityPolicyId
    )
    {
        this->SecurityPolicyIdValue = SecurityPolicyId;
        return SharedThis(this);
    }

    TOptional<FString> FDetachSecurityPolicyRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FDetachSecurityPolicyRequest::GetUserName() const
    {
        return UserNameValue;
    }

    TOptional<FString> FDetachSecurityPolicyRequest::GetSecurityPolicyId() const
    {
        return SecurityPolicyIdValue;
    }

    TSharedPtr<FDetachSecurityPolicyRequest> FDetachSecurityPolicyRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FDetachSecurityPolicyRequest>()
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

    TSharedPtr<FJsonObject> FDetachSecurityPolicyRequest::ToJson() const
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