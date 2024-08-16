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
    class FReceiveGlobalRankingReceivedRewardByUserIdRequest;

    class GS2RANKING2_API FReceiveGlobalRankingReceivedRewardByUserIdRequest final : public TSharedFromThis<FReceiveGlobalRankingReceivedRewardByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> RankingNameValue;
        TOptional<int64> SeasonValue;
        TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> ConfigValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FReceiveGlobalRankingReceivedRewardByUserIdRequest();
        FReceiveGlobalRankingReceivedRewardByUserIdRequest(
            const FReceiveGlobalRankingReceivedRewardByUserIdRequest& From
        );
        ~FReceiveGlobalRankingReceivedRewardByUserIdRequest() = default;

        TSharedPtr<FReceiveGlobalRankingReceivedRewardByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FReceiveGlobalRankingReceivedRewardByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FReceiveGlobalRankingReceivedRewardByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FReceiveGlobalRankingReceivedRewardByUserIdRequest> WithRankingName(const TOptional<FString> RankingName);
        TSharedPtr<FReceiveGlobalRankingReceivedRewardByUserIdRequest> WithSeason(const TOptional<int64> Season);
        TSharedPtr<FReceiveGlobalRankingReceivedRewardByUserIdRequest> WithConfig(const TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> Config);
        TSharedPtr<FReceiveGlobalRankingReceivedRewardByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FReceiveGlobalRankingReceivedRewardByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetRankingName() const;
        TOptional<int64> GetSeason() const;
        FString GetSeasonString() const;TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> GetConfig() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FReceiveGlobalRankingReceivedRewardByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FReceiveGlobalRankingReceivedRewardByUserIdRequest> FReceiveGlobalRankingReceivedRewardByUserIdRequestPtr;
}