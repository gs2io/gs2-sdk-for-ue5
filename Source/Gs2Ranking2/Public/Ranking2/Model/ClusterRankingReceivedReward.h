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
#include "Core/Gs2Object.h"

namespace Gs2::Ranking2::Model
{
    class GS2RANKING2_API FClusterRankingReceivedReward final : public FGs2Object, public TSharedFromThis<FClusterRankingReceivedReward>
    {
        TOptional<FString> ClusterRankingReceivedRewardIdValue;
        TOptional<FString> RankingNameValue;
        TOptional<FString> ClusterNameValue;
        TOptional<int64> SeasonValue;
        TOptional<FString> UserIdValue;
        TOptional<int64> ReceivedAtValue;
        TOptional<int64> RevisionValue;

    public:
        FClusterRankingReceivedReward();
        FClusterRankingReceivedReward(
            const FClusterRankingReceivedReward& From
        );
        virtual ~FClusterRankingReceivedReward() override = default;

        TSharedPtr<FClusterRankingReceivedReward> WithClusterRankingReceivedRewardId(const TOptional<FString> ClusterRankingReceivedRewardId);
        TSharedPtr<FClusterRankingReceivedReward> WithRankingName(const TOptional<FString> RankingName);
        TSharedPtr<FClusterRankingReceivedReward> WithClusterName(const TOptional<FString> ClusterName);
        TSharedPtr<FClusterRankingReceivedReward> WithSeason(const TOptional<int64> Season);
        TSharedPtr<FClusterRankingReceivedReward> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FClusterRankingReceivedReward> WithReceivedAt(const TOptional<int64> ReceivedAt);
        TSharedPtr<FClusterRankingReceivedReward> WithRevision(const TOptional<int64> Revision);

        TOptional<FString> GetClusterRankingReceivedRewardId() const;
        TOptional<FString> GetRankingName() const;
        TOptional<FString> GetClusterName() const;
        TOptional<int64> GetSeason() const;
        FString GetSeasonString() const;
        TOptional<FString> GetUserId() const;
        TOptional<int64> GetReceivedAt() const;
        FString GetReceivedAtString() const;
        TOptional<int64> GetRevision() const;
        FString GetRevisionString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetUserIdFromGrn(const FString Grn);
        static TOptional<FString> GetRankingNameFromGrn(const FString Grn);
        static TOptional<FString> GetClusterNameFromGrn(const FString Grn);
        static TOptional<FString> GetSeasonFromGrn(const FString Grn);

        static TSharedPtr<FClusterRankingReceivedReward> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FClusterRankingReceivedReward, ESPMode::ThreadSafe> FClusterRankingReceivedRewardPtr;
}