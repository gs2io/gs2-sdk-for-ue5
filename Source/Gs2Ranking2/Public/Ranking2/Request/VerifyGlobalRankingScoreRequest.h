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
    class FVerifyGlobalRankingScoreRequest;

    class GS2RANKING2_API FVerifyGlobalRankingScoreRequest final : public TSharedFromThis<FVerifyGlobalRankingScoreRequest>
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
        
        FVerifyGlobalRankingScoreRequest();
        FVerifyGlobalRankingScoreRequest(
            const FVerifyGlobalRankingScoreRequest& From
        );
        ~FVerifyGlobalRankingScoreRequest() = default;

        TSharedPtr<FVerifyGlobalRankingScoreRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FVerifyGlobalRankingScoreRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FVerifyGlobalRankingScoreRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FVerifyGlobalRankingScoreRequest> WithRankingName(const TOptional<FString> RankingName);
        TSharedPtr<FVerifyGlobalRankingScoreRequest> WithVerifyType(const TOptional<FString> VerifyType);
        TSharedPtr<FVerifyGlobalRankingScoreRequest> WithSeason(const TOptional<int64> Season);
        TSharedPtr<FVerifyGlobalRankingScoreRequest> WithScore(const TOptional<int64> Score);
        TSharedPtr<FVerifyGlobalRankingScoreRequest> WithMultiplyValueSpecifyingQuantity(const TOptional<bool> MultiplyValueSpecifyingQuantity);
        TSharedPtr<FVerifyGlobalRankingScoreRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

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

        static TSharedPtr<FVerifyGlobalRankingScoreRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FVerifyGlobalRankingScoreRequest> FVerifyGlobalRankingScoreRequestPtr;
}