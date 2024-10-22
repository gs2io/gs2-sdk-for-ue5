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
    class FVerifyClusterRankingScoreByUserIdRequest;

    class GS2RANKING2_API FVerifyClusterRankingScoreByUserIdRequest final : public TSharedFromThis<FVerifyClusterRankingScoreByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> RankingNameValue;
        TOptional<FString> ClusterNameValue;
        TOptional<FString> VerifyTypeValue;
        TOptional<int64> SeasonValue;
        TOptional<int64> ScoreValue;
        TOptional<bool> MultiplyValueSpecifyingQuantityValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FVerifyClusterRankingScoreByUserIdRequest();
        FVerifyClusterRankingScoreByUserIdRequest(
            const FVerifyClusterRankingScoreByUserIdRequest& From
        );
        ~FVerifyClusterRankingScoreByUserIdRequest() = default;

        TSharedPtr<FVerifyClusterRankingScoreByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FVerifyClusterRankingScoreByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FVerifyClusterRankingScoreByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FVerifyClusterRankingScoreByUserIdRequest> WithRankingName(const TOptional<FString> RankingName);
        TSharedPtr<FVerifyClusterRankingScoreByUserIdRequest> WithClusterName(const TOptional<FString> ClusterName);
        TSharedPtr<FVerifyClusterRankingScoreByUserIdRequest> WithVerifyType(const TOptional<FString> VerifyType);
        TSharedPtr<FVerifyClusterRankingScoreByUserIdRequest> WithSeason(const TOptional<int64> Season);
        TSharedPtr<FVerifyClusterRankingScoreByUserIdRequest> WithScore(const TOptional<int64> Score);
        TSharedPtr<FVerifyClusterRankingScoreByUserIdRequest> WithMultiplyValueSpecifyingQuantity(const TOptional<bool> MultiplyValueSpecifyingQuantity);
        TSharedPtr<FVerifyClusterRankingScoreByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FVerifyClusterRankingScoreByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetRankingName() const;
        TOptional<FString> GetClusterName() const;
        TOptional<FString> GetVerifyType() const;
        TOptional<int64> GetSeason() const;
        FString GetSeasonString() const;
        TOptional<int64> GetScore() const;
        FString GetScoreString() const;
        TOptional<bool> GetMultiplyValueSpecifyingQuantity() const;
        FString GetMultiplyValueSpecifyingQuantityString() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FVerifyClusterRankingScoreByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FVerifyClusterRankingScoreByUserIdRequest> FVerifyClusterRankingScoreByUserIdRequestPtr;
}