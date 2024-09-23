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
    class FGetSubscribeRankingRequest;

    class GS2RANKING2_API FGetSubscribeRankingRequest final : public TSharedFromThis<FGetSubscribeRankingRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> RankingNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<int64> SeasonValue;
        TOptional<FString> ScorerUserIdValue;
        
    public:
        
        FGetSubscribeRankingRequest();
        FGetSubscribeRankingRequest(
            const FGetSubscribeRankingRequest& From
        );
        ~FGetSubscribeRankingRequest() = default;

        TSharedPtr<FGetSubscribeRankingRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetSubscribeRankingRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetSubscribeRankingRequest> WithRankingName(const TOptional<FString> RankingName);
        TSharedPtr<FGetSubscribeRankingRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FGetSubscribeRankingRequest> WithSeason(const TOptional<int64> Season);
        TSharedPtr<FGetSubscribeRankingRequest> WithScorerUserId(const TOptional<FString> ScorerUserId);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetRankingName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<int64> GetSeason() const;
        FString GetSeasonString() const;
        TOptional<FString> GetScorerUserId() const;

        static TSharedPtr<FGetSubscribeRankingRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetSubscribeRankingRequest, ESPMode::ThreadSafe> FGetSubscribeRankingRequestPtr;
}