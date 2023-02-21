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
    class GS2IDENTIFIER_API FDescribeCommonSecurityPoliciesResult final : public TSharedFromThis<FDescribeCommonSecurityPoliciesResult>
    {
        TSharedPtr<TArray<TSharedPtr<Model::FSecurityPolicy>>> ItemsValue;
        TOptional<FString> NextPageTokenValue;
        
    public:
        
        FDescribeCommonSecurityPoliciesResult();
        FDescribeCommonSecurityPoliciesResult(
            const FDescribeCommonSecurityPoliciesResult& From
        );
        ~FDescribeCommonSecurityPoliciesResult() = default;

        TSharedPtr<FDescribeCommonSecurityPoliciesResult> WithItems(const TSharedPtr<TArray<TSharedPtr<Model::FSecurityPolicy>>> Items);
        TSharedPtr<FDescribeCommonSecurityPoliciesResult> WithNextPageToken(const TOptional<FString> NextPageToken);

        TSharedPtr<TArray<TSharedPtr<Model::FSecurityPolicy>>> GetItems() const;
        TOptional<FString> GetNextPageToken() const;

        static TSharedPtr<FDescribeCommonSecurityPoliciesResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDescribeCommonSecurityPoliciesResult, ESPMode::ThreadSafe> FDescribeCommonSecurityPoliciesResultPtr;
}