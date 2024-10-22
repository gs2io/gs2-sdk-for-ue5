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
    class FDescribeSubscribeRankingScoresRequest;

    class GS2RANKING2_API FDescribeSubscribeRankingScoresRequest final : public TSharedFromThis<FDescribeSubscribeRankingScoresRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> RankingNameValue;
        TOptional<FString> PageTokenValue;
        TOptional<int32> LimitValue;
        
    public:
        
        FDescribeSubscribeRankingScoresRequest();
        FDescribeSubscribeRankingScoresRequest(
            const FDescribeSubscribeRankingScoresRequest& From
        );
        ~FDescribeSubscribeRankingScoresRequest() = default;

        TSharedPtr<FDescribeSubscribeRankingScoresRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDescribeSubscribeRankingScoresRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDescribeSubscribeRankingScoresRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FDescribeSubscribeRankingScoresRequest> WithRankingName(const TOptional<FString> RankingName);
        TSharedPtr<FDescribeSubscribeRankingScoresRequest> WithPageToken(const TOptional<FString> PageToken);
        TSharedPtr<FDescribeSubscribeRankingScoresRequest> WithLimit(const TOptional<int32> Limit);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetRankingName() const;
        TOptional<FString> GetPageToken() const;
        TOptional<int32> GetLimit() const;
        FString GetLimitString() const;

        static TSharedPtr<FDescribeSubscribeRankingScoresRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDescribeSubscribeRankingScoresRequest> FDescribeSubscribeRankingScoresRequestPtr;
}