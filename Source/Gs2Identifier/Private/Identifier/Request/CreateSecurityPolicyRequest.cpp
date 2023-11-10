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

#include "Identifier/Request/CreateSecurityPolicyRequest.h"

namespace Gs2::Identifier::Request
{
    FCreateSecurityPolicyRequest::FCreateSecurityPolicyRequest():
        NameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        PolicyValue(TOptional<FString>())
    {
    }

    FCreateSecurityPolicyRequest::FCreateSecurityPolicyRequest(
        const FCreateSecurityPolicyRequest& From
    ):
        NameValue(From.NameValue),
        DescriptionValue(From.DescriptionValue),
        PolicyValue(From.PolicyValue)
    {
    }

    TSharedPtr<FCreateSecurityPolicyRequest> FCreateSecurityPolicyRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FCreateSecurityPolicyRequest> FCreateSecurityPolicyRequest::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FCreateSecurityPolicyRequest> FCreateSecurityPolicyRequest::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
        return SharedThis(this);
    }

    TSharedPtr<FCreateSecurityPolicyRequest> FCreateSecurityPolicyRequest::WithPolicy(
        const TOptional<FString> Policy
    )
    {
        this->PolicyValue = Policy;
        return SharedThis(this);
    }

    TOptional<FString> FCreateSecurityPolicyRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FCreateSecurityPolicyRequest::GetName() const
    {
        return NameValue;
    }

    TOptional<FString> FCreateSecurityPolicyRequest::GetDescription() const
    {
        return DescriptionValue;
    }

    TOptional<FString> FCreateSecurityPolicyRequest::GetPolicy() const
    {
        return PolicyValue;
    }

    TSharedPtr<FCreateSecurityPolicyRequest> FCreateSecurityPolicyRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FCreateSecurityPolicyRequest>()
            ->WithContextStack(Data->HasField("contextStack") ? TOptional<FString>(Data->GetStringField("contextStack")) : TOptional<FString>())
            ->WithName(Data->HasField("name") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("name", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithDescription(Data->HasField("description") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("description", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithPolicy(Data->HasField("policy") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("policy", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FCreateSecurityPolicyRequest::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ContextStackValue.IsSet())
        {
            JsonRootObject->SetStringField("contextStack", ContextStackValue.GetValue());
        }
        if (NameValue.IsSet())
        {
            JsonRootObject->SetStringField("name", NameValue.GetValue());
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