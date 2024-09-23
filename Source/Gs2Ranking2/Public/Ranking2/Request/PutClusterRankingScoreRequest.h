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
    class FPutClusterRankingScoreRequest;

    class GS2RANKING2_API FPutClusterRankingScoreRequest final : public TSharedFromThis<FPutClusterRankingScoreRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> RankingNameValue;
        TOptional<FString> ClusterNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<int64> ScoreValue;
        TOptional<FString> MetadataValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FPutClusterRankingScoreRequest();
        FPutClusterRankingScoreRequest(
            const FPutClusterRankingScoreRequest& From
        );
        ~FPutClusterRankingScoreRequest() = default;

        TSharedPtr<FPutClusterRankingScoreRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FPutClusterRankingScoreRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FPutClusterRankingScoreRequest> WithRankingName(const TOptional<FString> RankingName);
        TSharedPtr<FPutClusterRankingScoreRequest> WithClusterName(const TOptional<FString> ClusterName);
        TSharedPtr<FPutClusterRankingScoreRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FPutClusterRankingScoreRequest> WithScore(const TOptional<int64> Score);
        TSharedPtr<FPutClusterRankingScoreRequest> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FPutClusterRankingScoreRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetRankingName() const;
        TOptional<FString> GetClusterName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<int64> GetScore() const;
        FString GetScoreString() const;
        TOptional<FString> GetMetadata() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FPutClusterRankingScoreRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FPutClusterRankingScoreRequest, ESPMode::ThreadSafe> FPutClusterRankingScoreRequestPtr;
}