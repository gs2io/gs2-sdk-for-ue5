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
    class FCreateGlobalRankingReceivedRewardByUserIdRequest;

    class GS2RANKING2_API FCreateGlobalRankingReceivedRewardByUserIdRequest final : public TSharedFromThis<FCreateGlobalRankingReceivedRewardByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> RankingNameValue;
        TOptional<FString> UserIdValue;
        TOptional<int64> SeasonValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FCreateGlobalRankingReceivedRewardByUserIdRequest();
        FCreateGlobalRankingReceivedRewardByUserIdRequest(
            const FCreateGlobalRankingReceivedRewardByUserIdRequest& From
        );
        ~FCreateGlobalRankingReceivedRewardByUserIdRequest() = default;

        TSharedPtr<FCreateGlobalRankingReceivedRewardByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FCreateGlobalRankingReceivedRewardByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FCreateGlobalRankingReceivedRewardByUserIdRequest> WithRankingName(const TOptional<FString> RankingName);
        TSharedPtr<FCreateGlobalRankingReceivedRewardByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FCreateGlobalRankingReceivedRewardByUserIdRequest> WithSeason(const TOptional<int64> Season);
        TSharedPtr<FCreateGlobalRankingReceivedRewardByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FCreateGlobalRankingReceivedRewardByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetRankingName() const;
        TOptional<FString> GetUserId() const;
        TOptional<int64> GetSeason() const;
        FString GetSeasonString() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FCreateGlobalRankingReceivedRewardByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FCreateGlobalRankingReceivedRewardByUserIdRequest> FCreateGlobalRankingReceivedRewardByUserIdRequestPtr;
}