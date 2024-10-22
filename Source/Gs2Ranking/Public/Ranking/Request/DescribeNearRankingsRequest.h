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
#include "Dom/JsonObject.h"

namespace Gs2::Ranking::Request
{
    class FDescribeNearRankingsRequest;

    class GS2RANKING_API FDescribeNearRankingsRequest final : public TSharedFromThis<FDescribeNearRankingsRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> CategoryNameValue;
        TOptional<FString> AdditionalScopeNameValue;
        TOptional<int64> ScoreValue;
        
    public:
        
        FDescribeNearRankingsRequest();
        FDescribeNearRankingsRequest(
            const FDescribeNearRankingsRequest& From
        );
        ~FDescribeNearRankingsRequest() = default;

        TSharedPtr<FDescribeNearRankingsRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDescribeNearRankingsRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDescribeNearRankingsRequest> WithCategoryName(const TOptional<FString> CategoryName);
        TSharedPtr<FDescribeNearRankingsRequest> WithAdditionalScopeName(const TOptional<FString> AdditionalScopeName);
        TSharedPtr<FDescribeNearRankingsRequest> WithScore(const TOptional<int64> Score);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetCategoryName() const;
        TOptional<FString> GetAdditionalScopeName() const;
        TOptional<int64> GetScore() const;
        FString GetScoreString() const;

        static TSharedPtr<FDescribeNearRankingsRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDescribeNearRankingsRequest> FDescribeNearRankingsRequestPtr;
}