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
    class FGetClusterRankingRequest;

    class GS2RANKING2_API FGetClusterRankingRequest final : public TSharedFromThis<FGetClusterRankingRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> RankingNameValue;
        TOptional<FString> ClusterNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<int64> SeasonValue;
        
    public:
        
        FGetClusterRankingRequest();
        FGetClusterRankingRequest(
            const FGetClusterRankingRequest& From
        );
        ~FGetClusterRankingRequest() = default;

        TSharedPtr<FGetClusterRankingRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetClusterRankingRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetClusterRankingRequest> WithRankingName(const TOptional<FString> RankingName);
        TSharedPtr<FGetClusterRankingRequest> WithClusterName(const TOptional<FString> ClusterName);
        TSharedPtr<FGetClusterRankingRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FGetClusterRankingRequest> WithSeason(const TOptional<int64> Season);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetRankingName() const;
        TOptional<FString> GetClusterName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<int64> GetSeason() const;
        FString GetSeasonString() const;

        static TSharedPtr<FGetClusterRankingRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetClusterRankingRequest> FGetClusterRankingRequestPtr;
}