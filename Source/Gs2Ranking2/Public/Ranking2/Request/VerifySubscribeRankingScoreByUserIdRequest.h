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
    class FVerifySubscribeRankingScoreByUserIdRequest;

    class GS2RANKING2_API FVerifySubscribeRankingScoreByUserIdRequest final : public TSharedFromThis<FVerifySubscribeRankingScoreByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> RankingNameValue;
        TOptional<FString> VerifyTypeValue;
        TOptional<int64> SeasonValue;
        TOptional<int64> ScoreValue;
        TOptional<bool> MultiplyValueSpecifyingQuantityValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FVerifySubscribeRankingScoreByUserIdRequest();
        FVerifySubscribeRankingScoreByUserIdRequest(
            const FVerifySubscribeRankingScoreByUserIdRequest& From
        );
        ~FVerifySubscribeRankingScoreByUserIdRequest() = default;

        TSharedPtr<FVerifySubscribeRankingScoreByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FVerifySubscribeRankingScoreByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FVerifySubscribeRankingScoreByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FVerifySubscribeRankingScoreByUserIdRequest> WithRankingName(const TOptional<FString> RankingName);
        TSharedPtr<FVerifySubscribeRankingScoreByUserIdRequest> WithVerifyType(const TOptional<FString> VerifyType);
        TSharedPtr<FVerifySubscribeRankingScoreByUserIdRequest> WithSeason(const TOptional<int64> Season);
        TSharedPtr<FVerifySubscribeRankingScoreByUserIdRequest> WithScore(const TOptional<int64> Score);
        TSharedPtr<FVerifySubscribeRankingScoreByUserIdRequest> WithMultiplyValueSpecifyingQuantity(const TOptional<bool> MultiplyValueSpecifyingQuantity);
        TSharedPtr<FVerifySubscribeRankingScoreByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FVerifySubscribeRankingScoreByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetRankingName() const;
        TOptional<FString> GetVerifyType() const;
        TOptional<int64> GetSeason() const;
        FString GetSeasonString() const;
        TOptional<int64> GetScore() const;
        FString GetScoreString() const;
        TOptional<bool> GetMultiplyValueSpecifyingQuantity() const;
        FString GetMultiplyValueSpecifyingQuantityString() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FVerifySubscribeRankingScoreByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FVerifySubscribeRankingScoreByUserIdRequest> FVerifySubscribeRankingScoreByUserIdRequestPtr;
}