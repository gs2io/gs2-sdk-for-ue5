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
#include "../Model/SecurityPolicy.h"

namespace Gs2::Identifier::Result
{
    class GS2IDENTIFIER_API FDetachSecurityPolicyResult final : public TSharedFromThis<FDetachSecurityPolicyResult>
    {
        TSharedPtr<TArray<TSharedPtr<Model::FSecurityPolicy>>> ItemsValue;
        
    public:
        
        FDetachSecurityPolicyResult();
        FDetachSecurityPolicyResult(
            const FDetachSecurityPolicyResult& From
        );
        ~FDetachSecurityPolicyResult() = default;

        TSharedPtr<FDetachSecurityPolicyResult> WithItems(const TSharedPtr<TArray<TSharedPtr<Model::FSecurityPolicy>>> Items);

        TSharedPtr<TArray<TSharedPtr<Model::FSecurityPolicy>>> GetItems() const;

        static TSharedPtr<FDetachSecurityPolicyResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDetachSecurityPolicyResult, ESPMode::ThreadSafe> FDetachSecurityPolicyResultPtr;
}