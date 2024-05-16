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

#include "Identifier/Request/GetHasSecurityPolicyRequest.h"

namespace Gs2::Identifier::Request
{
    FGetHasSecurityPolicyRequest::FGetHasSecurityPolicyRequest():
        UserNameValue(TOptional<FString>())
    {
    }

    FGetHasSecurityPolicyRequest::FGetHasSecurityPolicyRequest(
        const FGetHasSecurityPolicyRequest& From
    ):
        UserNameValue(From.UserNameValue)
    {
    }

    TSharedPtr<FGetHasSecurityPolicyRequest> FGetHasSecurityPolicyRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FGetHasSecurityPolicyRequest> FGetHasSecurityPolicyRequest::WithUserName(
        const TOptional<FString> UserName
    )
    {
        this->UserNameValue = UserName;
        return SharedThis(this);
    }

    TOptional<FString> FGetHasSecurityPolicyRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FGetHasSecurityPolicyRequest::GetUserName() const
    {
        return UserNameValue;
    }

    TSharedPtr<FGetHasSecurityPolicyRequest> FGetHasSecurityPolicyRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FGetHasSecurityPolicyRequest>()
            ->WithContextStack(Data->HasField(ANSI_TO_TCHAR("contextStack")) ? TOptional<FString>(Data->GetStringField(ANSI_TO_TCHAR("contextStack"))) : TOptional<FString>())
            ->WithUserName(Data->HasField(ANSI_TO_TCHAR("userName")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("userName"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FGetHasSecurityPolicyRequest::ToJson() const
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
        return JsonRootObject;
    }
}