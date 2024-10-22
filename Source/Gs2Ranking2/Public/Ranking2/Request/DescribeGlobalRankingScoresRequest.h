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

namespace Gs2::Ranking2::Request
{
    class FDescribeGlobalRankingScoresRequest;

    class GS2RANKING2_API FDescribeGlobalRankingScoresRequest final : public TSharedFromThis<FDescribeGlobalRankingScoresRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> RankingNameValue;
        TOptional<FString> PageTokenValue;
        TOptional<int32> LimitValue;
        
    public:
        
        FDescribeGlobalRankingScoresRequest();
        FDescribeGlobalRankingScoresRequest(
            const FDescribeGlobalRankingScoresRequest& From
        );
        ~FDescribeGlobalRankingScoresRequest() = default;

        TSharedPtr<FDescribeGlobalRankingScoresRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDescribeGlobalRankingScoresRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDescribeGlobalRankingScoresRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FDescribeGlobalRankingScoresRequest> WithRankingName(const TOptional<FString> RankingName);
        TSharedPtr<FDescribeGlobalRankingScoresRequest> WithPageToken(const TOptional<FString> PageToken);
        TSharedPtr<FDescribeGlobalRankingScoresRequest> WithLimit(const TOptional<int32> Limit);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetRankingName() const;
        TOptional<FString> GetPageToken() const;
        TOptional<int32> GetLimit() const;
        FString GetLimitString() const;

        static TSharedPtr<FDescribeGlobalRankingScoresRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDescribeGlobalRankingScoresRequest> FDescribeGlobalRankingScoresRequestPtr;
}