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
    class FDescribeGlobalRankingScoresByUserIdRequest;

    class GS2RANKING2_API FDescribeGlobalRankingScoresByUserIdRequest final : public TSharedFromThis<FDescribeGlobalRankingScoresByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> RankingNameValue;
        TOptional<FString> PageTokenValue;
        TOptional<int32> LimitValue;
        TOptional<FString> TimeOffsetTokenValue;
        
    public:
        
        FDescribeGlobalRankingScoresByUserIdRequest();
        FDescribeGlobalRankingScoresByUserIdRequest(
            const FDescribeGlobalRankingScoresByUserIdRequest& From
        );
        ~FDescribeGlobalRankingScoresByUserIdRequest() = default;

        TSharedPtr<FDescribeGlobalRankingScoresByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDescribeGlobalRankingScoresByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDescribeGlobalRankingScoresByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FDescribeGlobalRankingScoresByUserIdRequest> WithRankingName(const TOptional<FString> RankingName);
        TSharedPtr<FDescribeGlobalRankingScoresByUserIdRequest> WithPageToken(const TOptional<FString> PageToken);
        TSharedPtr<FDescribeGlobalRankingScoresByUserIdRequest> WithLimit(const TOptional<int32> Limit);
        TSharedPtr<FDescribeGlobalRankingScoresByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetRankingName() const;
        TOptional<FString> GetPageToken() const;
        TOptional<int32> GetLimit() const;
        FString GetLimitString() const;
        TOptional<FString> GetTimeOffsetToken() const;

        static TSharedPtr<FDescribeGlobalRankingScoresByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDescribeGlobalRankingScoresByUserIdRequest, ESPMode::ThreadSafe> FDescribeGlobalRankingScoresByUserIdRequestPtr;
}