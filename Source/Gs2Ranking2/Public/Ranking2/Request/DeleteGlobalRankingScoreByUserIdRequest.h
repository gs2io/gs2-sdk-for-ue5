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
    class FDeleteGlobalRankingScoreByUserIdRequest;

    class GS2RANKING2_API FDeleteGlobalRankingScoreByUserIdRequest final : public TSharedFromThis<FDeleteGlobalRankingScoreByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> RankingNameValue;
        TOptional<FString> UserIdValue;
        TOptional<int64> SeasonValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FDeleteGlobalRankingScoreByUserIdRequest();
        FDeleteGlobalRankingScoreByUserIdRequest(
            const FDeleteGlobalRankingScoreByUserIdRequest& From
        );
        ~FDeleteGlobalRankingScoreByUserIdRequest() = default;

        TSharedPtr<FDeleteGlobalRankingScoreByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDeleteGlobalRankingScoreByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDeleteGlobalRankingScoreByUserIdRequest> WithRankingName(const TOptional<FString> RankingName);
        TSharedPtr<FDeleteGlobalRankingScoreByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FDeleteGlobalRankingScoreByUserIdRequest> WithSeason(const TOptional<int64> Season);
        TSharedPtr<FDeleteGlobalRankingScoreByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FDeleteGlobalRankingScoreByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetRankingName() const;
        TOptional<FString> GetUserId() const;
        TOptional<int64> GetSeason() const;
        FString GetSeasonString() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FDeleteGlobalRankingScoreByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDeleteGlobalRankingScoreByUserIdRequest> FDeleteGlobalRankingScoreByUserIdRequestPtr;
}