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
    class FGetSubscribeRankingByUserIdRequest;

    class GS2RANKING2_API FGetSubscribeRankingByUserIdRequest final : public TSharedFromThis<FGetSubscribeRankingByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> RankingNameValue;
        TOptional<FString> UserIdValue;
        TOptional<int64> SeasonValue;
        TOptional<FString> ScorerUserIdValue;
        TOptional<FString> TimeOffsetTokenValue;
        
    public:
        
        FGetSubscribeRankingByUserIdRequest();
        FGetSubscribeRankingByUserIdRequest(
            const FGetSubscribeRankingByUserIdRequest& From
        );
        ~FGetSubscribeRankingByUserIdRequest() = default;

        TSharedPtr<FGetSubscribeRankingByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetSubscribeRankingByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetSubscribeRankingByUserIdRequest> WithRankingName(const TOptional<FString> RankingName);
        TSharedPtr<FGetSubscribeRankingByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FGetSubscribeRankingByUserIdRequest> WithSeason(const TOptional<int64> Season);
        TSharedPtr<FGetSubscribeRankingByUserIdRequest> WithScorerUserId(const TOptional<FString> ScorerUserId);
        TSharedPtr<FGetSubscribeRankingByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetRankingName() const;
        TOptional<FString> GetUserId() const;
        TOptional<int64> GetSeason() const;
        FString GetSeasonString() const;
        TOptional<FString> GetScorerUserId() const;
        TOptional<FString> GetTimeOffsetToken() const;

        static TSharedPtr<FGetSubscribeRankingByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetSubscribeRankingByUserIdRequest, ESPMode::ThreadSafe> FGetSubscribeRankingByUserIdRequestPtr;
}