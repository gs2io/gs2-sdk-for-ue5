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

#include "Identifier/Request/DeleteSecurityPolicyRequest.h"

namespace Gs2::Identifier::Request
{
    FDeleteSecurityPolicyRequest::FDeleteSecurityPolicyRequest():
        SecurityPolicyNameValue(TOptional<FString>())
    {
    }

    FDeleteSecurityPolicyRequest::FDeleteSecurityPolicyRequest(
        const FDeleteSecurityPolicyRequest& From
    ):
        SecurityPolicyNameValue(From.SecurityPolicyNameValue)
    {
    }

    TSharedPtr<FDeleteSecurityPolicyRequest> FDeleteSecurityPolicyRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FDeleteSecurityPolicyRequest> FDeleteSecurityPolicyRequest::WithSecurityPolicyName(
        const TOptional<FString> SecurityPolicyName
    )
    {
        this->SecurityPolicyNameValue = SecurityPolicyName;
        return SharedThis(this);
    }

    TOptional<FString> FDeleteSecurityPolicyRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FDeleteSecurityPolicyRequest::GetSecurityPolicyName() const
    {
        return SecurityPolicyNameValue;
    }

    TSharedPtr<FDeleteSecurityPolicyRequest> FDeleteSecurityPolicyRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FDeleteSecurityPolicyRequest>()
            ->WithContextStack(Data->HasField(ANSI_TO_TCHAR("contextStack")) ? TOptional<FString>(Data->GetStringField(ANSI_TO_TCHAR("contextStack"))) : TOptional<FString>())
            ->WithSecurityPolicyName(Data->HasField(ANSI_TO_TCHAR("securityPolicyName")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("securityPolicyName"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FDeleteSecurityPolicyRequest::ToJson() const
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
        return JsonRootObject;
    }
}