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
#include "../Model/Config.h"

namespace Gs2::Ranking2::Request
{
    class FReceiveGlobalRankingReceivedRewardRequest;

    class GS2RANKING2_API FReceiveGlobalRankingReceivedRewardRequest final : public TSharedFromThis<FReceiveGlobalRankingReceivedRewardRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> RankingNameValue;
        TOptional<int64> SeasonValue;
        TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> ConfigValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FReceiveGlobalRankingReceivedRewardRequest();
        FReceiveGlobalRankingReceivedRewardRequest(
            const FReceiveGlobalRankingReceivedRewardRequest& From
        );
        ~FReceiveGlobalRankingReceivedRewardRequest() = default;

        TSharedPtr<FReceiveGlobalRankingReceivedRewardRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FReceiveGlobalRankingReceivedRewardRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FReceiveGlobalRankingReceivedRewardRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FReceiveGlobalRankingReceivedRewardRequest> WithRankingName(const TOptional<FString> RankingName);
        TSharedPtr<FReceiveGlobalRankingReceivedRewardRequest> WithSeason(const TOptional<int64> Season);
        TSharedPtr<FReceiveGlobalRankingReceivedRewardRequest> WithConfig(const TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> Config);
        TSharedPtr<FReceiveGlobalRankingReceivedRewardRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetRankingName() const;
        TOptional<int64> GetSeason() const;
        FString GetSeasonString() const;TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> GetConfig() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FReceiveGlobalRankingReceivedRewardRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FReceiveGlobalRankingReceivedRewardRequest> FReceiveGlobalRankingReceivedRewardRequestPtr;
}