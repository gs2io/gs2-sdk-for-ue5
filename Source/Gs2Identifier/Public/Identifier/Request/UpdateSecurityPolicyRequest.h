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

#pragma once

#include "CoreMinimal.h"

namespace Gs2::Identifier::Request
{
    class FUpdateSecurityPolicyRequest;

    class GS2IDENTIFIER_API FUpdateSecurityPolicyRequest final : public TSharedFromThis<FUpdateSecurityPolicyRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> SecurityPolicyNameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> PolicyValue;
        
    public:
        
        FUpdateSecurityPolicyRequest();
        FUpdateSecurityPolicyRequest(
            const FUpdateSecurityPolicyRequest& From
        );
        ~FUpdateSecurityPolicyRequest() = default;

        TSharedPtr<FUpdateSecurityPolicyRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FUpdateSecurityPolicyRequest> WithSecurityPolicyName(const TOptional<FString> SecurityPolicyName);
        TSharedPtr<FUpdateSecurityPolicyRequest> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FUpdateSecurityPolicyRequest> WithPolicy(const TOptional<FString> Policy);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetSecurityPolicyName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetPolicy() const;

        static TSharedPtr<FUpdateSecurityPolicyRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUpdateSecurityPolicyRequest, ESPMode::ThreadSafe> FUpdateSecurityPolicyRequestPtr;
}