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
    class FGetClusterRankingByUserIdRequest;

    class GS2RANKING2_API FGetClusterRankingByUserIdRequest final : public TSharedFromThis<FGetClusterRankingByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> RankingNameValue;
        TOptional<FString> ClusterNameValue;
        TOptional<FString> UserIdValue;
        TOptional<int64> SeasonValue;
        TOptional<FString> TimeOffsetTokenValue;
        
    public:
        
        FGetClusterRankingByUserIdRequest();
        FGetClusterRankingByUserIdRequest(
            const FGetClusterRankingByUserIdRequest& From
        );
        ~FGetClusterRankingByUserIdRequest() = default;

        TSharedPtr<FGetClusterRankingByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetClusterRankingByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetClusterRankingByUserIdRequest> WithRankingName(const TOptional<FString> RankingName);
        TSharedPtr<FGetClusterRankingByUserIdRequest> WithClusterName(const TOptional<FString> ClusterName);
        TSharedPtr<FGetClusterRankingByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FGetClusterRankingByUserIdRequest> WithSeason(const TOptional<int64> Season);
        TSharedPtr<FGetClusterRankingByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetRankingName() const;
        TOptional<FString> GetClusterName() const;
        TOptional<FString> GetUserId() const;
        TOptional<int64> GetSeason() const;
        FString GetSeasonString() const;
        TOptional<FString> GetTimeOffsetToken() const;

        static TSharedPtr<FGetClusterRankingByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetClusterRankingByUserIdRequest, ESPMode::ThreadSafe> FGetClusterRankingByUserIdRequestPtr;
}