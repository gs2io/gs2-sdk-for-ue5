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

#include "Identifier/Request/UpdateSecurityPolicyRequest.h"

namespace Gs2::Identifier::Request
{
    FUpdateSecurityPolicyRequest::FUpdateSecurityPolicyRequest():
        SecurityPolicyNameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        PolicyValue(TOptional<FString>())
    {
    }

    FUpdateSecurityPolicyRequest::FUpdateSecurityPolicyRequest(
        const FUpdateSecurityPolicyRequest& From
    ):
        SecurityPolicyNameValue(From.SecurityPolicyNameValue),
        DescriptionValue(From.DescriptionValue),
        PolicyValue(From.PolicyValue)
    {
    }

    TSharedPtr<FUpdateSecurityPolicyRequest> FUpdateSecurityPolicyRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateSecurityPolicyRequest> FUpdateSecurityPolicyRequest::WithSecurityPolicyName(
        const TOptional<FString> SecurityPolicyName
    )
    {
        this->SecurityPolicyNameValue = SecurityPolicyName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateSecurityPolicyRequest> FUpdateSecurityPolicyRequest::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateSecurityPolicyRequest> FUpdateSecurityPolicyRequest::WithPolicy(
        const TOptional<FString> Policy
    )
    {
        this->PolicyValue = Policy;
        return SharedThis(this);
    }

    TOptional<FString> FUpdateSecurityPolicyRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FUpdateSecurityPolicyRequest::GetSecurityPolicyName() const
    {
        return SecurityPolicyNameValue;
    }

    TOptional<FString> FUpdateSecurityPolicyRequest::GetDescription() const
    {
        return DescriptionValue;
    }

    TOptional<FString> FUpdateSecurityPolicyRequest::GetPolicy() const
    {
        return PolicyValue;
    }

    TSharedPtr<FUpdateSecurityPolicyRequest> FUpdateSecurityPolicyRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FUpdateSecurityPolicyRequest>()
            ->WithContextStack(Data->HasField(ANSI_TO_TCHAR("contextStack")) ? TOptional<FString>(Data->GetStringField(ANSI_TO_TCHAR("contextStack"))) : TOptional<FString>())
            ->WithSecurityPolicyName(Data->HasField(ANSI_TO_TCHAR("securityPolicyName")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("securityPolicyName"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithDescription(Data->HasField(ANSI_TO_TCHAR("description")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("description"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithPolicy(Data->HasField(ANSI_TO_TCHAR("policy")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("policy"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FUpdateSecurityPolicyRequest::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ContextStackValue.IsSet())
        {
            JsonRootObject->SetStringField("contextStack", ContextStackValue.GetValue());
        }
        if (SecurityPolicyNameValue.IsSet())
        {
            JsonRootObject->SetStringField("securityPolicyName", SecurityPolicyNameValue.GetValue());
        }
        if (DescriptionValue.IsSet())
        {
            JsonRootObject->SetStringField("description", DescriptionValue.GetValue());
        }
        if (PolicyValue.IsSet())
        {
            JsonRootObject->SetStringField("policy", PolicyValue.GetValue());
        }
        return JsonRootObject;
    }
}