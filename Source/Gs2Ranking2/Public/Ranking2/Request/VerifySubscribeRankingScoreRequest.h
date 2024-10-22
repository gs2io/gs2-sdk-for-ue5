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
    class FVerifySubscribeRankingScoreRequest;

    class GS2RANKING2_API FVerifySubscribeRankingScoreRequest final : public TSharedFromThis<FVerifySubscribeRankingScoreRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> RankingNameValue;
        TOptional<FString> VerifyTypeValue;
        TOptional<int64> SeasonValue;
        TOptional<int64> ScoreValue;
        TOptional<bool> MultiplyValueSpecifyingQuantityValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FVerifySubscribeRankingScoreRequest();
        FVerifySubscribeRankingScoreRequest(
            const FVerifySubscribeRankingScoreRequest& From
        );
        ~FVerifySubscribeRankingScoreRequest() = default;

        TSharedPtr<FVerifySubscribeRankingScoreRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FVerifySubscribeRankingScoreRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FVerifySubscribeRankingScoreRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FVerifySubscribeRankingScoreRequest> WithRankingName(const TOptional<FString> RankingName);
        TSharedPtr<FVerifySubscribeRankingScoreRequest> WithVerifyType(const TOptional<FString> VerifyType);
        TSharedPtr<FVerifySubscribeRankingScoreRequest> WithSeason(const TOptional<int64> Season);
        TSharedPtr<FVerifySubscribeRankingScoreRequest> WithScore(const TOptional<int64> Score);
        TSharedPtr<FVerifySubscribeRankingScoreRequest> WithMultiplyValueSpecifyingQuantity(const TOptional<bool> MultiplyValueSpecifyingQuantity);
        TSharedPtr<FVerifySubscribeRankingScoreRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetRankingName() const;
        TOptional<FString> GetVerifyType() const;
        TOptional<int64> GetSeason() const;
        FString GetSeasonString() const;
        TOptional<int64> GetScore() const;
        FString GetScoreString() const;
        TOptional<bool> GetMultiplyValueSpecifyingQuantity() const;
        FString GetMultiplyValueSpecifyingQuantityString() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FVerifySubscribeRankingScoreRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FVerifySubscribeRankingScoreRequest> FVerifySubscribeRankingScoreRequestPtr;
}