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
    class FPutSubscribeRankingScoreRequest;

    class GS2RANKING2_API FPutSubscribeRankingScoreRequest final : public TSharedFromThis<FPutSubscribeRankingScoreRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> RankingNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<int64> ScoreValue;
        TOptional<FString> MetadataValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FPutSubscribeRankingScoreRequest();
        FPutSubscribeRankingScoreRequest(
            const FPutSubscribeRankingScoreRequest& From
        );
        ~FPutSubscribeRankingScoreRequest() = default;

        TSharedPtr<FPutSubscribeRankingScoreRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FPutSubscribeRankingScoreRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FPutSubscribeRankingScoreRequest> WithRankingName(const TOptional<FString> RankingName);
        TSharedPtr<FPutSubscribeRankingScoreRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FPutSubscribeRankingScoreRequest> WithScore(const TOptional<int64> Score);
        TSharedPtr<FPutSubscribeRankingScoreRequest> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FPutSubscribeRankingScoreRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetRankingName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<int64> GetScore() const;
        FString GetScoreString() const;
        TOptional<FString> GetMetadata() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FPutSubscribeRankingScoreRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FPutSubscribeRankingScoreRequest, ESPMode::ThreadSafe> FPutSubscribeRankingScoreRequestPtr;
}