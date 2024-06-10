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

namespace Gs2::Ranking2::Request
{
    class FDescribeSubscribeRankingScoresByUserIdRequest;

    class GS2RANKING2_API FDescribeSubscribeRankingScoresByUserIdRequest final : public TSharedFromThis<FDescribeSubscribeRankingScoresByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> RankingNameValue;
        TOptional<FString> PageTokenValue;
        TOptional<int32> LimitValue;
        TOptional<FString> TimeOffsetTokenValue;
        
    public:
        
        FDescribeSubscribeRankingScoresByUserIdRequest();
        FDescribeSubscribeRankingScoresByUserIdRequest(
            const FDescribeSubscribeRankingScoresByUserIdRequest& From
        );
        ~FDescribeSubscribeRankingScoresByUserIdRequest() = default;

        TSharedPtr<FDescribeSubscribeRankingScoresByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDescribeSubscribeRankingScoresByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDescribeSubscribeRankingScoresByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FDescribeSubscribeRankingScoresByUserIdRequest> WithRankingName(const TOptional<FString> RankingName);
        TSharedPtr<FDescribeSubscribeRankingScoresByUserIdRequest> WithPageToken(const TOptional<FString> PageToken);
        TSharedPtr<FDescribeSubscribeRankingScoresByUserIdRequest> WithLimit(const TOptional<int32> Limit);
        TSharedPtr<FDescribeSubscribeRankingScoresByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetRankingName() const;
        TOptional<FString> GetPageToken() const;
        TOptional<int32> GetLimit() const;
        FString GetLimitString() const;
        TOptional<FString> GetTimeOffsetToken() const;

        static TSharedPtr<FDescribeSubscribeRankingScoresByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDescribeSubscribeRankingScoresByUserIdRequest, ESPMode::ThreadSafe> FDescribeSubscribeRankingScoresByUserIdRequestPtr;
}